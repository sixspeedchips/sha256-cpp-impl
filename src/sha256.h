//
// Created by finn on 2/5/20.
//

#ifndef SHA256_SHA256_H
#define SHA256_SHA256_H

#include <cstdint>
#include <vector>

typedef struct _ubit_512 { __uint32_t word[16] = {0}; } _ubit_512;
typedef struct mSchedule { __uint32_t word[64] = {0}; } mSchedule;


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

struct workingVar {
  __uint32_t a = 0;
  __uint32_t b = 0;
  __uint32_t c = 0;
  __uint32_t d = 0;
  __uint32_t e = 0;
  __uint32_t f = 0;
  __uint32_t g = 0;
  __uint32_t h = 0;

};

class sha256 {

 private:
  __uint32_t k;
  std::vector<unsigned char> buffer;
  std::vector<_ubit_512> padded_message;
  void pad_message();
  void print_p_message();



 public:
  explicit sha256(const std::vector<unsigned char> &buffer);
  hashValues digest();

};


#endif //SHA256_SHA256_H
