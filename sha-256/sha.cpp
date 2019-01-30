#include "sha.h"
const uint8_t sha::outputSize(){
  return 32;
}

std::string  sha::show_hash(){
  std::ostringstream o;
  if(rdy){
  for(uint8_t pos = 0; pos < 32; pos++)
  o << ((hash[pos]<16)?"0":"")
  << std::hex << (unsigned int)hash[pos];
  o << '\n';
  }
  else o << "calculate me first...." << '\n';
  return o.str();
}

void sha::gen_M_(uint8_t block){
  uint8_t n;
  uint8_t start = block * 64;
  for(n = 0; n < 16; n++){
    _M_[n] = mk_word(data + start + (4*n));
  }
  for(n = 16; n < 64; n++){
    _M_[n] = mfunc1(_M_[n - 2]) + _M_[n - 7] + mfunc0(_M_[n - 15]) + _M_[n - 16];
  }
}

//binary math functions
uint32_t sha::roR(uint32_t& _word_, uint8_t _n){
  return ((_word_ >> _n) | (_word_ << (32 - _n)));
}
uint32_t sha::Ch(uint32_t& X, uint32_t const& Y, uint32_t const& Z){
return ((X & Y) ^ (~(X) & Z));
}
uint32_t sha::Maj(uint32_t& X, uint32_t const& Y, uint32_t const& Z){
return ((X & Y) ^ (X & Z) ^ (Y & Z));
}
uint32_t sha::func0(uint32_t& X){
return (roR(X, 2) ^ roR(X, 13) ^ roR(X, 22));
}
uint32_t sha::func1(uint32_t& X){
return (roR(X, 6) ^ roR(X, 11) ^ roR(X, 25));
}
uint32_t sha::mfunc0(uint32_t& X){
return (roR(X, 7) ^ roR(X, 18) ^ (X >> 3));
}
uint32_t sha::mfunc1(uint32_t& X){
return (roR(X, 17) ^ roR(X, 19) ^ (X >> 10));
}

uint32_t sha::mk_word(const char * __s){
  uint32_t _word_ = ((uint32_t)__s[0] << 24)
    | ((uint32_t)__s[1] << 16)
    | ((uint32_t)__s[2] << 8)
    | (uint32_t)__s[3];
  return _word_;
}

void sha::split_word(const uint32_t& _word_, char* buff){
  uint8_t y = 24;
  for(uint8_t x = 0; x < 4; x++){
    buff[x] = (_word_ >> y) & 0xff;
    y -= 8;
  }
}

void sha::load(const char* _data_, uint64_t size){
  uint8_t ac = size % 64;//calculate 0's to append
  uint8_t pos;
  if(ac > 55) ac = 120 - ac;
  else ac = 56 - ac;
  if(rdy){
    rdy = false;
    if(data) delete [] data;
  }
  data = new char[size + ac + 8];//create new msg of apropriate bit-length
  for(pos = 0; pos < size; pos++) data[pos] = _data_[pos];
  data[size] = 0x80;//append a single 1 and 7 0's
  for(pos = 1; pos < ac; pos++){
    //append 0's until we reach a multiple of 512. (-64 bits for length)
    data[size + pos] = 0;
  }
  //append og msg length
  uint64_t bit_len = size * 8;
  size += pos;
  data[size] = (bit_len >> 56)&0xff;
  size++;
  data[size] = (bit_len >> 48)&0xff;
  size++;
  data[size] = (bit_len >> 40)&0xff;
  size++;
  data[size] = (bit_len >> 32)&0xff;
  size++;
  data[size] = (bit_len >> 24)&0xff;
  size++;
  data[size] = (bit_len >> 16)&0xff;
  size++;
  data[size] = (bit_len >> 8)&0xff;
  size++;
  data[size] = bit_len & 0xff;
  size++;
  _blocks_ = size / 64;
}
void sha::load(const char* _data_){
  load(_data_, strlen(_data_));
}

//constructor
sha::sha(){
  rdy = false;
}
sha::sha(const char* _data_){
  load(_data_, strlen(_data_));
}
sha::sha(const char* _data_, uint64_t size){
  load(_data_, size);
}

sha::~sha(){
  if(data) delete [] data;
}

  //member functions
char* sha::calc(){
  if(rdy) return hash;
  const uint32_t _K_[_turns_] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };
  uint32_t _H_[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
  };
  _M_ = new uint32_t[_turns_];
  uint32_t T1, T2;
  uint32_t ah[8];
  uint8_t pos;
  for(uint8_t cur_block = 0; cur_block < _blocks_; cur_block++){
    gen_M_(cur_block);
    for(pos = 0; pos < 8; pos++) ah[pos] = _H_[pos];

    for(pos = 0; pos < _turns_; pos++){
      T1 = ah[7] + func1(ah[4]) + Ch(ah[4], ah[5], ah[6]) + _K_[pos] + _M_[pos];
      T2 = func0(ah[0]) + Maj(ah[0], ah[1], ah[2]);
      ah[7] = ah[6];
      ah[6] = ah[5];
      ah[5] = ah[4];
      ah[4] = ah[3] + T1;
      ah[3] = ah[2];
      ah[2] = ah[1];
      ah[1] = ah[0];
      ah[0] = T1 + T2;
    }
    for(pos = 0; pos < 8; pos++) _H_[pos] += ah[pos];
  }
  rdy = true;
  delete [] _M_; //free memory used to store msg block
  _M_ = 0;
  for(pos = 0; pos < 8; pos++) split_word(_H_[pos], hash + (4*pos));
  return hash;
}
