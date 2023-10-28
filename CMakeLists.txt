cmake_minimum_required(VERSION 3.26)

project(RollingStats VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/SourcesAndHeaders.cmake)

add_library(RollingStats INTERFACE ${headers})
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
target_link_libraries( RollingStats INTERFACE ${Boost_LIBRARIES} )
target_include_directories(RollingStats INTERFACE include)

enable_testing()
add_subdirectory(tests)

add_executable(RollingStatsDemo ${demo_sources})
target_link_libraries(RollingStatsDemo RollingStats)

#file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h PRE_EXCLUDE_REGEXES "cmake*")
list(APPEND ALL_SOURCE_FILES "${RollingStats_INC}")
message(STATUS ${ALL_SOURCE_FILES})

add_custom_target(
        clang-format
        COMMAND clang-format
        -style=file

        ${headers} ${demo_sources} ${test_sources} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        clang-tidy
        COMMAND clang-tidy
        ${ALL_SOURCE_FILES}
        -format-style='file'
        -p cmake-build-release
        ${headers} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


