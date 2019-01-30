#include "hmacsha256.h"
#include <iostream>

int main(int args, char** arg){
  hmac_sha256 hmacs(arg[1], arg[2]);
  const char* tmp = hmacs.hmac();
  for(uint8_t pos = 0; pos < 32; pos++)
  std::cout << ((tmp[pos]<16)?"0":"") << std::hex << (unsigned int)tmp[pos];
  std::cout << '\n';
  return 0;
}
