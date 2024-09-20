cmake_minimum_required(VERSION 3.22)

project(Flanger)

set(CMAKE_CXX_STANDARD 20)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GIT_TAG 8.0.1
    VERSION 8.0.1
    GITHUB_REPOSITORY juce-framework/JUCE
    SOURCE_DIR ${LIB_DIR}/juce
)

add_subdirectory(plugin)
