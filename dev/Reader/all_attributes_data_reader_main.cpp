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

//template<typename T>
//void get_attribute_data(const std::string& i_attribute_name, std::vector<T> o_attribute_data)
//{
//	openvdb::points::AttributeHandle<T>::Ptr handle = openvdb::points::AttributeHandle<openvdb::Vec3s>::create(leafIter->constAttributeArray("P"));
//
//    for (openvdb::points::PointDataTree::LeafNodeType::IndexOnIter iter = leafIter->beginIndexOn(); iter; ++iter)
//    {
//        const typename T voxelCoord = iter.getCoord().asVec3d();
//    }
//}

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
					if (!inputPointDataGrid->tree().empty())
					{
						openvdb::points::PointDataTree::LeafCIter leafIter = inputPointDataGrid->tree().cbeginLeaf();
						const openvdb::points::AttributeSet::Descriptor& descriptor = leafIter->attributeSet().descriptor();
						openvdb::points::AttributeSet::Descriptor::NameToPosMap::const_iterator npIter = descriptor.map().begin();
						openvdb::points::AttributeSet::Descriptor::NameToPosMap::const_iterator npEIter = descriptor.map().end();
						for (;npIter!=npEIter;++npIter)
						{
							const openvdb::Name& name = npIter->first;
							const size_t index = npIter->second;
							const openvdb::Name& valueType = descriptor.valueType(index);
							std::cout << boost::format("Attribute[%1%] is '%2%' of type %3%") % index % name.c_str() % valueType.c_str() << std::endl;


						}

						for (openvdb::points::PointDataTree::LeafCIter leafIter = inputPointDataGrid->tree().cbeginLeaf(); leafIter; ++leafIter)
						{
							const openvdb::Name attribute_name("Cd");
							openvdb::points::AttributeHandle<openvdb::Vec3s>::Ptr handle = openvdb::points::AttributeHandle<openvdb::Vec3s>::create(leafIter->constAttributeArray(attribute_name));

						    for (openvdb::points::PointDataTree::LeafNodeType::IndexOnIter iter = leafIter->beginIndexOn(); iter; ++iter)
						    {
						        if (attribute_name.compare("P")==0)
						        {

							        const openvdb::Vec3s voxelCoord = iter.getCoord().asVec3d();
							        const openvdb::Vec3s positionVoxelSpace = handle->get(*iter);
							        const openvdb::Vec3s positionWorldSpace = inputPointDataGrid->transform().indexToWorld(positionVoxelSpace + voxelCoord);
							        std::cout << boost::format("%1%: %2%") % attribute_name % positionWorldSpace << std::endl;
						        }
						        else
						        {
							        const openvdb::Vec3s positionVoxelSpace = handle->get(*iter);
						        	std::cout << boost::format("%1%: %2%") % attribute_name % positionVoxelSpace << std::endl;
						        }
						    }
						}
					}
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
