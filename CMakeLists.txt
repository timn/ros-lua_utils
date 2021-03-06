cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
include(FindPkgConfig)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_definitions(-DUSE_ROS -DHAVE_INOTIFY)
pkg_check_modules(LUA_DEB lua5.1)
pkg_check_modules(LUA_FED lua)

if(LUA_DEB_FOUND)
  include_directories(${LUA_DEB_INCLUDE_DIRS})
  link_libraries(${LUA_DEB_LIBRARIES})
elseif(LUA_FED_FOUND)
  include_directories(${LUA_FED_INCLUDE_DIRS})
  link_libraries(${LUA_FED_LIBRARIES})
else()
  message(FATAL_ERROR "Lua not found on system.")
endif()


message("-- checking for tolua++")
find_library(TOLUA_DEB tolua++5.1)
find_library(TOLUA_FED tolua++)

if(TOLUA_DEB)
  message("--   Debian style tolua++ found")
  link_libraries(${TOLUA_DEB})
elseif(TOLUA_FED)
  message("--   Fedora style tolua++ found")
  link_libraries(${TOLUA_FED})
else()
  message(FATAL_ERROR "tolua++ not found on system.")
endif()



#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

rosbuild_add_library(${PROJECT_NAME} src/fam.cpp src/context.cpp src/exceptions.cpp src/context_watcher.cpp)
set(${PROJECT_NAME}_CFLAGS_OTHER -DUSE_ROS)

