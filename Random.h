#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "Time.h"

using namespace std;

class Random {

    private:
    vector<int> solution;
    Time time_utilities;
    vector<double> time_records;
    vector<int> cost_records;
    vector<int> absolute_errors;
    vector<double> relative_errors;
    double time_mean;
    double absolute_error_mean, relative_error_mean;
    void doRandom(int number_vertices, vector<vector<int>> edges, int optCost, int limit);
    int calcCost(vector<int> permutation, int number_vertices, vector<vector<int>> edges);

    public:
    Random();
    void testRandom(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int time_limit);
    bool saveResults(string out_file, string in_file, int optCost);


};