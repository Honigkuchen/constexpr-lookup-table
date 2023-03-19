// STL includes
#include <iostream>

// Project includes
#include <constexpr-lookup-table.h>

template <unsigned int width, unsigned int height>
[[nodiscard]] constexpr auto create_LUT()
{
  using KeyType = std::tuple<unsigned int, unsigned int>;
  using ValueType = std::tuple<unsigned char, unsigned char, unsigned char>;
  constexpr_lookup_table::LUT<KeyType, ValueType, width * height> lut;
  lut.add(KeyType{20, 10}, ValueType({254, 255, 253}));
  return lut;
}

int main()
{
  static constexpr auto lut_40_20 = create_LUT<40, 20>();
  static constexpr unsigned char result = std::get<0>(lut_40_20(20, 10));
  std::cout << "Value should be 254: " << static_cast<unsigned int>(result) << std::endl;
  return EXIT_SUCCESS;
}