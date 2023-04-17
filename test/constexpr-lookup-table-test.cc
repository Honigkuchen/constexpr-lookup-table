#include <gtest/gtest.h>

#include <constexpr-lookup-table.h>

class ConstexprLookupTableTest : public ::testing::Test
{
};

using PixelCoordinateType = std::tuple<unsigned int, unsigned int>;
using PixelValueType = std::tuple<unsigned char, unsigned char, unsigned char>;

template <unsigned int width, unsigned int height>
[[nodiscard]] consteval auto create_image_LUT()
{
  constexpr_lookup_table::LUT<PixelCoordinateType, PixelValueType, width * height> lut;
  lut.add(PixelCoordinateType{20, 10}, PixelValueType({254, 255, 253}));
  return lut;
}

template <unsigned int width = 2, unsigned int height = 2>
[[nodiscard]] consteval auto create_image_LUT_add_overflow()
{
  constexpr_lookup_table::LUT<PixelCoordinateType, PixelValueType, width * height> lut;
  for (auto i = 0; i < 4; ++i)
    lut.add(PixelCoordinateType{i, 10}, PixelValueType({254, 255, 253}));
  return lut;
}

TEST_F(ConstexprLookupTableTest, Test_Add_Single_Pixel)
{
  constexpr auto lut = create_image_LUT<40, 20>();

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

TEST_F(ConstexprLookupTableTest, Test_Add_Overflow)
{
  constexpr auto lut = create_image_LUT_add_overflow<2, 2>();

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