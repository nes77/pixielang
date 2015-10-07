cmake_minimum_required (VERSION 3.0)
project (pixie)

# set up Boost
if (NOT DEFINED BOOST_ROOT AND
    NOT DEFINED ENV{BOOST_ROOT} AND
    NOT DEFINED BOOST_INCLUDEDIR AND
    NOT DEFINED ENV{BOOST_INCLUDEDIR} AND
    NOT DEFINED BOOST_LIBRARYDIR AND
    NOT DEFINED ENV{BOOST_LIBRARYDIR})
    
    set(BOOST_ROOT "libs/boost")

endif()

if (APPLE OR WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
endif()

find_package(Boost 1.46 REQUIRED COMPONENTS program_options filesystem regex)

# version number
set (PIXIE_VERSION_MAJOR 0)
set (PIXIE_VERSION_MINOR 1)

set (COMP_FLAGS "-g -Werror -Wall -Wno-reorder -std=c++11")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMP_FLAGS}")

configure_file (
    src/libpixie/pixie_config.in.hpp
    src/libpixie/pixie_config.hpp
    )

include_directories(src/libpixie ${Boost_INCLUDE_DIRS})

#message("PROJECT_SOURCE_DIR points to " ${PROJECT_SOURCE_DIR})

add_library(pixie-core
    SHARED
    src/libpixie/ast.cpp
    src/libpixie/lexer.cpp
    #src/libpixie/parser.cpp
)

add_executable(pixc 
    src/pixc/pixc.cpp
)

add_executable(pixie 
    src/pixie/pixie.cpp
)

#message("Boost libs: " ${Boost_LIBRARIES})

target_link_libraries(pixie-core ${Boost_LIBRARIES})
target_link_libraries(pixc pixie-core ${Boost_LIBRARIES})
target_link_libraries(pixie pixie-core ${Boost_LIBRARIES})

enable_testing()

add_test (pixc_simple_grammar pixc doc/grammar_test1.px)
add_test (pixc_huge_file pixc doc/grammar_test2.px)

