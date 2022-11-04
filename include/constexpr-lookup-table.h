#pragma once

// STL includes
#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <tuple>

namespace constexpr_lookup_table
{

template <typename Key, typename Value, std::size_t S>
class LUT
{
public:
  struct LUTEntry
  {
    Key key;
    Value value;
  };

private:
  using LUTEntryType = LUTEntry;

public:
  template <typename... Ts>
  [[nodiscard]] constexpr const Value& operator()(Ts... args) const
  {
    return this->operator()(Key{args...});
  }
  [[nodiscard]] constexpr const Value& operator()(const Key key) const
  {
    const auto iter = std::find_if(
        _storage.begin(), _storage.end(),
        [&key](const LUTEntryType& l)
        {
          return l.key == key;
        });

    if (iter != _storage.end())
      return iter->value;
    else
      throw std::runtime_error("Key does not exist!");
  }
  constexpr void add(const Key& key, const Value& value)
  {
    const auto iter = std::find_if(
        _storage.begin(), _storage.end(),
        [&key](const LUTEntryType& l)
        {
          return l.key == key;
        });

    if (iter != _storage.end())
      return;
    else
    {
      _storage[_count] = {key, value};
      ++_count;
    }
  }

private:
  std::array<LUTEntryType, S> _storage;
  std::size_t _count = 0;
};
using PixelCoordinateType = std::tuple<unsigned int, unsigned int>;
using PixelValueType = std::tuple<unsigned char, unsigned char, unsigned char>;

template <unsigned int width, unsigned int height>
[[nodiscard]] constexpr auto create_LUT()
{
  LUT<PixelCoordinateType, PixelValueType, width * height> lut;
  lut.add(PixelCoordinateType{20, 10}, PixelValueType({254, 255, 253}));
  return lut;
}
} // namespace constexpr_lookup_table