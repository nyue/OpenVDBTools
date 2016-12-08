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
					for (openvdb::points::PointDataTree::LeafCIter leafIter = inputPointDataGrid->tree().cbeginLeaf(); leafIter; ++leafIter)
					{
						const openvdb::points::AttributeSet& as = leafIter->attributeSet();
						size_t num_attributes = as.size();
						std::cout << boost::format("AttributeSet size %1%") % num_attributes << std::endl;
						for (auto pos = 0;pos<num_attributes;pos++)
						{
							size_t descriptor_size = as.descriptor().size();
							std::cout << boost::format("Descriptor name pair {%1%,%2%}") % as.descriptor().type(0).first.c_str() % as.descriptor().type(0).second.c_str() << std::endl;
							std::cout << boost::format("descriptor_size %1%") % descriptor_size << std::endl;
							const openvdb::points::AttributeArray* aa = as.get(pos);
							if (aa)
							{
								std::cout << boost::format("Attribute name pair {%1%,%2%}") % aa->type().first.c_str() % aa->type().second.c_str() << std::endl;
							}
						}
						openvdb::points::AttributeHandle<openvdb::Vec3f>::Ptr handle = openvdb::points::AttributeHandle<openvdb::Vec3f>::create(leafIter->constAttributeArray("P"),true);
						if (handle)
							std::cout << "Handle is valid" << std::endl;
						else
							std::cout << "Handle is invalid" << std::endl;
					}
#ifdef UNUSED
					std::cout << boost::format("PointDataGrid name = '%1%', type = '%2%', metadata count = %3%")
									% inputPointDataGrid->getName()
									% inputPointDataGrid->gridType()
									% inputPointDataGrid->metaCount()
									<< std::endl;

					openvdb::MetaMap::ConstMetaIterator mIter = inputPointDataGrid->beginMeta();
					openvdb::MetaMap::ConstMetaIterator mEIter = inputPointDataGrid->endMeta();

					for (;mIter!=mEIter;++mIter)
					{
						std::cout << boost::format("MetaData['%1%'] has '%2%'") % mIter->first % mIter->second->str()<< std::endl;
					}
#endif // UNUSED

#ifdef UNUSED
					openvdb::points::PointDataTree& inputTree = inputPointDataGrid->tree();

					const openvdb::points::PointDataGrid::TreeType::LeafNodeType& leaf = *inputTree.cbeginLeaf();
		            const openvdb::points::AttributeSet& attributeSet = leaf.attributeSet();
		            size_t num_attributes = attributeSet.size();
					std::cout << boost::format("num_attributes = %1%") % num_attributes << std::endl;
					for (size_t index=0;index<num_attributes;index++)
					{
						const openvdb::points::AttributeArray* aa = attributeSet.getConst(index);
						std::cout << boost::format("Attribute[%1%] = %2%") % aa->type().first % aa->type().second << std::endl;
					}


		            const openvdb::points::AttributeSet::Descriptor& descriptor = leaf.attributeSet().descriptor();
					std::cout << boost::format("descriptor.size() = %1%") % descriptor.size() << std::endl;
					std::cout << boost::format("Meta Data count = %1%") % descriptor.getMetadata().metaCount() << std::endl;

					openvdb::MetaMap::ConstMetaIterator mmIter = descriptor.getMetadata().beginMeta();
					openvdb::MetaMap::ConstMetaIterator mmEIter = descriptor.getMetadata().endMeta();
					size_t index = 0;
					for (;mmIter!=mmEIter;++mmIter)
					{
						std::cout << boost::format("MetaData[%1%] = %2%") % index % mmIter->first << std::endl;
						index++;
					}
#endif // UNUSED
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
