#pragma once
#include <vector>
#include <chrono>
#include <iostream>

template <typename T>
void benchmark_vector_push(int N) {
    std::vector<T> vec;
    vec.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i)
        vec.push_back(T{});
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Vector push time: " << elapsed.count() << " seconds;" << std::endl;
}