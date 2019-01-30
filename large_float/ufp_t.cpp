#include "ufp_t.h"
//constructors
ufp_t::ufp_t(){
	clear_all();
}

ufp_t::ufp_t(ufp_t& __n){
	*this = __n;
}

ufp_t::ufp_t(const ufp_t& __n){
	*this = __n;
}

//bitwise not
ufp_t ufp_t::operator~() const{
	ufp_t not_this;
	for(uint16_t b=0;b<num_bytes;b++){
		not_this.val[b] = ~val[b];
	}
	return not_this;
}

//increment
ufp_t ufp_t::operator++(int){
	ufp_t tmp(*this);
	*this += 1U;
	return tmp;
}

ufp_t& ufp_t::operator++(){
	return *this += 1U;
}

//decrement
ufp_t ufp_t::operator--(int){
	ufp_t tmp(*this);
	*this -= 1U;
	return tmp;
}

ufp_t& ufp_t::operator--(){
	return *this -= 1U;
}

//comparison operators
//equals
bool ufp_t::operator==(const ufp_t& __n) const{
	for(uint8_t pos=0; pos<num_bytes;pos++){
		if(val[pos] != __n.val[pos]) return false;
	}
	return true;
}

//not equal
bool ufp_t::operator!=(const ufp_t& __n) const{
	for(uint8_t pos=0; pos<num_bytes;pos++){
		if(val[pos] != __n.val[pos]) return true;
	}
	return false;
}

//greater or equal
bool ufp_t::operator>=(const ufp_t& __n) const{
	for(uint8_t pos = num_bytes-1; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return true;
		else if(val[pos] < __n.val[pos]) return false;
	}
	return true; //neither larger or smaller must be equal
}

//less or equal
bool ufp_t::operator<=(const ufp_t& __n) const{
	for(uint8_t pos = num_bytes-1; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return false;
		else if(val[pos] < __n.val[pos]) return true;
	}
	return true; //neither larger or smaller must be equal
}

//less than
bool ufp_t::operator<(const ufp_t& __n) const{
	for(uint8_t pos = num_bytes-1; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return false;
		else if(val[pos] < __n.val[pos]) return true;
	}
	return false; //neither larger or smaller must be equal
}

//greater than
bool ufp_t::operator>(const ufp_t& __n) const{
	for(uint8_t pos = num_bytes-1; pos < num_bytes; pos--){
		if(val[pos] > __n.val[pos]) return true;
		else if(val[pos] < __n.val[pos]) return false;
	}
	return false; //neither larger or smaller must be equal
}

//assignment operator (equals)
ufp_t& ufp_t::operator=(const ufp_t& __n){
	for(uint8_t pos=0;pos<num_bytes;pos++) val[pos]=__n.val[pos];
	return *this;
}

