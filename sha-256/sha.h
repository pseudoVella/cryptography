#ifndef _SHA256_h
#define _SHA256_h
#include <sstream>

class sha {
private:
  static const uint8_t _turns_ = 64;

  char * data;
  bool rdy;
  uint8_t _blocks_;
  uint32_t* _M_;  //message block

  //private member functions
  uint32_t roR(uint32_t& _word_, uint8_t _n);
  uint32_t Ch(uint32_t& X, uint32_t const& Y, uint32_t const& Z);
  uint32_t Maj(uint32_t& X, uint32_t const& Y, uint32_t const& Z);
  uint32_t func0(uint32_t& X);
  uint32_t func1(uint32_t& X);
  uint32_t mfunc0(uint32_t& X);
  uint32_t mfunc1(uint32_t& X);

  uint32_t mk_word(const char * __s);
  void split_word(const uint32_t& _word_, char* buff);
  void gen_M_(uint8_t block);

public:
  //constructor
  sha();
  sha(const char* _data_);
  sha(const char* _data_, uint64_t size);
  ~sha();

  //member functions
  const uint8_t outputSize();
  char* calc();
  std::string show_hash();
  void load(const char* _data_);
  void load(const char* _data_, uint64_t size);

  //buff to store calculated hash
  char hash[32];
};

#endif
