#include "pch.h"
#include <iostream>
#include <vector>
#include "Thread_guard.h"

void scalar_product(std::vector<int>& result, int pos, std::vector<int>& u, std::vector<int>& v, int num, int len){
	int sum_pros = 0;
	for (int i = 0; i < len; ++i) {
		if (u.size() <= i + num) break;
			sum_pros += u[i + num] * v[i + num];
	}
	result[pos] = sum_pros;
}

int main(){
	setlocale(LC_ALL, "Russian");
	std::vector<int> u, v;
	int n;
	std::cout << "Введите длину вектора: ";
	std::cin >> n;
	u.reserve(n);
	v.reserve(n);

	int data;
	std::cout << "Введите первый вектор: " << "\n";
	for (int i = 0; i < n; i++){
		std::cin >> data;
		u.push_back(data);
	}

	std::cout << "\n" << "Введите второй вектор: " << "\n";
	for (int i = 0; i < n; ++i){
		std::cin >> data;
		v.push_back(data);
	}

	Thread_guard sentinel;
	int hard_conc = sentinel.hardware_concurrency();
	int amount_of_threads;
	if (hard_conc > n)
		amount_of_threads = n;
	else
		amount_of_threads = hard_conc; 
	std::vector<int> result(amount_of_threads);
	int step = n / amount_of_threads;
	if (n % amount_of_threads != 0)
		step++;
	for (int i = 0, j = 0; i < n; i += step, j++)
		sentinel.add_thread(std::thread(scalar_product, std::ref(result), j, std::ref(u), std::ref(v), i, step));

	sentinel.join();

	int col_result = result.size();
	int answer = 0;
	for (int i = 0; i < col_result; ++i)
		answer += result[i];
	std::cout << "\n" << answer << "\n";

	system("pause");
	return 0;
}