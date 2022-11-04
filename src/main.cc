// STL includes
//#include <iostream>

// Project includes
#include <constexpr-lookup-table.h>

using PixelCoordinateType = std::tuple<unsigned int, unsigned int>;
using PixelValueType = std::tuple<unsigned char, unsigned char, unsigned char>;

template <unsigned int width, unsigned int height>
[[nodiscard]] constexpr auto create_LUT()
{
  constexpr_lookup_table::LUT<PixelCoordinateType, PixelValueType, width * height> lut;
  lut.add(PixelCoordinateType{20, 10}, PixelValueType({254, 255, 253}));
  return lut;
}

static constexpr auto lut_40_20 = create_LUT<40, 20>();

int main()
{
  // constexpr unsigned char result = std::get<0>(lut_40_20(20, 10));
  // std::cout << "Value should be 254: " << static_cast<unsigned int>(result) << std::endl;
  // return EXIT_SUCCESS;
  return std::get<0>(lut_40_20(20, 10));
}