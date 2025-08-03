#include <gtest/gtest.h>

#include <constexpr-lookup-table/constexpr-lookup-table.hpp>

class ConstexprLookupTableTest : public ::testing::Test
{
};

using PixelCoordinateType = std::tuple<unsigned int, unsigned int>;
using PixelValueType = std::tuple<unsigned char, unsigned char, unsigned char>;

template <unsigned int width, unsigned int height>
[[nodiscard]] consteval auto create_image_LUT()
{
  CLT::LUT<PixelCoordinateType, PixelValueType, width * height> lut(
      std::make_pair(PixelCoordinateType{20, 10}, PixelValueType{254, 255, 253}));
  return lut;
}

TEST_F(ConstexprLookupTableTest, Test_Add_Single_Pixel)
{
  static constexpr auto lut = create_image_LUT<40, 20>();

  constexpr auto v0 = std::get<0>(lut(20, 10));
  constexpr auto v1 = std::get<1>(lut(20, 10));
  constexpr auto v2 = std::get<2>(lut(20, 10));

  static_assert(v0 == 254);
  static_assert(v1 == 255);
  static_assert(v2 == 253);

  EXPECT_EQ(254, v0);
  EXPECT_EQ(255, v1);
  EXPECT_EQ(253, v2);
}
