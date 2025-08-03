#pragma once

// STL includes
#include <array>
#include <cstddef>
#include <type_traits>

// Project includes
#include "defines.hpp"

namespace CLT
{
/**
 * @brief Lookup-Table which can be used in constexpr context.
 * @tparam Key Key of the LUT, used for lookup-indexing
 * @tparam Value Value associated with a respective Key
 * @tparam S The size of the LUT which needs to be known at compile-time
 */
template <typename Key, typename Value, std::size_t S>
class LUT
{
  static_assert(std::is_default_constructible_v<Key>, "Key must be default constructible");
  static_assert(std::is_default_constructible_v<Value>, "Value must be default constructible");

public:
  using LUTEntryType = std::pair<Key, Value>;

public:
  template <typename... Ts>
  CLT_EXPLICIT CLT_CONSTEXPR LUT(Ts... key_value_pairs)
      : storage_{key_value_pairs...}, count_(sizeof...(key_value_pairs))
  {
    static_assert(sizeof...(key_value_pairs) <= S, "Too many entries for LUT size");
  }
  /**
   * @brief Lookup of value which is associated with Key created using ...args
   * @tparam ...Ts Types of arguments to instanciate the Key 'key'
   * @param ...args Arguments used to instanciate the Key 'key'
   * @return Value associated with Key 'key' if it exists
   * @throws std::runtime_error if the Key 'key' does not exist
   */
  template <typename... Ts>
  CLT_NODISCARD CLT_CONSTEXPR const Value& operator()(Ts... args) const
  {
    return this->operator()(Key{args...});
  }
  /// @brief Lookup of value which is associated with Key key
  /// @param k Key used to lookup for
  /// @return Value associated with key if it exists
  /// @throws std::runtime_error if the Key 'key' does not exist
  CLT_NODISCARD CLT_CONSTEXPR const Value& operator()(const Key& k) const
  {
    return Find(k);
  }
  /// @brief Adds a key-value-pair to the lookup table
  /// @param key The key to add
  /// @param value The value associated to add to the associated key
  CLT_CONSTEXPR void
  Add(const Key& key, const Value& value)
  {
    for (const auto& kv : storage_)
    {
      if (kv.first == key)
      {
        if (kv.second == value)
          return; // Key already exists with the same value
        else
          static_assert(
              false,
              "Key already exists with a different value. Please use a different key or value.");
      }
    }
    storage_[count_] = {key, value};
    ++count_;
  }

private:
  CLT_NODISCARD CLT_CONSTEXPR const Value& Find(const Key& key) const
  {
    std::size_t index{count_};
    std::size_t c{0};
    for (const LUTEntryType& storage_entry : storage_)
    {
      if (storage_entry.first == key)
      {
        index = c;
        break;
      }
      c++;
    }

    return storage_[index].second;
  }

  std::array<LUTEntryType, S> storage_{};
  std::size_t count_{0};
};
} // namespace CLT