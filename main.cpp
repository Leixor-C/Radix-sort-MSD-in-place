#include "radix_sort_ftl.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>   
#include <iostream>
#include <chrono>
#include<string>
#include <array>
#include <math.h>
class data
{
public:
	data() {};
	size_t& get_size_t() { return m; };
	void operator = (data& T) { m = T.m; };
	size_t m;
};
void object_version(const size_t pow10,const size_t pow2,const size_t mod_pow2) {
	size_t size = pow(10,pow10);
	data* arr = new data[size];
	size_t mod = 1 << (2+pow2);

	for (size_t i = 0; i < size; i++) {

		arr[i].m = rand() % mod;
	}


	auto started = std::chrono::high_resolution_clock::now();
	leixor::radix_sort_ftl(arr, size,mod_pow2);
	auto done = std::chrono::high_resolution_clock::now();

	std::cout<<"|" << float(std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count()) / float(1000000);

	delete[] arr;

};
void pointer_object_version(const size_t pow10, const size_t pow2, const size_t mod_pow2) {
	size_t size = pow(10, pow10);
	data** arr = new data*[size];
	size_t mod = 1 << (2 + pow2);

	for (size_t i = 0; i < size; i++) {
		arr[i] = new data();
		arr[i]->m = rand() % mod;
	}


	auto started = std::chrono::high_resolution_clock::now();
	leixor::radix_sort_ftl(arr, size, mod_pow2);
	auto done = std::chrono::high_resolution_clock::now();

	std::cout << "|" << float(std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count()) / float(1000000);

	for (size_t i = 0; i < size; i++) {
		delete arr[i];
	}

	delete[] arr;

};
int main() {
	srand(time(NULL));
	std::cout << 
		"\n      --------------------------------------------------"<<
		"\n      ----------------object oriented version-----------"<<
		"\n      --------------------------------------------------\n\n";
	std::array<std::string, 5> alfa = { "\nmax|2 ","\nnum|3 ","\npow|4 ","\n   |5 ","\n2  |6 " };
	for (size_t mod_pow2 = 2; mod_pow2 < 6; mod_pow2++){
		std::cout << 
			"\n      ------------------size mod of "<< size_t(1<<mod_pow2)<<" ------------------";
	
		std::cout <<
			"\n      ---------------------size pow 10------------------" <<
			"\n      --------------------------------------------------" <<
			"\n      |  1   | 2    |    3 |    4 |    5 |    6 |    7 |";

		for (size_t z = 0; z < 5; z++) {
			std::cout << "\n      --------------------------------------------------"<<
				alfa[z];

			for (size_t i = 1; i < 8; i++){
				object_version(i,z,mod_pow2);
			}
		}
		std::cout << "\n      --------------------------------------------------\n";
	}
	std::cout <<
		"\n      --------------------------------------------------" <<
		"\n      ----------------pointer oriented version-----------" <<
		"\n      --------------------------------------------------\n\n";
	for (size_t mod_pow2 = 2; mod_pow2 < 6; mod_pow2++) {
		std::cout <<
			"\n      ------------------size mod of " << size_t(1 << mod_pow2) << " ------------------";

		std::cout <<
			"\n      ---------------------size pow 10------------------" <<
			"\n      --------------------------------------------------" <<
			"\n      |  1   | 2    |    3 |    4 |    5 |    6 |    7 |";

		for (size_t z = 0; z < 5; z++) {
			std::cout << "\n      --------------------------------------------------" <<
				alfa[z];

			for (size_t i = 1; i < 8; i++) {
				pointer_object_version(i, z, mod_pow2);
			}
		}
		std::cout << "\n      --------------------------------------------------\n";
	}

}