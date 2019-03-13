project(Epitain)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.5.1)

include(build/conanbuildinfo.cmake)

include_directories(${CMAKE_SOURCE_DIR}/Include)
include_directories(${CMAKE_SOURCE_DIR}/Include/Network)
include_directories(${CMAKE_SOURCE_DIR}/Include/Protocol)

conan_basic_setup()
add_definitions("-g --std=c++17 -pthread")


file(GLOB_RECURSE ssources "Source/*.cpp" "Source/Network/*.cpp" "Source/Protocol/*.cpp")
file(GLOB_RECURSE sheaders "Include/*.hpp" "Include/Network/*.hpp" "Include/Protocol/*.hpp")

set(slist_include "")

foreach(i ${sheader})
    get_filename_component(directory  ${i} PATH)
    list(APPEND slist_include ${directory})
endforeach()
list(REMOVE_DUPLICATES slist_include)

add_executable(Epitain ${ssources})
target_include_directories(Epitain PRIVATE ${slist_include})

target_link_libraries(Epitain ${CONAN_LIBS})
