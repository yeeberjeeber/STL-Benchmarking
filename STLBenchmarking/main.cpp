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
    cout << "Data array size: " << sizeof(Big) << " bytes" << endl;
    benchmark_vector_push<Big>(1000000);
    return 0;
}

