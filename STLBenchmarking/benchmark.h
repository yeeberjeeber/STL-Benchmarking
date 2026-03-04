#pragma once
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

// template is a blueprint to make a function for any type T
template <typename T>
void benchmark_vector_push(int N) {
    vector<T> vec;
    vec.reserve(N);

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i)
        vec.push_back(T{}); // initializing T to 0, pushing an array of doubles of size 100 into vector
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Vector push time: " << elapsed.count() << " seconds;" << std::endl;
}