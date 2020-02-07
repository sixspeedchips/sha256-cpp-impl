//
// Created by finn on 2/6/20.
//

#include <sys/types.h>
#include "operations.h"


u_int32_t Ch(u_int32_t x, u_int32_t y, u_int32_t z) {
  return (x & y) ^ (~x & z);
}
u_int32_t Maj(u_int32_t x, u_int32_t y, u_int32_t z) {
  return (x & y) ^ (x & z) ^ (y & z);
}
u_int32_t ROTR(u_int32_t x, __uint8_t n) {
  return (x >> n) | (x << (32u - n));
}
u_int32_t SHR(u_int32_t x, u_int8_t n) {
  return x >> n;
}
u_int32_t bigSigma0(u_int32_t x) {
  return ROTR(x, 2) ^ ROTR(x, 13) ^ (ROTR(x, 22));
}
u_int32_t bigSigma1(u_int32_t x) {
  return ROTR(x, 6) ^ ROTR(x, 11) ^ (ROTR(x, 25));
}
u_int32_t littleSigma0(u_int32_t x) {
  return ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3);
}
u_int32_t littleSigma1(u_int32_t x) {
  return ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10);
}