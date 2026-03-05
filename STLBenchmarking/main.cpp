// STLBenchmarking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "benchmark.h"
#include <iostream>
#include <vector>

using namespace std;

struct Big {
    double data[100];

};

int main()
{
    int n = 1000000;

    //cout << "Data array size: " << sizeof(Big) << " bytes" << endl;
    benchmark_vector_push(n);

    benchmark_list_push(n);

    benchmark_deque_push(n);

    benchmark_map_push(n);

    benchmark_unorderedmap_push(n);
    return 0;
}

