ADD_EXECUTABLE ( simple_reader
  simple_reader_main.cpp
  )

ADD_EXECUTABLE ( partitioned_reader
  partitioned_reader_main.cpp
  )

ADD_EXECUTABLE ( list_attributes
  list_attributes_main.cpp
  )

ADD_EXECUTABLE ( mandatory_attribute_P_data_reader
  mandatory_attribute_P_data_reader_main.cpp
  )

ADD_EXECUTABLE ( all_attributes_data_reader
  all_attributes_data_reader_main.cpp
  )

TARGET_LINK_LIBRARIES ( simple_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

TARGET_LINK_LIBRARIES ( partitioned_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

TARGET_LINK_LIBRARIES ( list_attributes
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

TARGET_LINK_LIBRARIES ( mandatory_attribute_P_data_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

TARGET_LINK_LIBRARIES ( all_attributes_data_reader
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )
