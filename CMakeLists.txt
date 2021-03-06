CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )

PROJECT (OpenVDBTools)

FIND_PACKAGE ( OpenVDB 4.0 REQUIRED )
FIND_PACKAGE ( Boost REQUIRED COMPONENTS program_options )
FIND_PACKAGE ( ILMBase 2.2 REQUIRED )
FIND_PACKAGE ( TBB REQUIRED )

INCLUDE_DIRECTORIES (
  ${OpenVDB_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${ILMBASE_INCLUDE_DIRS}
  ${TBB_INCLUDE_DIR}
  )

SET ( REQUIRED_OPENVDB_LINK_LIBRARIES
  ${OpenVDB_openvdb_LIBRARY}
  ${Boost_LIBRARIES}
  )

ADD_DEFINITIONS (
  -DOPENVDB_3_ABI_COMPATIBLE
  -DOPENVDB_PRIVATE
  -DOPENVDB_USE_BLOSC
  -DOPENVDB_USE_GLFW_3
  )

ADD_SUBDIRECTORY ( dev )
