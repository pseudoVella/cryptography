#include "uint1024_t.h"
int main(){
	uint1024_t num;
	//num = ;
	num -= 1;//num.pow(8);
	std::cout << num << '\n';
	num = 16;
	//multiplication
	num *= 320;
	std::cout << num << '\n';
	std::cout << std::hex << 5120 << '\n';
	//division
	num /= 16;
	std::cout << num << '\n';
	std::cout << std::hex << 320 << '\n';

	uint64_t x = -1;
	num *= x;
	std::cout << num << '\n';
	return 0;
}
