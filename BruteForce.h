#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
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
    void doBF(int number_vertices, vector<vector<int>> edges);
    // Calculates cost of given permutation
    int calcCost(vector<int> permutation, int number_vertices, vector<vector<int>> edges);


    public:
    BruteForce();
    // Method used in tests of the Brute-Force algorithm
    void testBF(int number_vertices, vector<vector<int>> edges, int repeats);
    bool saveResults(string out_file, string in_file, int optCost);


};