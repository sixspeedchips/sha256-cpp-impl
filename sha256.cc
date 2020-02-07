//
// Created by finn on 2/5/20.
//

#include <vector>
#include "sha256.h"

sha256::sha256(const std::vector<unsigned char> &buffer) {
  this->buffer = buffer;
  this->l = buffer.size()*8;

}
