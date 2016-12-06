ADD_EXECUTABLE ( simple_writer
  simple_writer_main.cpp
  )

TARGET_LINK_LIBRARIES ( simple_writer
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )
