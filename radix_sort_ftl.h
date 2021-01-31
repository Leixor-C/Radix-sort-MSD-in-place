#pragma once
namespace leixor {
	//we write the mod pow 2 to avoid idv instruccion of the compiler
	static constexpr size_t modpow2(size_t& num, size_t& mod_pow2) {
		return num - (num >> mod_pow2 << mod_pow2);
	}
	static constexpr size_t modpow2(size_t& num, size_t mod_pow2) {
		return num - (num >> mod_pow2 << mod_pow2);
	}
	static constexpr size_t modpow2(size_t num, size_t mod_pow2) {
		return num - (num >> mod_pow2 << mod_pow2);
	}
	//fast log in power of 2
	static size_t& logb_pow2(size_t num, const size_t& base_pow2) {
		size_t aux = 1;
		if (base_pow2 == 0) return aux = -1;
		while (0 < (num >>= base_pow2))
			aux++;
		return aux;
	}
	//------------------------obj version---------------------------
	//custom get_max because i don't wanna add lib,and normaly we will use this in a custom class
	template<class obj_arr>
	static size_t& get_max(obj_arr*& arr, const size_t& size) {

		size_t i = modpow2(size, 1), aux = arr[0].get_size_t(), aux2;
		for (; i < size; i += 2) {
			aux2 = arr[i].get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
			aux2 = arr[i + 1].get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
		}
		return aux;
	}


	
	template<class obj_arr>
	void countrad(
		size_t depth,
		obj_arr*& arr,
		size_t*& count_control, size_t**& counts, size_t& mod_pow2,
		size_t start, size_t finish
	) {
		size_t i;
		static size_t move;
		static obj_arr auxiliar;
		depth--;
		for (i = start; i < finish; i++) {
			count_control[modpow2(arr[i].get_size_t() >> (depth * mod_pow2), mod_pow2)]++;
		}
		counts[depth][0] = start;
		for (i = 1; i < 1 << mod_pow2; i++) {
			counts[depth][i] = counts[depth][i - 1] + count_control[i - 1];
		}

		for (i = 0; i < 1 << mod_pow2; i++) {
			while (count_control[i] > 0) {
				auxiliar = arr[counts[depth][i] + count_control[i] - 1];
				move = modpow2(auxiliar.get_size_t() >> (depth * mod_pow2), mod_pow2);
				arr[counts[depth][i] + count_control[i] - 1] = arr[counts[depth][move] + count_control[move] - 1];
				arr[counts[depth][move] + count_control[move] - 1] = auxiliar;
				count_control[move]--;
			}
		}

		if (depth > 0) {
			start = counts[depth][(1 << mod_pow2) - 1];
			countrad(depth, arr, count_control, counts, mod_pow2, start, finish);
			for (i = 0; i < (1 << mod_pow2) - 1; i++) {
				start = counts[depth][i];
				finish = counts[depth][i + 1];
				countrad(depth, arr, count_control, counts, mod_pow2, start, finish);
			}
		}

	}

	template<class obj_arr>
	bool radix_sort_ftl(obj_arr* arr, size_t size, size_t mod_pow2 = 4) {
		if (mod_pow2 == 0 || size < 2)
			return false;
		size_t max = get_max(arr, size), start = 0, finish = size;
		const size_t num_count = logb_pow2(max, mod_pow2);
		//we use count_control so we don't need a axiliar memory the same size as arr
		size_t* count_control = new size_t[1 << mod_pow2];
		for (size_t i = 0; i < 1 << mod_pow2; i++)
			count_control[i] = 0;
		//------------------
		size_t** counts = new size_t * [num_count];
		for (size_t i = 0; i < num_count; i++) {
			counts[i] = new size_t[1 << mod_pow2];
		}

		countrad(num_count, arr, count_control, counts, mod_pow2, start, finish);

		delete[] count_control;

		for (size_t i = 0; i < num_count; i++)
			delete[] counts[i];
		delete[]counts;

		return true;
	}
	//----------------------------pointer obj version---------------------
	template<class obj_arr>
	static size_t& get_max(obj_arr**& arr, const size_t& size) {

		size_t i = modpow2(size, 1), aux = arr[0]->get_size_t(), aux2;
		for (; i < size; i += 2) {
			aux2 = arr[i]->get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
			aux2 = arr[i + 1]->get_size_t();
			aux = aux2 * (aux < aux2) + aux * (aux >= aux2);
		}
		return aux;
	}



	template<class obj_arr>
	void countrad(
		size_t depth,
		obj_arr**& arr,
		size_t*& count_control, size_t**& counts, size_t& mod_pow2,
		size_t start, size_t finish
	) {
		size_t i;
		static size_t move;
		static obj_arr* auxiliar;
		depth--;
		for (i = start; i < finish; i++) {
			count_control[modpow2(arr[i]->get_size_t() >> (depth * mod_pow2), mod_pow2)]++;
		}
		counts[depth][0] = start;
		for (i = 1; i < 1 << mod_pow2; i++) {
			counts[depth][i] = counts[depth][i - 1] + count_control[i - 1];
		}

		for (i = 0; i < 1 << mod_pow2; i++) {
			while (count_control[i] > 0) {
				auxiliar = arr[counts[depth][i] + count_control[i] - 1];
				move = modpow2(auxiliar->get_size_t() >> (depth * mod_pow2), mod_pow2);
				arr[counts[depth][i] + count_control[i] - 1] = arr[counts[depth][move] + count_control[move] - 1];
				arr[counts[depth][move] + count_control[move] - 1] = auxiliar;
				count_control[move]--;
			}
		}

		if (depth > 0) {
			start = counts[depth][(1 << mod_pow2) - 1];
			countrad(depth, arr, count_control, counts, mod_pow2, start, finish);
			for (i = 0; i < (1 << mod_pow2) - 1; i++) {
				start = counts[depth][i];
				finish = counts[depth][i + 1];
				countrad(depth, arr, count_control, counts, mod_pow2, start, finish);
			}
		}

	}

	template<class obj_arr>
	bool radix_sort_ftl(obj_arr** arr, size_t size, size_t mod_pow2 = 4) {
		if (mod_pow2 == 0 || size < 2)
			return false;
		size_t max = get_max(arr, size), start = 0, finish = size;
		const size_t num_count = logb_pow2(max, mod_pow2);
		//we use count_control so we don't need a axiliar memory the same size as arr
		size_t* count_control = new size_t[1 << mod_pow2];
		for (size_t i = 0; i < 1 << mod_pow2; i++)
			count_control[i] = 0;
		//------------------
		size_t** counts = new size_t * [num_count];
		for (size_t i = 0; i < num_count; i++) {
			counts[i] = new size_t[1 << mod_pow2];
		}

		countrad(num_count, arr, count_control, counts, mod_pow2, start, finish);

		delete[] count_control;

		for (size_t i = 0; i < num_count; i++)
			delete[] counts[i];
		delete[]counts;

		return true;
	}

}

