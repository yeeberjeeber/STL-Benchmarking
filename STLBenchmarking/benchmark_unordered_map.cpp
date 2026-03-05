#include "benchmark.h"
#include <iostream>
#include <chrono>
#include <unordered_map>
using namespace std;

void benchmark_unorderedmap_push(int n) {
	unordered_map<int, int> mp;

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		mp[i] = n;
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;

	cout << "Unordered map push time: " << elapsed.count() << " seconds." << endl;
}