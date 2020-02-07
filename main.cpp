#include <iostream>
#include <fmt/format.h>
#include <fstream>
#include <vector>
#include "sha256.h"


typedef struct _uint_512 { __uint32_t pInt[8]; } _uint_512;

const u_int8_t BYTES_PER_INT32 = 4;
const u_int8_t BYTE_SIZE = 8;


void get_message(const std::vector<unsigned char> &buffer,
                 std::vector<_uint_512> *padded_message);
void print_message(std::vector<_uint_512> *message);


int main(int argc, char **argv) {
//  read file into stdin equiv to < operator on CL in Clion
//  freopen("../hello.txt", "r", stdin);

//  std::ifstream input("../example.pdf", std::ios::binary);
//  std::ifstream input("../test.txt", std::ios::binary);
  std::ifstream input("../hello.txt", std::ios::binary);
  // load the file into a vector as bytes
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

  // the padded message vector
  auto *padded_message = new std::vector<_uint_512>();
  // process the raw input
  get_message(buffer, padded_message);
  // utility function to print the padded message
  print_message(padded_message);

  std::cout << std::endl;
  return 0;

}


void get_message(const std::vector<unsigned char> &buffer,
                 std::vector<_uint_512> *padded_message) {
  u_long cPt = 0;
  // while the buffer is not empty begin to build blocks
  // of the message to be padded
  while (cPt < buffer.size()) {
    _uint_512 h_n = _uint_512();
    // each block is a 512 bit number
    // this is 8->uint32 numbers in an array
    for (unsigned int &anInt : h_n.pInt) {
      // each uint32 number must have the current
      // buffer byte added to it
      for (int j = 0; j < BYTES_PER_INT32; ++j) {
        unsigned char byte = 0x00;
        // if the ptr in the buffer is not at the end
        if (buffer.size() > cPt) {
          byte = buffer.at(cPt++);
        // if the buffer is empty add the 1-bit
        } else if (buffer.size() == cPt) {
          byte = 0x80;
          cPt++;
        }
        anInt = (anInt << BYTE_SIZE) | byte;
      }
    }
    // add the block to the padded message
    padded_message->push_back(h_n);
  }
  // check if the last block can hold the 64 bits
  // containing the size of the message in binary
  // error here since a vector likely cannot
  // support a 2**64 bit byte array might need to re-impl
  // using file.seek to traverse the file
  if(buffer.size() % 64 > BYTE_SIZE){
    _uint_512 s{};
    s.pInt[7] |= buffer.size() * BYTE_SIZE;
    padded_message->push_back(s);
  } else{
    _uint_512 *end = &padded_message->back();
    end->pInt[7] |= buffer.size() * BYTE_SIZE;
  }
}
void print_message(std::vector<_uint_512> *message) {
  __uint64_t count = 0;
  for (_uint_512 &_512_block: *message) {
    for (__uint32_t i_int: _512_block.pInt) {
      fmt::print("{:032b} ", i_int);
      if (++count % 2 == 0) {
        fmt::print("\n");
      }
    }

  }
}
