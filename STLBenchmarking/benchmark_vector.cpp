#include "benchmark.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void benchmark_vector_push(int N) {
	vector<int> vec; // capacity starts with 0
	vec.reserve(N);

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++) {
		vec.push_back(i);
	}
	
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Vector push time: " << elapsed.count() << " seconds." << endl;
}

