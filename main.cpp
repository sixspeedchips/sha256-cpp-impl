#include <iostream>
#include <fmt/format.h>
#include <fstream>
#include <vector>
#include "sha256.h"
#include "constants.h"
#include "operations.h"

typedef struct _ubit_512 { __uint32_t word[8]; } _ubit_512;
typedef struct mSchedule { __uint32_t word[64]; } mSchedule;


void pad_message(const std::vector<unsigned char> &buffer,
                 std::vector<_ubit_512> *padded_message);
void print_message(std::vector<_ubit_512> *message);
hashValues digest(const std::vector<_ubit_512> *padded_message);


int main(int argc, char **argv) {
//  read file into stdin equiv to < operator on CL in Clion
//  freopen("../hello.txt", "r", stdin);

//  std::ifstream input("../example.pdf", std::ios::binary);
//  std::ifstream input("../test.txt", std::ios::binary);
  std::ifstream input("../hello.txt", std::ios::binary);
  // load the file into a vector as bytes
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

  // the padded message vector
  auto *padded_message = new std::vector<_ubit_512>();
  // process the raw input
  pad_message(buffer, padded_message);
  print_message(padded_message);
//  std::cout<<padded_message->size() << std::endl;
  hashValues h = digest(padded_message);
  fmt::print("{:04x}", h.h_0);
  fmt::print("{:04x}", h.h_1);
  fmt::print("{:04x}", h.h_2);
  fmt::print("{:04x}", h.h_3);
  fmt::print("{:04x}", h.h_4);
  fmt::print("{:04x}", h.h_5);
  fmt::print("{:04x}", h.h_6);
  fmt::print("{:04x}", h.h_7);
  std::cout << std::endl;

  return 0;

}


void pad_message(const std::vector<unsigned char> &buffer,
                 std::vector<_ubit_512> *padded_message) {
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
        // if the ptr in the buffer is not at the end
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
    padded_message->push_back(block);
  }
  // check if the last block can hold the 64 bits
  // containing the size of the message in binary
  // error here since a vector likely cannot
  // support a 2**64 bit byte array might need to re-impl
  // using file.seek to traverse the file
//  std::cout << ((buffer.size() * 8 + 1 % 512) < 64) << std::endl;
  if ((buffer.size() * 8 + 1 % 512) < 64) {
    _ubit_512 block{};
    block.word[7] |= buffer.size() * BYTE_SIZE;
    padded_message->push_back(block);
  } else {
    _ubit_512 *end = &padded_message->back();
    end->word[7] |= buffer.size() * BYTE_SIZE;
  }
}
void print_message(std::vector<_ubit_512> *message) {
  __uint64_t count = 0;
  for (_ubit_512 &_512_block: *message) {
    for (__uint32_t i_int: _512_block.word) {
      fmt::print("{:032b} ", i_int);
      if (++count % 2 == 0) {
        fmt::print("\n");
      }
    }

  }
}


hashValues digest(const std::vector<_ubit_512> *padded_message) {

  hashValues hashes{};
  workingVar vars{};
  for (_ubit_512 ubit512: *padded_message) {
    mSchedule W;
    for (int t = 0; t < 16; ++t) {
      W.word[t] = ubit512.word[t];
    }
    for (int t = 16; t < 64; ++t) {
      W.word[t] = lSigmaOne(W.word[t - 2]) + W.word[t - 7]
          + lSigmaZero(W.word[t - 15]) + W.word[t - 16];
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

      T1 = vars.h + cSigmaOne(vars.e) + Ch(vars.e, vars.f, vars.g) + K[t]
          + W.word[t];
      T2 = cSigmaZero(vars.a) + Maj(vars.a, vars.b, vars.c);

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


