project(Epicraft)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.5.1)

include(build/conanbuildinfo.cmake)

include_directories(${CMAKE_SOURCE_DIR}/Include)
include_directories(${CMAKE_SOURCE_DIR}/Include/Config)
include_directories(${CMAKE_SOURCE_DIR}/Include/Game)
include_directories(${CMAKE_SOURCE_DIR}/Include/Network)
include_directories(${CMAKE_SOURCE_DIR}/Include/Protocol)
include_directories(${CMAKE_SOURCE_DIR}/Include/Miscellaneous)

conan_basic_setup()
add_definitions("-g --std=c++17 -pthread")

file(GLOB_RECURSE ssources
        "Source/*.cpp"
        "Source/Config/*.cpp"
        "Source/Game/*.cpp"
        "Source/Network/*.cpp"
        "Source/Protocol/*.cpp"
        "Source/Miscellaneous/*.cpp")
file(GLOB_RECURSE sheaders
        "Include/*.hpp"
        "Include/Config/*.hpp"
        "Include/Game/*.hpp"
        "Include/Network/*.hpp"
        "Include/Protocol/*.hpp"
        "Include/Miscellaneous/*.hpp")

set(slist_include "")

foreach(i ${sheader})
    get_filename_component(directory  ${i} PATH)
    list(APPEND slist_include ${directory})
endforeach()
list(REMOVE_DUPLICATES slist_include)

add_executable(Epicraft ${ssources})
target_include_directories(Epicraft PRIVATE ${slist_include})

target_link_libraries(Epicraft ${CONAN_LIBS})
