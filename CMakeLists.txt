cmake_minimum_required (VERSION 3.0)
project (ppxe)

# version number
set (PPXE_VERSION_MAJOR 0)
set (PPXE_VERSION_MINOR 1)

configure_file (
    includes/ppxe_config.h.in
    includes/ppxe_config.h
    )

include_directories(includes)

add_executable(ppxe
        src/main.cpp
        src/ppxe/object.cpp src/ppxe/function.cpp
        includes/ppxe/object.hpp includes/ppxe/function.hpp
        includes/ppxe/instructions.hpp includes/ppxe/common.hpp)

include (InstallRequiredSystemLibraries)

set (CPACK_RESOURCE_FILE_LICENSE LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR "${PPXE_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PPXE_VERSION_MINOR}")

include (CPack)
