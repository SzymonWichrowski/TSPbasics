#include "NN.h"

NN::NN() {}

void NN::doNN(int number_vertices, vector<vector<int>> edges) {
    solution.clear();
    solution.reserve(number_vertices);
    vector<bool> visited(number_vertices, false);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_vertex(0, number_vertices - 1);
    start_vertex = dist_vertex(gen);
    visited[start_vertex] = true;
    solution.push_back(start_vertex);
    int current_vertex = start_vertex;
    int nearest_vertex;
    for (int j = 0; j < number_vertices - 1; j++) {
        int minCost = INT_MAX;
        for (int i = 0; i < number_vertices; i++) {
            if (!visited[i]) {
                if (edges[current_vertex][i] < minCost) {
                    minCost = edges[current_vertex][i];
                    nearest_vertex = i;
                }
            }
        }
        solution.push_back(nearest_vertex);
        visited[nearest_vertex] = true;
        current_vertex = nearest_vertex;
    }
}

int NN::calcCost(int number_vertices, vector<vector<int>> edges) {
    int cost = 0;
    for (int i = 0; i < number_vertices - 1; i++) {
        cost += edges[solution[i]][solution[i+1]];
    }
    cost += edges[solution[number_vertices - 1]][solution[0]];
    return cost;
}

void NN::testNN(int number_vertices, vector<vector<int>> edges, int repeats) {
    double time_total = 0;
    time_records.reserve(repeats);
    cost_records.reserve(repeats);
    for (int i = 0; i < repeats; i++) {
        time_utilities.timeStart();
        doNN(number_vertices, edges);
        time_utilities.timeStop();
        time_records.push_back(1000000.0 * time_utilities.getElapsed() / time_utilities.getFrequency()); //[us]
        time_total += time_records[i];
        cost_records.push_back(calcCost(number_vertices, edges));
        //printing results
        cout << i + 1 << "iteration" << endl;
        cout << "Received cost: " << cost_records[i] << endl;
        if(number_vertices < 16) {
            cout << "Received solution: ";
            for (int node : solution) {
                cout << node << "->";
            }
            cout << solution[0] << endl;
        }
        cout << "Time: " << time_records[i] << " [us]" << endl;
    }
    time_mean = time_total / repeats;
    cout << "Average time: " << time_mean << " [us]" << endl;
}

bool NN::saveResults(string out_file, string in_file, int optCost) {
    ofstream fileCSV(out_file, ios::app);
    if (!fileCSV.good()) {
        return false;
    }
    else {
        if (!fileCSV.is_open()) {
            return false;
        }
        else {
            fileCSV << "\n";
            fileCSV << "Nearest Neighbour\n";
            fileCSV << in_file << "\n";
            fileCSV << optCost << "\n";
            fileCSV << "Time records [us]\n";
            for (double record : time_records) {
                fileCSV << record << "\n";
            }
            fileCSV << "Average time\n";
            fileCSV << time_mean << "\n";
            fileCSV << "Cost records\n";
            for (double cost : cost_records) {
                fileCSV << cost << "\n";
            }
            fileCSV.close();
            return true;
        }
    }
}

//bool NN::allVisited(vector<bool> visited) {
//    bool result = true;
//    for (bool node : visited) {
//        if (!node) {
//            result = false;
//            break;
//        }
//    }
//    return result;
//}
