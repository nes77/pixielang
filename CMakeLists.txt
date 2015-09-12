cmake_minimum_required (VERSION 3.0)
project (pixie)

# version number
set (PIXIE_VERSION_MAJOR 0)
set (PIXIE_VERSION_MINOR 1)

configure_file (
    includes/pixie_config.h.in
    includes/pixie/pixie_config.h
    )

include_directories(includes)

add_executable(pixie
        src/main.cpp
        src/pixie/object.cpp src/pixie/function.cpp
        includes/pixie/object.hpp includes/pixie/function.hpp
        includes/pixie/instructions.hpp includes/pixie/common.hpp)

include (InstallRequiredSystemLibraries)

set (CPACK_RESOURCE_FILE_LICENSE LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR "${PIXIE_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PIXIE_VERSION_MINOR}")

include (CPack)
