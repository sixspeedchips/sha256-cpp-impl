//
// Created by finn on 2/5/20.
//

#include <vector>
#include <sys/types.h>
#include "sha256.h"
#include "constants.h"
#include "operations.h"

sha256::sha256(const std::vector<unsigned char> &buffer) {
  this->buffer = buffer;
  this->padded_message = std::vector<_ubit_512>();
  this->pad_message();
}
void sha256::pad_message() {
  u_long cPt = 0;
  // while the buffer is not empty begin to build blocks
  // of the message to be padded
  while (cPt < buffer.size()) {
    _ubit_512 block = _ubit_512();
    // each block is a 512 bit number
    // this is 8->uint32 numbers in an array
    for (unsigned int &word : block.word) {
      // each uint32 number must have the current
      // buffer byte added to it
      for (int j = 0; j < BYTES_PER_INT32; ++j) {
        unsigned char byte = 0x00;
        // if the position in the buffer is not at the end
        if (buffer.size() > cPt) {
          byte = buffer.at(cPt++);
          // if the buffer is empty add the 1-bit
        } else if (buffer.size() == cPt++) {
          byte = 0x80;
        }
        word = (word << BYTE_SIZE) | byte;
      }
    }
    // add the block to the padded message
    padded_message.push_back(block);
  }
  // check if the .st block can hold the 64 bits
  // containing the size of the message in binary
  // error here since a vector likely cannot
  // support a 2**64 bit byte array might need to re-impl
  // using file.seek to traverse the file
//  std::cout << ((buffer.size() * 8 + 1 % 512) < 64) << std::endl;
  if ((buffer.size() * BYTE_SIZE + 1 % 512) < 64) {
    _ubit_512 block{};
    block.word[15] |= buffer.size() * BYTE_SIZE;
    padded_message.push_back(block);
  } else {
    padded_message.back().word[15] |= buffer.size() * BYTE_SIZE;
  }
}

hashValues sha256::digest() {

  hashValues hashes{};
  workingVar vars{};
  for (_ubit_512 block: padded_message) {
    mSchedule W;
    for (int t = 0; t < 16; ++t) {
      W.word[t] = block.word[t];
    }
    for (int t = 16; t < 64; ++t) {
      W.word[t] = littleSigma1(W.word[t - 2]) + W.word[t - 7]
          + littleSigma0(W.word[t - 15]) + W.word[t - 16];
    }

    vars.a = hashes.h_0;
    vars.b = hashes.h_1;
    vars.c = hashes.h_2;
    vars.d = hashes.h_3;
    vars.e = hashes.h_4;
    vars.f = hashes.h_5;
    vars.g = hashes.h_6;
    vars.h = hashes.h_7;


    for (int t = 0; t < 64; ++t) {
      __uint32_t T1;
      __uint32_t T2;

      T1 = vars.h + bigSigma1(vars.e) + Ch(vars.e, vars.f, vars.g) + K[t]
          + W.word[t];
      T2 = bigSigma0(vars.a) + Maj(vars.a, vars.b, vars.c);

      vars.h = vars.g;
      vars.g = vars.f;
      vars.f = vars.e;
      vars.e = vars.d + T1;
      vars.d = vars.c;
      vars.c = vars.b;
      vars.b = vars.a;
      vars.a = T1 + T2;
    }

    hashes.h_0 += vars.a;
    hashes.h_1 += vars.b;
    hashes.h_2 += vars.c;
    hashes.h_3 += vars.d;
    hashes.h_4 += vars.e;
    hashes.h_5 += vars.f;
    hashes.h_6 += vars.g;
    hashes.h_7 += vars.h;
  }
  return hashes;
}
