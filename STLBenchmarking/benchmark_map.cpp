#include "benchmark.h"
#include <iostream>
#include <chrono>
#include <map>
using namespace std;

void benchmark_map_erase(int n) {
	map<int, int> mp;
	volatile long long sum = 0;

	for (int i = 0; i < n; i++) {
		mp[i] = n;
	}

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		int index = rand() % n; // generates random number between 0 and n-1
		mp.erase(index);
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Map erase time: " << elapsed.count() << " seconds." << endl;
}

void benchmark_map_access(int n) {
	map<int, int> mp;
	volatile long long sum = 0;

	for (int i = 0; i < n; i++) {
		mp[i] = n;
	}

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		int index = rand() % n; // generates random number between 0 and n-1
		auto it = mp.find(index); 
		sum += it->second; // retrieving value stored in key
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Map random access time: " << elapsed.count() << " seconds." << endl;
}

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