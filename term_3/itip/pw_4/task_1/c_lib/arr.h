#pragma once
#include <iostream>

#define READ_ONLY_FLAG 1

using namespace std;

extern "C" int countElments(int *arr, int len);
extern "C" int *inputIntArray(int len);
extern "C" void outputIntArray(int *arr, int len);
