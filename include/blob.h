#pragma once

#include <cstdint>
#include <cassert>
#include <array>
#include <ostream>
#include <string>
#include <string_view>
#include <span>
#include <algorithm>

#include "util/hex.h"


template<unsigned int bits>
class blob {

  static_assert(bits % 8 == 0);

protected:
  
  static constexpr unsigned int width_ = bits / 8;
  std::array<uint8_t, width_> data_; 

public:

  constexpr blob() : data_{} {}
  constexpr explicit blob(std::string_view hex_str);
  constexpr explicit blob(std::span<const unsigned char> chs);

  constexpr bool is_null() const;
  constexpr void set_null() { std::fill(data_.begin(), data_.end(), 0); }

  static constexpr unsigned int size() { return width_; }

  constexpr unsigned char* data() { return data_.data(); }
  constexpr const unsigned char* data() const { return data_.data(); }
  constexpr unsigned char* begin() { return data_.data(); }
  constexpr const unsigned char* begin() const { return data_.data(); }
  constexpr unsigned char* end() { return data_.data() + width_; }
  constexpr const unsigned char* end() const { return data_.data() + width_; }

public: 

  friend constexpr auto operator<=>(const blob& a, const blob& b) = default;

};

template<unsigned int bits>
constexpr blob<bits>::blob(std::string_view hex_str) {
  assert(hex_str.size() == width_ * 2);
  auto str_it = hex_str.rbegin();
  for (auto& e : data_) {
    auto l = hex_char_to_uint8t(*(str_it++));
    e = hex_char_to_uint8t(*(str_it++)) << 4 | l;
  }
}

template<unsigned int bits>
constexpr blob<bits>::blob(std::span<const unsigned char> chs) {
  std::copy(chs.begin(), chs.end(), data_.begin());
}

template<unsigned int bits>
constexpr bool blob<bits>::is_null() const { 
  return std::all_of(data_.begin(), data_.end(), [](uint8_t val) {
    return val == 0;
  });
}

template<unsigned int bits>
inline std::ostream& operator<<(std::ostream& os, const blob<bits>& value) {
  const unsigned char* it = value.end();
  const unsigned char* begin = value.begin();
  while (it != begin) {
    --it;
    uint8_t byte = *it;
    os << uint8t_to_hex_char((byte >> 4) & 0x0f)
       << uint8t_to_hex_char(byte & 0x0f);
  }
  return os;
}


using uint256_t = blob<256>;