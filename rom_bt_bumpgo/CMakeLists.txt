cmake_minimum_required(VERSION 3.5)
project(rom_bt_bumpgo)

set(CMAKE_CONFIG_PATH ${CMAKE_MODULE_PATH}  "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CONFIG_PATH}")

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_cpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)

find_package(ZMQ)
if(ZMQ_FOUND)
    message(STATUS "ZeroMQ found.")
    add_definitions(-DZMQ_FOUND)
else()
  message(WARNING "ZeroMQ NOT found. Not including PublisherZMQ.")
endif()

set(CMAKE_CXX_STANDARD 17)

set(dependencies
    rclcpp
    behaviortree_cpp
    sensor_msgs
    geometry_msgs
    ament_index_cpp
)

include_directories(include ${ZMQ_INCLUDE_DIRS})

# add_library(rom_forward_bt_node SHARED src/Forward.cpp)
# add_library(rom_back_bt_node SHARED src/Back.cpp)
# add_library(rom_turn_bt_node SHARED src/Turn.cpp)
# add_library(rom_is_obstacle_bt_node SHARED src/IsObstacle.cpp)

# list(APPEND plugin_libs
#   rom_forward_bt_node
#   rom_back_bt_node
#   rom_turn_bt_node
#   rom_is_obstacle_bt_node
# )

# foreach(bt_plugin ${plugin_libs})
#   ament_target_dependencies(${bt_plugin} ${dependencies})
#   target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
# endforeach()

# add_executable(bt_bumpgo src/main_bumpgo.cpp)
# ament_target_dependencies(bt_bumpgo ${dependencies})
# target_link_libraries(bt_bumpgo ${ZMQ_LIBRARIES})

# install(TARGETS
#   ${plugin_libs}
#   bt_bumpgo
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION lib/${PROJECT_NAME}
# )

# install(DIRECTORY include/
#   DESTINATION include/
# )

# install(DIRECTORY behavior_tree_xml launch
#   DESTINATION share/${PROJECT_NAME}
# )


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)

  add_subdirectory(tests)
endif()

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})

ament_package()
