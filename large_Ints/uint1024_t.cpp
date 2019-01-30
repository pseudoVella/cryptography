#include "uint1024_t.h"
//constructors
uint1024_t::uint1024_t(){
	clear_all();
}

uint1024_t::uint1024_t(uint1024_t& __n){
	*this = __n;
}

uint1024_t::uint1024_t(const uint1024_t& __n){
	*this = __n;
}

//comparison operators
//equals
bool uint1024_t::operator==(const uint1024_t& __n){
	for(uint8_t pos=0; pos<num_bytes;pos++){
		if(val[pos] != __n.val[pos]) return false;
	}
	return true;
}

//greater or equal
bool uint1024_t::operator>=(const uint1024_t& __n){
	for(uint8_t pos = 127; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return true;
		else if(val[pos] < __n.val[pos]) return false;
	}
	return true; //neither larger or smaller must be equal
}

//less or equal
bool uint1024_t::operator<=(const uint1024_t& __n){
	for(uint8_t pos = 127; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return false;
		else if(val[pos] < __n.val[pos]) return true;
	}
	return true; //neither larger or smaller must be equal
}

//less than
bool uint1024_t::operator<(const uint1024_t& __n){
	for(uint8_t pos = 127; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return false;
		else if(val[pos] < __n.val[pos]) return true;
	}
	return false; //neither larger or smaller must be equal
}

//greater than
bool uint1024_t::operator>(const uint1024_t& __n){
	for(uint8_t pos = 127; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return true;
		else if(val[pos] < __n.val[pos]) return false;
	}
	return false; //neither larger or smaller must be equal
}

//assignment operator (equals)
uint1024_t& uint1024_t::operator=(const uint1024_t& __n){
	for(uint8_t pos = 0; pos < num_bytes; pos++) val[pos] = __n.val[pos];
	return *this;
}

//addition assignment operator
uint1024_t& uint1024_t::operator+=(const uint1024_t& __n){
	uint16_t tpos;
	for(uint16_t pos = 0; pos < num_bits; pos++){
		if(checkbit(__n.val,pos)){
			tpos = pos;
			while(checkbit(val, tpos)){
				cbit(val, tpos);
				tpos++;
			}
			sbit(val, tpos);
		}
	}
	return *this;
}

//subtraction assignment operator
uint1024_t& uint1024_t::operator-=(const uint1024_t& __n){
	uint16_t tpos;
	for(uint16_t pos = 0; pos < num_bits; pos++){
		if(checkbit(__n.val,pos)){
			tpos = pos;
			while(checkbit(val, tpos)==0){
				sbit(val, tpos);
				tpos++;
			}
			cbit(val, tpos);
		}
	}
	return *this;
}

//multiplication operator
uint1024_t uint1024_t::operator*(const uint1024_t& __n){
	uint1024_t tmp;
	for(uint16_t pos = 0; pos < num_bits; pos++){
		if(checkbit(__n.val, pos)) tmp += (*this << pos);
	}
	return tmp;
}

//division operator
uint1024_t uint1024_t::operator/(const uint1024_t& __n){
	uint1024_t quo;
	uint1024_t rem;
	for(uint16_t pos = num_bits-1; pos<num_bits; pos--){
		if(checkbit(val, pos)) rem |= 1;
		if(rem >= __n){
			rem -= __n;
			quo |= 1;
		}
		quo <<= 1U;
		rem <<= 1U;
	}
	return (quo >> 1U);
}

//binary AND assignment operator
uint1024_t& uint1024_t::operator&=(const uint1024_t& __n){
	for(uint8_t pos=0; pos<num_bytes;pos++) val[pos] &= __n.val[pos];
	return *this;
}

//binary OR assignment operator
uint1024_t& uint1024_t::operator|=(const uint1024_t& __n){
	for(uint8_t pos=0;pos<num_bytes;pos++) val[pos] |= __n.val[pos];
	return *this;
}

//binary XOR assignment operator
uint1024_t& uint1024_t::operator^=(const uint1024_t& __n){
	for(uint8_t pos=0;pos<num_bytes;pos++) val[pos] ^= __n.val[pos];
	return *this;
}

//binary AND operator
uint1024_t uint1024_t::operator&(const uint1024_t& __n){
	uint1024_t res;
	for(uint8_t pos=0;pos<num_bytes;pos++){
		res.val[pos] = val[pos] & __n.val[pos];
	}
	return res;
}

//binary XOR operator
uint1024_t uint1024_t::operator^(const uint1024_t& __n){
	uint1024_t res;
	for(uint8_t pos=0;pos<num_bytes;pos++){
		res.val[pos] = val[pos] ^ __n.val[pos];
	}
	return res;
}

//binary OR operator
uint1024_t uint1024_t::operator|(const uint1024_t& __n){
	uint1024_t res;
	for(uint8_t pos=0;pos<num_bytes;pos++){
		res.val[pos] = val[pos] | __n.val[pos];
	}
	return res;
}

//subtraction operator
const uint1024_t uint1024_t::operator-(const uint1024_t& __n)const{
	uint1024_t res(*this);
	res -= __n;
	return res;
}

//addition operator
uint1024_t uint1024_t::operator+(const uint1024_t& __n){
	uint1024_t res = *this;
	res += __n;
	return res;
}

//division assignment operator
uint1024_t& uint1024_t::operator/=(const uint1024_t& __n){
	*this =	*this / __n;
	return *this;
}

//multiplication operator;
uint1024_t& uint1024_t::operator*=(const uint1024_t& __n){
	*this = *this * __n;
	return *this;
}

//modulo operator
uint1024_t uint1024_t::operator%(const uint1024_t& __n){
	uint1024_t res;
	res = *this & (__n-1U);
	return res;
}

//member functions
uint1024_t uint1024_t::pow(const uint1024_t& __n){
	uint1024_t res(1), tmp(*this);
	for(uint16_t pos = 0; pos < num_bits; pos++){
		if(checkbit(__n.val, pos)){
			res *= tmp;
		}
		tmp *= tmp;
	}
	return res;
}

void uint1024_t::clear_all(){
	for(uint8_t pos=0; pos<num_bytes; pos++) val[pos]=0;
}
