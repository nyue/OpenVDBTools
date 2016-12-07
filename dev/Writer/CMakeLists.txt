ADD_EXECUTABLE ( simple_writer
  simple_writer_main.cpp
  )

ADD_EXECUTABLE ( random_points_writer
  random_points_writer_main.cpp
  )

TARGET_LINK_LIBRARIES ( simple_writer
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )

TARGET_LINK_LIBRARIES ( random_points_writer
  ${REQUIRED_OPENVDB_LINK_LIBRARIES}
  )
