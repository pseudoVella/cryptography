#include "ufp_t.h"
int main(){
	ufp_t num;

	std::cout << ~num << '\n';

	num = 2;
	//num.pow(8);
	std::cout << num.pow<int>((int)8) << '\n';
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

	num = 51;
	num /= 7;
	std::cout << num << '\n';

	num = 12;
	std::cout << num.log2() << '\n';

	std::cout << num.sqrt() << '\n';

	return 0;
}
