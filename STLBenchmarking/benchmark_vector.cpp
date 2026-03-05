#include "benchmark.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void benchmark_vector_access(int N) {
	vector<int> vec(N, 1); // capacity starts with 0
	//vec.reserve(N);
	volatile long long sum = 0;

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++) {
		// vec.push_back(i);
		int index = rand() % vec.size();
		sum += vec[index];
	}
	
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Vector random access time: " << elapsed.count() << " seconds." << endl;
}

void benchmark_vector_push(int N) {
	vector<int> vec; // capacity starts with 0
	vec.reserve(N);

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++) {
		vec.push_back(i);
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Vector random access time: " << elapsed.count() << " seconds." << endl;
}