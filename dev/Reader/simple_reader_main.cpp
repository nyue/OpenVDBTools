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

		std::cout << boost::format("Reading '%1%'") % vdb_file << std::endl;

        openvdb::io::File fileIn(vdb_file);
        fileIn.open();

        openvdb::GridPtrVecPtr grids = fileIn.getGrids();

        fileIn.close();

		std::cout << boost::format("Grid size = %1%") % grids->size() << std::endl;

		if (!grids->empty())
		{
			openvdb::points::PointDataGrid::Ptr inputPointDataGrid = openvdb::GridBase::grid<openvdb::points::PointDataGrid>((*grids)[0]);
			if (inputPointDataGrid)
			{
				if (!inputPointDataGrid->empty())
				{
					std::cout << boost::format("PointDataGrid is empty = %1%") %
							(inputPointDataGrid->empty()?"true":"false")
							<< std::endl;
					openvdb::points::PointDataTree& inputTree = inputPointDataGrid->tree();

					std::vector<openvdb::Index64> pointOffsets;
					std::vector<openvdb::Name> includeGroups;
					std::vector<openvdb::Name> excludeGroups;

					openvdb::Index64 total = openvdb::points::getPointOffsets(pointOffsets, inputTree, includeGroups, excludeGroups, /*inCoreOnly=*/true);
					std::cout << boost::format("PointDataGrid total = %1%") % total << std::endl;
					std::cout << boost::format("pointOffsets.size() = %1%") % pointOffsets.size() << std::endl;
					std::cout << boost::format("pointOffsets[0] = %1%") % pointOffsets[0] << std::endl;
					std::cout << boost::format("pointOffsets[1] = %1%") % pointOffsets[1] << std::endl;
					std::cout << boost::format("pointOffsets[2] = %1%") % pointOffsets[2] << std::endl;
					std::cout << boost::format("pointOffsets[3] = %1%") % pointOffsets[3] << std::endl;


					openvdb::Index64 point_count = openvdb::points::pointCount(inputTree);
					std::cout << boost::format("point_count = %1%") % point_count << std::endl;
				}
			}
		}
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
