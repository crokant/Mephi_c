#pragma once

#include <vector>
#include <cstdio>

using namespace std;

void graph(const vector<size_t>& sizes, const vector<long long>& rawTimes,
               const vector<long long>& uniqueTimes, const vector<long long>& sharedTimes,
               const vector<long long>& stdSharedTimes);