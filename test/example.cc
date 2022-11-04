#include <gtest/gtest.h>

class ExampleTest : public ::testing::Test
{
};

TEST_F(ExampleTest, Example)
{
  std::vector<char> symbols = {};
  EXPECT_EQ(0, symbols.size());
}
