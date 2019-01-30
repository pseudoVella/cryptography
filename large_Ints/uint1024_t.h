#ifndef uint1024_t_h
#define uint1024_t_h
#include <iostream>
//#define setbit(a, b) (a |= 1ULL<<b)
//#define clearbit(a, b) (a &= ~(1ULL<<b))
//#define checkbit(a, b) (((a & (1ULL<<b)) == (1ULL<<b))?1:0)

//check if bit is set
#define checkbit(a, b) (a[(b>>3)] & (1U<<(b&7U)))
//clear bit, set bit, clear or set bit conditionally
#define cbit(a,b) (a[(b>>3)] &= (~(1U<<(b&7U))))
#define sbit(a,b) (a[(b>>3)] |= (1U<<(b&7U)))
#define CS_bit(a,b,c) (a[(b>>3)] ^= ((-c) ^ a[(b>>3)]) & (1U<<(b&7U)))
//check highest bit, check lowest bit
#define CHbit(a) (a&(1ULL<<((sizeof(a)<<3U)-1U)))
#define CLbit(a) (a&1)

class uint1024_t {

private:
	static const uint8_t num_bytes = 128;
	static const uint16_t num_bits = 1024;

public:
//constructors
  uint1024_t();

  uint1024_t(uint1024_t& __n);
  uint1024_t(const uint1024_t& __n);

	template <typename num_t>
  uint1024_t(num_t __n);

 //array to hold extremely large 1024bit number
	uint8_t val[num_bytes];

	//operators
	bool operator==(const uint1024_t& __n);
	template <typename num_t>
	 bool operator==(num_t __n);

	bool operator>=(const uint1024_t& __n);
	template <typename num_t>
	 bool operator>=(num_t __n);

	bool operator<=(const uint1024_t& __n);
	template <typename num_t>
	 bool operator<=(num_t __n);

	bool operator>(const uint1024_t& __n);
	template <typename num_t>
	 bool operator>(num_t __n);

	bool operator<(const uint1024_t& __n);
	template <typename num_t>
	 bool operator<(num_t __n);

	uint1024_t& operator=(const uint1024_t& __n);
	template <typename num_t>
	 uint1024_t& operator=(num_t __n);

	uint1024_t& operator+=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator+=(num_t __n);

	uint1024_t& operator-=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator-=(num_t __n);

	uint1024_t& operator*=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator*=(num_t __n);

	uint1024_t& operator/=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator/=(num_t __n);

	template <typename num_t>
   uint1024_t& operator>>=(num_t __n);

	template <typename num_t>
   uint1024_t& operator<<=(num_t __n);

	uint1024_t& operator&=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator&=(num_t __n);

	uint1024_t& operator|=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator|=(num_t __n);

	uint1024_t& operator^=(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t& operator^=(num_t __n);

	uint1024_t operator%(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator%(num_t __n);

	uint1024_t operator&(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator&(num_t __n);

	uint1024_t operator^(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator^(num_t __n);

	uint1024_t operator|(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator|(num_t __n);

	template <typename num_t>
   uint1024_t operator>>(num_t __n);

	template <typename num_t>
   uint1024_t operator<<(num_t __n);

	const uint1024_t operator-(const uint1024_t& __n)const;
	template <typename num_t>
   const uint1024_t operator-(num_t __n)const;

	uint1024_t operator+(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator+(num_t __n);

	uint1024_t operator/(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator/(num_t __n);

	uint1024_t operator*(const uint1024_t& __n);
	template <typename num_t>
   uint1024_t operator*(num_t __n);

	//member function
	uint1024_t pow(const uint1024_t& __n);
	template <typename num_t>
	uint1024_t pow(num_t __n);

	void clear_all();
};


template <typename num_t>
uint1024_t::uint1024_t(num_t __n){
	*this = __n;
}

inline std::ostream& operator<<(std::ostream& o, uint1024_t& d){
	uint8_t pos = 127;
	while(d.val[pos] == 0) {
		pos--;
		if(pos>128)break;
	}
	for(; pos < 128; pos--){
		o << ((d.val[pos]<16)?"0":"")<< std::hex << (uint16_t)d.val[pos];
	}
	return o;
}

//little endian file storage
//inline std::ofstream& operator<<(std::ofstream& o, uint1024_t& d){
	//for(uint8_t pos=0; pos<128; pos++){
	//	o << (char)d.val[pos];
	//}
	//return o;
//}
#include "uint1024_t.imp"

#endif
