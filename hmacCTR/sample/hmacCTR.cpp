#include <hmacsha256.h>
#include <fstream>

static const uint8_t nonce_size = 40;
static const uint8_t block_size = 32;

void mkIV(char* buff){
  std::ifstream getR;
  getR.open("/dev/urandom", std::ios::in|std::ios::binary);
  if(getR){
  getR.read(buff, block_size);
  getR.close();
  }
}

int main(int args, char** arg){
  if(args < 4) return -1;
  std::ifstream itext;
  std::ofstream otext;
  itext.open(arg[3], std::ios::in|std::ios::binary);
  otext.open(arg[4], std::ios::out|std::ios::binary);
  uint8_t pos;
  uint64_t cnt = 0;
  uint8_t x;
  char* key = arg[2];
  uint8_t key_len = strlen(key);
  char nonce[nonce_size];
  uint64_t it_len = 0;
  uint8_t blocks;
//setup IV + prep to encrypt data
  switch(arg[1][0]){
    case 'e':
	    mkIV(nonce);
  	  itext.seekg(0, itext.end);
    	it_len = itext.tellg();
	    itext.seekg(0, itext.beg);
  	  x = 56;
    	while(x <= 56){
      	otext.put((it_len>>x)&0xff);
 	     x -= 8;
  	  }
    	for(pos = 0; pos < block_size; pos++) otext.put(nonce[pos]);
	    blocks = it_len / block_size;
  	  break;
    case 'd':
    	x = 56;
    	while(x<=56){
      	it_len |= (uint64_t)(itext.get() << x);
      	x-=8;
    	}
    	blocks = it_len / block_size;
	    it_len += nonce_size;
	    for(pos = 0; pos < block_size; pos++) nonce[pos] = itext.get();
    	break;
  }
  hmac_sha256 hmac;
  for(uint16_t block = 0; block < blocks; block++){
    x = 56;
    for(pos = block_size; pos < nonce_size; pos++){
      nonce[pos] = (cnt >> x)&0xff;
      x-=8;
    }
    hmac.load(key, key_len, nonce, nonce_size);
    char* tmp = hmac.hmac();
    for(pos = 0; pos < block_size; pos++){
      otext.put(itext.get() ^ tmp[pos]);
    }
    cnt++;
  }

//last block
  x = 56;
  for(pos = block_size; pos < nonce_size; pos++){
    nonce[pos] = (cnt >> x)&0xff;
    x-=8;
  }
  hmac.load(key, key_len, nonce, nonce_size);
  char* tmp = hmac.hmac();
  pos = 0;
  while(itext.tellg() < it_len){
    otext.put(itext.get() ^ tmp[pos]);
    pos++;
  }
  itext.close();
  otext.close();
  return 0;
}
