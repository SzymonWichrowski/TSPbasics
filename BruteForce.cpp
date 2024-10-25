#include "BruteForce.h"
#include <algorithm>
#include <iostream>

BruteForce::BruteForce() {
    this -> minCost = INT_MAX;
}

void BruteForce::doBF(int number_vertices, vector<vector<int>> edges) {
    int cost;
    vector<int> permutation;
    permutation.reserve(number_vertices);
    for (int i = 0; i < number_vertices; i++) {
        permutation.push_back(i);
    }
    do {
        cost = calcCost(permutation, number_vertices, edges);
        if (cost < minCost) {
            minCost = cost;
            solution = permutation;
        }
    } while (next_permutation(permutation.begin() + 1, permutation.end()));
}

int BruteForce::calcCost(vector<int> permutation, int number_vertices, vector<vector<int>> edges) {
    int cost = 0;
    for (int i = 0; i < number_vertices - 1; i++) {
        cost += edges[permutation[i]][permutation[i + 1]];
    }
    cost += edges[permutation[number_vertices - 1]][permutation[0]];
    return cost;
}

void BruteForce::testBF(int number_vertices, vector<vector<int>> edges, int repeats) {
    double time_total = 0;
    time_records.reserve(repeats);
    for (int i = 0; i < repeats; i++) {
        time_utilities.timeStart();
        doBF(number_vertices, edges);
        time_utilities.timeStop();
        time_records.push_back(1000000.0 * time_utilities.getElapsed() / time_utilities.getFrequency()); // [us]
        time_total += time_records[i];
        // printing results (not very classy but its just research)
        cout << i + 1 << " iteration" << endl;
        cout << "Received cost: " << minCost << endl;
        if(number_vertices < 16) {
            cout << "Received solution: ";
            for (int node : solution) {
                cout << node << "->";
            }
            cout << solution[0] << endl;
        }
        cout << "Time: " << time_records[i] << endl;
    }
    mean = time_total / repeats;
    cout << "Average time: " << mean << endl;

}


