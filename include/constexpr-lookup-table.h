#pragma once

// STL includes
#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <tuple>

namespace constexpr_lookup_table
{
/// @brief Lookup-Table which can be used in constexpr context.
/// @tparam Key Key of the LUT, used for lookup-indexing
/// @tparam Value Value associated with a respective Key
/// @tparam S The size of the LUT which needs to be known at compile-time
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
  /// @brief Lookup of value which is associated with Key created using ...args
  /// @tparam ...Ts Types of arguments to instanciate the Key 'key'
  /// @param ...args Arguments used to instanciate the Key 'key'
  /// @return Value associated with Key 'key' if it exists
  /// @throws std::runtime_error if the Key 'key' does not exist
  template <typename... Ts>
  [[nodiscard]] constexpr const Value& operator()(Ts... args) const
  {
    return this->operator()(Key{args...});
  }
  /// @brief Lookup of value which is associated with Key key
  /// @param k Key used to lookup for
  /// @return Value associated with key if it exists
  /// @throws std::runtime_error if the Key 'key' does not exist
  [[nodiscard]] constexpr const Value& operator()(const Key& k) const
  {
    const auto iter = std::find_if(
        _storage.begin(), _storage.end(),
        [&k](const LUTEntryType& l)
        {
          return l.key == k;
        });

    if (iter != _storage.end())
      return iter->value;
    else
      throw std::runtime_error("Key does not exist!");
  }
  /// @brief Adds a key-value-pair to the lookup table
  /// @param key The key to add
  /// @param value The value associated to add to the associated key
  constexpr void add(const Key& key, const Value& value)
  {
    const auto iter = std::find_if(
        _storage.begin(), _storage.end(),
        [&key](const LUTEntryType& l)
        {
          return l.key == key;
        });

    if (iter == _storage.end())
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