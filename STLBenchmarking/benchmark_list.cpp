#include "benchmark.h"
#include <iostream>
#include <list>
#include <chrono>
using namespace std;

void benchmark_list_access(int n) {
	list<int> lst(n, 1);
	volatile long long sum = 0;
	vector<int> indices(n);
	for (int i = 0; i < n; i++) {
		indices[i] = rand() % lst.size();
	}

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		//lst.push_back(n);
		auto it = lst.begin();
		advance(it, indices[i]);
		sum += *it;
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "List random access time: " << elapsed.count() << " seconds." << endl;
}

void benchmark_list_push(int n) {
	list<int> lst;

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		lst.push_back(n);
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "List random access time: " << elapsed.count() << " seconds." << endl;
}