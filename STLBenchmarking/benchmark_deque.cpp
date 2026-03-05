#include "benchmark.h"
#include <iostream>
#include <chrono>
#include <deque>
using namespace std;

void benchmark_deque_access(int n) {
	deque<int> deck(n, 1);
	volatile long long sum = 0;
	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		//deck.push_back(n);
		int index = rand() % deck.size();
		sum += deck[index];
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Deque random access time: " << elapsed.count() << " seconds." << endl;
}

void benchmark_deque_push(int n) {
	deque<int> deck;
	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++) {
		deck.push_back(n);
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	cout << "Deque push time: " << elapsed.count() << " seconds." << endl;
}