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

    
    benchmark_map_erase(n);

    benchmark_unorderedmap_erase(n);


    return 0;
}

