// STL includes
#include <iostream>

// Project includes
#include <constexpr-lookup-table.h>

static constexpr auto lut_1920_1080 = constexpr_lookup_table::create_LUT<40, 20>();

int main()
{
  constexpr unsigned char result = std::get<0>(lut_1920_1080(20, 10));
  std::cout << "Value should be 254: " << static_cast<unsigned int>(result) << std::endl;
  return EXIT_SUCCESS;
}