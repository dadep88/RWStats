cmake_minimum_required(VERSION 3.26)

project(RollingStats VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

FUNCTION(PREPEND var )
    SET(listVar "")
    FOREACH(f ${${var}})
        LIST(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
    ENDFOREACH(f)
    SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

add_subdirectory(include)

enable_testing()
add_subdirectory(tests)

add_library(RollingStats INTERFACE ${RollingStats_INC})

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

target_link_libraries( RollingStats INTERFACE ${Boost_LIBRARIES} )

target_include_directories(RollingStats INTERFACE include)

add_custom_target(
        clangformat
        ALL
        COMMAND clang-format
        -style=file
        ${ALL_SOURCE_FILES})
