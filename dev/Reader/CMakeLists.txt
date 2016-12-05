ADD_EXECUTABLE ( simple_reader
  simple_reader_main.cpp
  )

TARGET_LINK_LIBRARIES ( simple_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

