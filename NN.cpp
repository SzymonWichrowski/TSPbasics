#include "NN.h"

NN::NN() {}

bool NN::doNN(int number_vertices, vector<vector<int>> edges, int limit) {
    solution.clear();
    solution.reserve(number_vertices);
    vector<bool> visited(number_vertices, false);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_vertex(0, number_vertices - 1);

    int start_vertex = dist_vertex(gen);
    visited[start_vertex] = true;
    solution.push_back(start_vertex);

    int current_vertex = start_vertex;
    int nearest_vertex;

    auto time_started = chrono::steady_clock::now();
    const auto time_limit = chrono::seconds(limit);

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

        auto time_current = chrono::steady_clock::now();
        if (time_current - time_started > time_limit) {
            return false;
        }
    }
    return true;
}

int NN::calcCost(int number_vertices, vector<vector<int>> edges) {
    int cost = 0;
    for (int i = 0; i < number_vertices - 1; i++) {
        cost += edges[solution[i]][solution[i+1]];
    }
    cost += edges[solution[number_vertices - 1]][solution[0]];
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
        cost_records.push_back(calcCost(number_vertices, edges));
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
