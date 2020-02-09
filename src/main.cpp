#include <iostream>
#include <fmt/format.h>
#include <fstream>
#include <vector>
#include "sha256.h"


void dispHash(const hashValues &h);

int main(int argc, char **argv) {
//  read file into stdin equiv to < operator on CL in Clion
//  freopen("../hello.txt", "r", stdin);

//  std::ifstream input("../example.pdf", std::ios::binary);
//  std::ifstream input("../test.txt", std::ios::binary);
//  std::ifstream input("../hello.txt", std::ios::binary);
  if (argc > 1) {
    std::ifstream input(argv[1], std::ios::binary);
    std::vector<unsigned char>buffer(std::istreambuf_iterator<char>(input), {});
    sha256 sha(buffer);
    dispHash(sha.digest());
  }

  return 0;

}
void dispHash(const hashValues &h) {
  fmt::print("{:08x}", h.h_0);
  fmt::print("{:08x}", h.h_1);
  fmt::print("{:08x}", h.h_2);
  fmt::print("{:08x}", h.h_3);
  fmt::print("{:08x}", h.h_4);
  fmt::print("{:08x}", h.h_5);
  fmt::print("{:08x}", h.h_6);
  fmt::print("{:08x}", h.h_7);
  std::cout << std::endl;
}




