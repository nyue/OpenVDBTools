#include <openvdb/points/PointDataGrid.h>
#include <openvdb/openvdb.h>

#include <openvdb/points/PointGroup.h>
#include <openvdb/points/PointCount.h>
#include <openvdb/points/PointConversion.h>

#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try {
		std::string vdb_file;
		po::options_description desc("Allowed options");
		desc.add_options()
            ("help", "produce help message")
            ("vdb", po::value<std::string>(&vdb_file),
			 "name of an OpenVDB file.")
			;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help") || vdb_file.empty()) {
			std::cout << desc << "\n";
			return 1;
		}

		openvdb::initialize();

		std::cout << boost::format("Writing '%1%'") % vdb_file << std::endl;

	    const float voxelSize(1.0);
	    openvdb::math::Transform::Ptr transform(openvdb::math::Transform::createLinearTransform(voxelSize));

	    // five points across four leafs

	    std::vector<openvdb::Vec3s> positions{{1, 1, 1}, {1, 101, 1}, {2, 101, 1}, {101, 1, 1}, {101, 101, 1}};

	    openvdb::points::PointDataGrid::Ptr grid = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(positions, *transform);
	    openvdb::points::PointDataTree& tree = grid->tree();

		std::vector<openvdb::Index64> pointOffsets;
		openvdb::Index64 total = getPointOffsets(pointOffsets, tree);

		openvdb::io::File fileOut(vdb_file);

		openvdb::GridCPtrVec grids{grid};

		fileOut.write(grids);

		openvdb::uninitialize();

    }
    catch(std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
		return 1;
    }
    catch(...) {
		std::cerr << "Exception of unknown type!\n";
    }
	return 0;
}

// == Emacs ================
// -------------------------
// Local variables:
// tab-width: 4
// indent-tabs-mode: t
// c-basic-offset: 4
// end:
//
// == vi ===================
// -------------------------
// Format block
// ex:ts=4:sw=4:expandtab
// -------------------------
