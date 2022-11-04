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
private:
  struct LUTEntry
  {
    Key key;
    Value value;
  };
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
} // namespace constexpr_lookup_table