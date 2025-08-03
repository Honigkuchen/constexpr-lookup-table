// STL includes
#include <cstddef>
#include <iostream>
#include <tuple>

// Project includes
#include <constexpr-lookup-table/constexpr-lookup-table.hpp>
#include <constexpr-lookup-table/defines.hpp>

/// @brief This function creates a lookup table for an image. Each pixel (x,y) is mapped to a respective RGB value (r,g,b).
/// @tparam width Width of the image
/// @tparam height Height of the image
/// @return Returns the lookup table
template <unsigned int width, unsigned int height>
CLT_NODISCARD CLT_CONSTEVAL auto create_image_LUT()
{
  using CLT::LUT;
  using KeyType = std::tuple<unsigned int, unsigned int>;
  using ValueType = std::tuple<std::byte, std::byte, std::byte>;
  LUT<KeyType, ValueType, width * height> lut(std::make_pair(KeyType{20, 10}, ValueType{std::byte{254}, std::byte{255}, std::byte{253}}));
  return lut;
}

int main()
{
  static constexpr auto lut_40_20 = create_image_LUT<40, 20>();
  static constexpr std::byte pixel_20_10 = std::get<0>(lut_40_20(20, 10));
  std::cout << "RGB value should be 254: " << std::to_integer<unsigned int>(pixel_20_10) << std::endl;
  return EXIT_SUCCESS;
}