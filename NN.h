#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Time.h"

using namespace std;

class NN {

    private:
    vector<int> solution;
    Time time_utilities;
    vector<double> time_records;
    vector<int> cost_records;
    vector<int> absolute_errors;
    vector<double> relative_errors;
    double time_mean;
    double absolute_error_mean, relative_error_mean;
    bool doNN(int number_vertices, vector<vector<int>> edges, int limit);
    bool doRecursiveNN(int number_vertices, vector<vector<int>>& edges,
                       chrono::seconds time_limit, chrono::steady_clock::time_point time_started,
                       vector<bool>& visited, int current_vertex, vector<int>& temp_solution, int& solution_cost);
    int calcCost(int number_vertices, vector<vector<int>> edges, vector<int> path);
    //bool allVisited(vector<bool> visited);


    public:
    NN();
    bool testNN(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int time_limit);
    bool saveResults(string out_file, string in_file, int optCost);

};