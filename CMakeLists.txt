project ( crave-bundle )
cmake_minimum_required(VERSION 2.8)


enable_testing()
list(INSERT CMAKE_PREFIX_PATH 0 "${CMAKE_BINARY_DIR}")
list(INSERT CMAKE_PREFIX_PATH 0 "${metaSMT_BINARY_DIR}/src")
add_subdirectory ( metaSMT )

add_subdirectory ( crave )

find_package(SystemC QUIET)
find_package(metaSMT QUIET)

add_subdirectory(examples)

############################################################
##                CPack settings                          ##
############################################################


# CPack version numbers for release tarball name.
if(UNIX)
execute_process(COMMAND date +%Y OUTPUT_VARIABLE CPACK_PACKAGE_VERSION_MAJOR ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND date +%m OUTPUT_VARIABLE CPACK_PACKAGE_VERSION_MINOR ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND date +%d OUTPUT_VARIABLE CPACK_PACKAGE_VERSION_PATCH ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

set(VERSION "${CPACK_PACKAGE_VERSION_MAJOR}-${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SMT programming library")
set(CPACK_PACKAGE_VENDOR "metaSMT development team")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set(CPACK_GENERATOR TGZ TGBZ2)
set(
CPACK_SOURCE_PACKAGE_FILE_NAME
"${PROJECT_NAME}-${VERSION}"
CACHE INTERNAL "tarball basename"
)
set(CPACK_SOURCE_GENERATOR TGZ TBZ2)

set(CPACK_SOURCE_IGNORE_FILES
"/\\\\.git"
"/deps.*/"
"/build.*/"
"/root.*/"
"/examples/simple_*/"
)
include(CPack)


############################################################
############################################################
