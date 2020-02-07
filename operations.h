//
// Created by finn on 2/6/20.
//

#ifndef SHA256_OPERATIONS_H
#define SHA256_OPERATIONS_H

u_int32_t Ch(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t Maj(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t SHR(u_int32_t x, u_int8_t n);
u_int32_t ROTR(u_int32_t x, __uint8_t n);
u_int32_t cSigmaZero(u_int32_t x);
u_int32_t cSigmaOne(u_int32_t x);
u_int32_t lSigmaZero(u_int32_t x);
u_int32_t lSigmaOne(u_int32_t x);


#endif //SHA256_OPERATIONS_H
