# Created by Hal@shurabaP
# This code is under The BSD 3-Caluse License.
# See more Licence.txt.
cmake_minimum_required(VERSION 3.1)
project(haruneko_util)

# configuration for Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# cmake options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# dependency
find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)

# sources
add_library(haruneko_util json/Json.h json/QHashJson.h json/QListJson.h io/DeviceFactory.cpp io/DeviceFactory.h json/QStringJson.h io/DeviceTextReader.cpp io/DeviceTextReader.h io/DeviceReader.h io/DeviceJsonReader.h io/DeviceWriter.h io/DeviceJsonWriter.h util/Try.h util/Execption.h Entity.cpp Entity.h io/DirectoryEnumerator.cpp io/DirectoryEnumerator.h util/Duration.h json/JsonValidator.h json/QIntJson.h)

target_link_libraries(haruneko_util Qt5::Core)

install(TARGETS haruneko_util DESTINATION lib/haruneko EXPORT haruneko_util_targets)
install(EXPORT haruneko_util_targets DESTINATION lib/haruneko)
