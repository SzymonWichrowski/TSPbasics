#include <vector>
#include <random>
#include <iostream>
#include <fstream>
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
    void doNN(int number_vertices, vector<vector<int>> edges);
    int calcCost(int number_vertices, vector<vector<int>> edges);
    //bool allVisited(vector<bool> visited);


    public:
    NN();
    void testNN(int number_vertices, vector<vector<int>> edges, int repeats, int optCost);
    bool saveResults(string out_file, string in_file, int optCost);

};