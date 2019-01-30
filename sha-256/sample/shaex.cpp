#include "sha.h"
#include <iostream>

int main(int args, char**arg){
  sha _hash(arg[1]);
  const char * x = _hash.calc();
  std::cout << _hash.show_hash() << '\n';
  for(uint8_t pos = 0; pos < 32; pos ++){
    std::cout << std::hex
    << ((x[pos] < 16) ? "0" : "")
    << (unsigned int)x[pos];
  }
  std::cout << '\n';
  return 0;
}