//addition assignment operator
ufp_t& ufp_t::operator+=(const ufp_t& __n){
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
ufp_t& ufp_t::operator-=(const ufp_t& __n){
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
ufp_t ufp_t::operator*(const ufp_t& __n) const{
	ufp_t tmp;
	for(uint16_t pos=0;pos<num_bits;pos++){
		if(checkbit(__n.val,pos)) tmp+=(*this<<pos);
	}
	return (tmp>>bit_offset);
}

//division operator
ufp_t ufp_t::operator/(const ufp_t& __n) const{
	ufp_t quo;
	ufp_t rem;
	uint64_t frac=0;
	uint16_t pos;
	for(pos=num_bits-1;pos>=bit_offset;pos--){
		if(checkbit(val, pos)) rem |= 1;
		if(rem >= __n){
			rem -= __n;
			quo |= 1;
		}
		quo <<= 1U;
		rem <<= 1U;
	}
	quo>>=1U;
  for(pos=bit_offset-1;pos<bit_offset;pos--){
    if(checkbit(val,pos)) rem |= 1U;
    if(rem >= __n){
      frac |= 1U;
      rem -= __n;
    }
    frac <<= 1;
    rem <<= 1;
  }
  frac>>=1;
  for(pos=0;pos<byte_offset;pos++){
    quo.val[pos]=((frac>>(pos<<3))&0xFF);
  }
	return quo;
}

//binary AND assignment operator
ufp_t& ufp_t::operator&=(const ufp_t& __n){
	for(uint8_t pos=0;pos<num_bytes;pos++) val[pos]&=__n.val[pos];
	return *this;
}

//binary OR assignment operator
ufp_t& ufp_t::operator|=(const ufp_t& __n){
	for(uint8_t pos=0;pos<num_bytes;pos++) val[pos] |= __n.val[pos];
	return *this;
}

//binary XOR assignment operator
ufp_t& ufp_t::operator^=(const ufp_t& __n){
	for(uint8_t pos=0;pos<num_bytes;pos++) val[pos] ^= __n.val[pos];
	return *this;
}

//binary AND operator
ufp_t ufp_t::operator&(const ufp_t& __n) const{
	ufp_t res;
	for(uint8_t pos=0;pos<num_bytes;pos++){
		res.val[pos] = val[pos] & __n.val[pos];
	}
	return res;
}

//binary XOR operator
ufp_t ufp_t::operator^(const ufp_t& __n) const{
	ufp_t res;
	for(uint8_t pos=0;pos<num_bytes;pos++){
		res.val[pos] = val[pos] ^ __n.val[pos];
	}
	return res;
}

//binary OR operator
ufp_t ufp_t::operator|(const ufp_t& __n) const{
	ufp_t res;
	for(uint8_t pos=0;pos<num_bytes;pos++){
		res.val[pos] = val[pos] | __n.val[pos];
	}
	return res;
}

//subtraction operator
ufp_t ufp_t::operator-(const ufp_t& __n) const{
	ufp_t res(*this);
	res -= __n;
	return res;
}

//addition operator
ufp_t ufp_t::operator+(const ufp_t& __n) const{
	ufp_t res(*this);
	res += __n;
	return res;
}

//division assignment operator
ufp_t& ufp_t::operator/=(const ufp_t& __n){
	*this =	*this / __n;
	return *this;
}

//multiplication operator;
ufp_t& ufp_t::operator*=(const ufp_t& __n){
	(*this) = (*this) * __n;
	return (*this);
}

//modulo operator
ufp_t ufp_t::operator%(const ufp_t& __n) const{
	ufp_t res;
	res = *this & (__n-1U);
	return res;
}

ufp_t& ufp_t::operator%=(const ufp_t& __n){
	*this &= (__n-1);
	return *this;
}

//member functions
//exponentiation
ufp_t ufp_t::pow(ufp_t __n) const{
	ufp_t res = 1, tmp(*this);
	uint16_t pos;
	uint64_t root;
	bool rational = false;
	//check for rational exponent
	for(pos=0;pos<bit_offset;pos++){
		if(checkbit(__n.val,pos)){
			rational = true;
			//turn rational exponent into a fraction
			root = 1<<(bit_offset-pos);
			__n <<= bit_offset-pos;
			break;
		}
	}
	//if rational exp. need to take nth root of base
	if(rational) tmp = tmp.rootn<uint64_t>(root);
	//square and multiply
	for(pos = bit_offset; pos < num_bits; pos++){
		if(checkbit(__n.val, pos)){
			res *= tmp;
		}
		tmp *= tmp;
	}
	return res;
}

ufp_t ufp_t::log2() const{
	uint16_t pos = num_bits-1;
	while(checkbit(val, pos)==0){
		pos--;
	}
	ufp_t tmp = *this;
	tmp >>= pos-bit_offset;
	ufp_t res = pos-bit_offset;
	for(pos=bit_offset;pos<57;){
		while(tmp<=2){
			tmp *= tmp;
			pos--;
			if(pos>bit_offset) break;
		}
		if(pos>bit_offset) break;
		sbit(res.val,pos);
		tmp>>=1;
	}
	return res;
}

ufp_t ufp_t::sqrt() const{
	ufp_t napprox=(*this)>>1;
	ufp_t approx, fx, dx;
	while(napprox != approx){
		approx = napprox;
		fx = approx*approx;
		fx -= *this;
		dx = approx<<1;
		napprox -= fx/dx;
	}
	return approx;
}

ufp_t ufp_t::rootn(ufp_t __n) const{
	ufp_t napprox(*this);
	ufp_t approx, fx, dx;
	bool rational = false;
	uint64_t P;
	//check for rational root
	for(uint8_t pos=0;pos<bit_offset;pos++){
		if(checkbit(__n.val,pos)){
			rational = true;
			//turn rational root into a fraction
			P = 1<<(bit_offset-pos);
			__n <<= bit_offset-pos;
			break;
		}
	}
	napprox /= __n;
	while(napprox != approx){
		approx = napprox;
		fx = approx.pow(__n);
		fx -= *this;
		dx = approx.pow(__n-1);
		dx *= __n;
		napprox -= fx/dx;
	}

	if(rational) return approx.pow<uint64_t>(P);
	else return approx;
}

void ufp_t::clear_all(){
	for(uint8_t pos=0; pos<num_bytes; pos++) val[pos]=0;
}
