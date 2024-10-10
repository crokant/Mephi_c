#include "Graph.h"
#include <vector>
#include <cstdio>

using namespace std;

void sendDataToGnuplot(FILE* gnuplotPipe, const vector<size_t>& sizes, const vector<long long>& times) {
    for (size_t i = 0; i < sizes.size(); ++i) {
        fprintf(gnuplotPipe, "%zu %lld\n", sizes[i], times[i]);
    }
    fprintf(gnuplotPipe, "e\n");
}

void graph(const vector<size_t>& sizes, const vector<long long>& rawTimes,
           const vector<long long>& uniqueTimes, const vector<long long>& sharedTimes,
           const vector<long long>& stdSharedTimes) {

    FILE *gnuplotPipe = popen("gnuplot -p", "w");
    fprintf(gnuplotPipe, "set title 'Performance Test Results'\n");
    fprintf(gnuplotPipe, "set xlabel 'Number of Elements (N)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time (microseconds)'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set logscale x\n");
    fprintf(gnuplotPipe, "set logscale y\n");
    fprintf(gnuplotPipe, "set key left top\n");

    fprintf(gnuplotPipe, "plot '-' with linespoints title 'Raw Pointer', "
                         "'-' with linespoints title 'Unique Pointer', "
                         "'-' with linespoints title 'Shared Pointer', "
                         "'-' with linespoints title 'std::shared_ptr'\n");

    sendDataToGnuplot(gnuplotPipe, sizes, rawTimes);
    sendDataToGnuplot(gnuplotPipe, sizes, uniqueTimes);
    sendDataToGnuplot(gnuplotPipe, sizes, sharedTimes);
    sendDataToGnuplot(gnuplotPipe, sizes, stdSharedTimes);
    pclose(gnuplotPipe);
}
