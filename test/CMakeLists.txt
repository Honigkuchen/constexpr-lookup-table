set(TEST_EXECUTABLE_NAME constexpr-lookup-table_TEST)
add_executable(${TEST_EXECUTABLE_NAME}
constexpr-lookup-table-test.cc)
target_link_libraries(${TEST_EXECUTABLE_NAME} GTest::gtest_main)
# add_test(NAME unit_test COMMAND unit_test)
include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE_NAME})
