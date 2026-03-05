#include "benchmark.h"
#include <iostream>
#include <chrono>
#include <map>
using namespace std;

void benchmark_map_push(int n) {
	map<int, int> mp;
	
	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		mp[i] = n;
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Map push time: " << elapsed.count() << " seconds." << endl;
}