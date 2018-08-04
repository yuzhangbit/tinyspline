PROJECT(tests)

ADD_CUSTOM_TARGET(tests)

ADD_EXECUTABLE(tinyspline_c
  tinyspline_c_tests.cpp)
TARGET_LINK_LIBRARIES(tinyspline_c
  gtest
  gtest_main)

## This is for running "make test" command
ADD_TEST(NAME tinyspline_c COMMAND tinyspline_c)


# This is for wrapping all the tests to a single target called tests to build
## Without this command, make test command will not run any test
## If you miss some test executable targets, make test won't run the missed ones
ADD_DEPENDENCIES(tests
  tinyspline_c)