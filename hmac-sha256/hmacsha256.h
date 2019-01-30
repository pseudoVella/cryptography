#ifndef hmac_sha256_h
#define hmac_sha256_h
#include "sha.h"
class hmac_sha256{
private:
  bool rdy;
  static const uint8_t blocksize = 64;
  static const uint8_t outsize = 32;
  char* okey = 0;
  char* ikey = 0;
  char _hmac_[outsize];
public:
  hmac_sha256();
  hmac_sha256(const char* _key, const char* data);
  hmac_sha256(const char* _key, uint8_t key_size, const char* data, uint8_t data_size);
  ~hmac_sha256();
  void load(const char* _key, uint8_t key_size, const char* data, uint8_t data_size);
  void load(const char* _key, const char* data);
  char* hmac();
};
#endif
