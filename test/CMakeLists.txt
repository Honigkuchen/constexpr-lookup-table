add_executable(CPP_CMAKE_DEFAULT_TEST
constexpr-lookup-table-test.cc)
target_link_libraries(CPP_CMAKE_DEFAULT_TEST GTest::gtest_main)
# add_test(NAME unit_test COMMAND unit_test)
include(GoogleTest)
gtest_discover_tests(CPP_CMAKE_DEFAULT_TEST)
