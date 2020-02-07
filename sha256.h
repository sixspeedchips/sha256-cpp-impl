//
// Created by finn on 2/5/20.
//

#ifndef SHA256_SHA256_H
#define SHA256_SHA256_H

#include <cstdint>

struct uint256_t
{
  uint64_t bits[4];
};

struct hashValues {
  __uint32_t h_0 = 0x6a09e667;
  __uint32_t h_1 = 0xbb67ae85;
  __uint32_t h_2 = 0x3c6ef372;
  __uint32_t h_3 = 0xa54ff53a;
  __uint32_t h_4 = 0x510e527f;
  __uint32_t h_5 = 0x9b05688c;
  __uint32_t h_6 = 0x1f83d9ab;
  __uint32_t h_7 = 0x5be0cd19;
};


class sha256 {

 private:
  int k;
  __u_long l;
  std::vector<unsigned char> buffer;


 public:
  sha256(const std::vector<unsigned char> &buffer);
};


#endif //SHA256_SHA256_H
