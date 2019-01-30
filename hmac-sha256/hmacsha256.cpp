#include "hmacsha256.h"

hmac_sha256::hmac_sha256(){
  rdy = false;
}

hmac_sha256::hmac_sha256(const char* _key, const char* data){
  load(_key, strlen(_key), data, strlen(data));
}

hmac_sha256::hmac_sha256
(const char* _key, uint8_t key_size, const char* data, uint8_t data_size){
  load(_key, key_size, data, data_size);
}
hmac_sha256::~hmac_sha256(){
  if(okey) delete[] okey;
  if(ikey) delete[] ikey;
}
void hmac_sha256::load
(const char* _key, uint8_t key_size, const char* data, uint8_t data_size){
  uint8_t msg_size = blocksize + data_size;
  uint8_t pos;
  sha hash;
  char* tmp;
  if(ikey){ delete[] ikey; ikey = 0; }
  if(okey){ delete[] okey; okey = 0; }
  ikey = new (std::nothrow) char[blocksize + data_size];
  okey = new (std::nothrow) char[blocksize + outsize];
  if(key_size > blocksize){
    hash.load(_key, key_size);
    tmp = hash.calc();
    for(pos = 0; pos < blocksize; pos++){
      if(pos < outsize){
        okey[pos] = tmp[pos] ^ 0x5c;
        ikey[pos] = tmp[pos] ^ 0x36;
      }
      else{
        okey[pos] = 0 ^ 0x5c;
        ikey[pos] = 0 ^ 0x36;
      }
    }
  }
  else{
    for(pos = 0; pos < blocksize; pos++){
      if(pos < key_size){
        okey[pos] = _key[pos] ^ 0x5c;
        ikey[pos] = _key[pos] ^ 0x36;
      }
      else{
        okey[pos] = 0 ^ 0x5c;
        ikey[pos] = 0 ^ 0x36;
      }
    }
  }
  for(pos = blocksize; pos < msg_size; pos++) ikey[pos] = data[pos - blocksize];
  hash.load(ikey, msg_size);
  tmp = hash.calc();
  msg_size = blocksize + outsize;
  for(pos = blocksize; pos < msg_size; pos++) okey[pos] = tmp[pos - blocksize];
  hash.load(okey, msg_size);
  tmp = hash.calc();
  for(pos = 0; pos < outsize; pos++) _hmac_[pos] = tmp[pos];
  rdy = true;
}

void hmac_sha256::load(const char* _key, const char* data){
  load(_key, strlen(_key), data, strlen(data));
}

char* hmac_sha256::hmac(){
  if(rdy) return _hmac_;
}
