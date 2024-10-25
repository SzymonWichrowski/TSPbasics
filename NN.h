#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include "Time.h"

using namespace std;

class NN {

    private:
    int start_vertex;
    vector<int> solution;
    Time time_utilities;
    vector<double> time_records;
    vector<int> cost_records;
    double time_mean;
    void doNN(int number_vertices, vector<vector<int>> edges);
    int calcCost(int number_vertices, vector<vector<int>> edges);
    //bool allVisited(vector<bool> visited);


    public:
    NN();
    void testNN(int number_vertices, vector<vector<int>> edges, int repeats);
    bool saveResults(string out_file, string in_file, int optCost);

};