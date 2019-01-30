#ifndef ufp_t_h
#define ufp_t_h
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

class ufp_t {

private:
	static const uint8_t num_bytes = 135;
	static const uint16_t num_bits = 1080;
	static const uint8_t byte_offset = 7;
	static const uint8_t bit_offset = 56;

public:
//constructors
  ufp_t();

  ufp_t(ufp_t& __n);
  ufp_t(const ufp_t& __n);

	template <typename num_t>
  ufp_t(num_t __n);

 //array to hold extremely large 1024bit number
 //with an extra 7 bytes of decimal precision
	uint8_t val[num_bytes];

	//operators
	bool operator==(const ufp_t& __n) const;
	template <typename num_t>
	bool operator==(const num_t& __n) const;

	bool operator!=(const ufp_t& __n) const;
	template <typename num_t>
	bool operator!=(const num_t& __n) const;

	bool operator>=(const ufp_t& __n) const;
	template <typename num_t>
	bool operator>=(const num_t& __n) const;

	bool operator<=(const ufp_t& __n) const;
	template <typename num_t>
	bool operator<=(const num_t& __n) const;

	bool operator>(const ufp_t& __n) const;
	template <typename num_t>
	bool operator>(const num_t& __n) const;

	bool operator<(const ufp_t& __n) const;
	template <typename num_t>
	bool operator<(const num_t& __n) const;

	ufp_t operator~() const;

	ufp_t& operator++();
	ufp_t& operator--();

	ufp_t operator++(int);
	ufp_t operator--(int);

	ufp_t& operator=(const ufp_t& __n);
	template <typename num_t>
	ufp_t& operator=(const num_t& __n);

	ufp_t& operator+=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator+=(num_t __n);

	ufp_t& operator-=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator-=(num_t __n);

	ufp_t& operator*=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator*=(num_t __n);

	ufp_t& operator/=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator/=(const num_t& __n);

	template <typename num_t>
  ufp_t& operator>>=(const num_t& __n);

	template <typename num_t>
  ufp_t& operator<<=(const num_t& __n);

	ufp_t& operator&=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator&=(const num_t& __n);

	ufp_t& operator|=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator|=(const num_t& __n);

	ufp_t& operator^=(const ufp_t& __n);
	template <typename num_t>
  ufp_t& operator^=(const num_t& __n);

	ufp_t operator%(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator%(const num_t& __n) const;

	ufp_t& operator%=(const ufp_t& __n);
	template <typename num_t>
	ufp_t& operator%=(const num_t& __n);

	ufp_t operator&(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator&(const num_t& __n) const;

	ufp_t operator^(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator^(const num_t& __n) const;

	ufp_t operator|(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator|(const num_t& __n) const;

	template <typename num_t>
  ufp_t operator>>(const num_t& __n)const;

	template <typename num_t>
  ufp_t operator<<(const num_t& __n)const;

	ufp_t operator-(const ufp_t& __n)const;
	template <typename num_t>
  ufp_t operator-(num_t __n)const;

	ufp_t operator+(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator+(num_t __n) const;

	ufp_t operator/(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator/(const num_t& __n) const;

	ufp_t operator*(const ufp_t& __n) const;
	template <typename num_t>
  ufp_t operator*(num_t __n) const;

	//member function
	ufp_t pow(ufp_t __n)const;
	template <typename num_t>
	ufp_t pow(num_t __n)const;

	ufp_t log2()const;

	ufp_t sqrt()const;

	ufp_t rootn(ufp_t __n) const;
	template<typename num_t>
	ufp_t rootn(const num_t& __n)const;

	void clear_all();
};


template <typename num_t>
ufp_t::ufp_t(num_t __n){
	*this = __n;
}

inline std::ostream& operator<<(std::ostream& o, const ufp_t& d){
	uint8_t pos = 134,lpos;
	bool more=false;
	while(d.val[pos] == 0) {
		pos--;
		if(pos<7)break;
	}
	for(; pos > 6; pos--){
		o << ((d.val[pos]<16)?"0":"")<< std::hex << (uint16_t)d.val[pos];
	}
	for(lpos=0;lpos<7;lpos++){
		if(d.val[lpos]){
			more=true;
			break;
		}
	}
	if(more){
		o << '.';
		for(;pos<7 && pos>=lpos;pos--){
			o << ((d.val[pos]<16)?"0":"")<< std::hex << (uint16_t)d.val[pos];
		}
	}
	return o;
}


/*inline std::ofstream& operator<<(std::ofstream& o, 
const ufp_t& d){
	uint8_t pos = 134,lpos;
	bool more=false;
	while(d.val[pos] == 0) {
		pos--;
		if(pos<7)break;
	}
	for(; pos > 6; pos--){
		o << ((d.val[pos]<16)?"0":"")<< std::hex << (uint16_t)d.val[pos];
	}
	for(lpos=0;lpos<7;lpos++){
		if(d.val[lpos]){
			more=true;
			break;
		}
	}
	if(more){
		o << '.';
		for(;pos<7;pos--){
			o << ((d.val[pos]<16)?"0":"")<< std::hex << (uint16_t)d.val[pos];
		}
	}
	return o;
}
*/
//little endian file storage
inline std::ofstream& operator<<(std::ofstream& o, const ufp_t& d){
	for(uint8_t pos=0; pos<134; pos++){
		o << (char)d.val[pos];
	}
	return o;
}
#include "ufp_t.imp"

#endif
