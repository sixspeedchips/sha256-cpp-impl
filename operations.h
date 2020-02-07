//
// Created by finn on 2/6/20.
//

#ifndef SHA256_OPERATIONS_H
#define SHA256_OPERATIONS_H

u_int32_t Ch(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t Maj(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t SHR(u_int32_t x, u_int8_t n);
u_int32_t ROTR(u_int32_t x, __uint8_t n);
u_int32_t bigSigma0(u_int32_t x);
u_int32_t bigSigma1(u_int32_t x);
u_int32_t littleSigma0(u_int32_t x);
u_int32_t littleSigma1(u_int32_t x);


#endif //SHA256_OPERATIONS_H
