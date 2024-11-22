#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include "Time.h"

using namespace std;

class BruteForce {

    private:
    int minCost;
    vector<int> solution;
    Time time_utilities;
    vector<double> time_records;
    double mean;
    // Executes the Brute-Force algorithm
    bool doBF(int number_vertices, vector<vector<int>> edges, int optCost, int limit);
    // Calculates cost of given permutation
    int calcCost(vector<int> permutation, int number_vertices, vector<vector<int>> edges);


    public:
    BruteForce();
    // Method used in tests of the Brute-Force algorithm
    bool testBF(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int time_limit);
    bool saveResults(string out_file, string in_file, int optCost);


};