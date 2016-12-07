ADD_EXECUTABLE ( simple_reader
  simple_reader_main.cpp
  )

ADD_EXECUTABLE ( partitioned_reader
  partitioned_reader_main.cpp
  )

TARGET_LINK_LIBRARIES ( simple_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

TARGET_LINK_LIBRARIES ( partitioned_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

