cmake_minimum_required(VERSION 3.4)
project(tinyspline)

# Turn on folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Exports TINYSPLINE_DEFINITIONS containing several preprocessor defines that
# are required by the remaining modules
add_subdirectory(src)
add_definitions("${TINYSPLINE_DEFINITIONS}")

ENABLE_TESTING()

## for gtest
ADD_SUBDIRECTORY(deps/googletest EXCLUDE_FROM_ALL)
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include/ ${gtest_SOURCE_DIR})

ADD_SUBDIRECTORY(tests)
# add_subdirectory(examples)
# add_subdirectory(test)
# add_subdirectory(docs)
# add_subdirectory(tools)
