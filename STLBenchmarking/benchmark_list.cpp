#include "benchmark.h"
#include <iostream>
#include <list>
#include <chrono>
using namespace std;

void benchmark_list_push(int n) {
	list<int> lst;
	
	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		lst.push_back(n);
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "List push time: " << elapsed.count() << " seconds." << endl;
}