#include "NN.h"

NN::NN() {}

bool NN::doNN(int number_vertices, vector<vector<int>> edges, int limit) {
    solution.clear();
    solution.reserve(number_vertices);
    int solution_cost = INT_MAX;
    vector<int> temp_solution;
    temp_solution.reserve(number_vertices);

    auto time_started = chrono::steady_clock::now();
    const auto time_limit = chrono::seconds(limit);

    for (int vertex = 0; vertex < number_vertices; vertex++) {

        temp_solution.clear();
        vector<bool> visited(number_vertices, false);

        visited[vertex] = true;
        temp_solution.push_back(vertex);

        if (!doRecursiveNN(number_vertices, edges, time_limit, time_started, visited, vertex, temp_solution, solution_cost)) {
            return false;
        }
    }

    return true;
}

bool NN::doRecursiveNN(int number_vertices, vector<vector<int>>& edges,
                       chrono::seconds time_limit, chrono::steady_clock::time_point time_started,
                       vector<bool>& visited, int current_vertex, vector<int>& temp_solution, int& solution_cost) {

    if (temp_solution.size() == number_vertices) {
        int temp_solution_cost = calcCost(number_vertices, edges, temp_solution);
        if (temp_solution_cost < solution_cost) {
            solution_cost = temp_solution_cost;
            solution = temp_solution;
        }
        return true;
    }

    int minCost = INT_MAX;
    vector<int> possibilities;

    for (int i = 0; i < number_vertices; i++) {
        if (!visited[i]) {
            if (edges[current_vertex][i] < minCost) {
                minCost = edges[current_vertex][i];
                possibilities.clear();
                possibilities.push_back(i);
            }
            else if (edges[current_vertex][i] == minCost) {
                possibilities.push_back(i);
            }
        }
    }

    for (int possibility : possibilities) {
        temp_solution.push_back(possibility);
        visited[possibility] = true;

        auto time_current = chrono::steady_clock::now();
        if (time_current - time_started > time_limit) {
            return false;
        }

        if (!doRecursiveNN(number_vertices, edges, time_limit, time_started, visited, possibility, temp_solution, solution_cost)) {
            return false;
        }

        temp_solution.pop_back();
        visited[possibility] = false;
    }

    return true;
}

int NN::calcCost(int number_vertices, vector<vector<int>> edges, vector<int> path) {
    int cost = 0;
    for (int i = 0; i < number_vertices - 1; i++) {
        cost += edges[path[i]][path[i+1]];
    }
    cost += edges[path[number_vertices - 1]][path[0]];
    return cost;
}

bool NN::testNN(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int time_limit) {
    double time_total = 0, relative_error_total = 0;
    int absolute_error_total = 0;
    bool time_over;

    time_records.reserve(repeats);
    cost_records.reserve(repeats);
    absolute_errors.reserve(repeats);
    relative_errors.reserve(repeats);

    for (int i = 0; i < repeats; i++) {
        time_utilities.timeStart();
        time_over = doNN(number_vertices, edges, time_limit);
        time_utilities.timeStop();

        if (!time_over) {
            cout << i + 1 << "iteration" << endl;
            cout << "Time limit exceeded!" << endl;
            return false;
        }

        time_records.push_back(1000000.0 * time_utilities.getElapsed() / time_utilities.getFrequency()); //[us]
        time_total += time_records[i];
        cost_records.push_back(calcCost(number_vertices, edges, solution));
        absolute_errors.push_back(cost_records[i] - optCost);
        relative_errors.push_back((double)absolute_errors[i] / optCost);
        absolute_error_total += absolute_errors[i];
        relative_error_total += relative_errors[i];

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
        cout << "Absolute error: " << absolute_errors[i] << endl;
        cout << "Relative error: " << relative_errors[i] << endl;
        cout << "Relative error [%]: " << relative_errors[i] * 100 << endl;
        cout << "Time: " << time_records[i] << " [us]" << endl;
    }
    time_mean = time_total / repeats;
    cout << "Average time: " << time_mean << " [us]" << endl;
    absolute_error_mean = (double)absolute_error_total / repeats;
    cout << "Mean absolute error: " << absolute_error_mean << endl;
    relative_error_mean = relative_error_total / repeats;
    cout << "Mean relative error: " << relative_error_mean << endl;
    cout << "Mean relative error [%]: " << relative_error_mean * 100 << endl;

    return true;
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
            fileCSV << "Absolute error records\n";
            for (double error : absolute_errors) {
                fileCSV << error << "\n";
            }
            fileCSV << "Average absolute record\n";
            fileCSV << absolute_error_mean << "\n";
            fileCSV << "Relative error records\n";
            for (double error : relative_errors) {
                fileCSV << error << "\n";
            }
            fileCSV << "Average relative error records\n";
            fileCSV << relative_error_mean << "\n";
            fileCSV << "Relative error records [%]\n";
            for (double error : relative_errors) {
                fileCSV << error * 100 << "\n";
            }
            fileCSV << "Average relative error records [%]\n";
            fileCSV << relative_error_mean * 100 << "\n";
            fileCSV.close();
            return true;
        }
    }
}
