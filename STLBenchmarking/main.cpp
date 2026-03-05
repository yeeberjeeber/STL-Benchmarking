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
    int n = 10000;

    
    benchmark_vector_push(n);

    benchmark_list_push(n);

    benchmark_deque_push(n);


    return 0;
}

