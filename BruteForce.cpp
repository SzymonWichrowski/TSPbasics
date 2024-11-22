#include "BruteForce.h"

BruteForce::BruteForce() {
    this -> minCost = INT_MAX;
}

bool BruteForce::doBF(int number_vertices, vector<vector<int>> edges, int optCost, int limit) {
    int cost;
    vector<int> permutation;
    permutation.reserve(number_vertices);
    for (int i = 0; i < number_vertices; i++) {
        permutation.push_back(i);
    }

    auto time_started = chrono::steady_clock::now();
    const auto time_limit = chrono::seconds(limit);

    do {
        cost = calcCost(permutation, number_vertices, edges);
        if (cost < minCost) {
            minCost = cost;
            solution = permutation;
        }

        if (minCost == optCost) break;

        auto time_current = chrono::steady_clock::now();
        if (time_current - time_started > time_limit) {
            return false;
        }

    } while (next_permutation(permutation.begin() + 1, permutation.end()));

    return true;
}

int BruteForce::calcCost(vector<int> permutation, int number_vertices, vector<vector<int>> edges) {
    int cost = 0;
    for (int i = 0; i < number_vertices - 1; i++) {
        cost += edges[permutation[i]][permutation[i + 1]];
    }
    cost += edges[permutation[number_vertices - 1]][permutation[0]];
    return cost;
}

bool BruteForce::testBF(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int time_limit) {
    double time_total = 0;
    bool time_over;
    time_records.reserve(repeats);

    for (int i = 0; i < repeats; i++) {
        time_utilities.timeStart();
        time_over = doBF(number_vertices, edges, optCost, time_limit);
        time_utilities.timeStop();

        if (!time_over) {
            cout << i + 1 << " iteration" << endl;
            cout << "Time limit exceeded!" << endl;
            return false;
        }

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
        cout << "Time: " << time_records[i] << " [us]" << endl;
    }
    mean = time_total / repeats;
    cout << "Average time: " << mean << " [us]" << endl;

    return true;
}

bool BruteForce::saveResults(string out_file, string in_file, int optCost) {
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
            fileCSV << "Brute-Force\n";
            fileCSV << in_file << "\n";
            fileCSV << optCost << "\n";
            fileCSV << "Time records [us]\n";
            for (double record : time_records) {
                fileCSV << record << "\n";
            }
            fileCSV << "Average\n";
            fileCSV << mean << "\n";
            fileCSV.close();
            return true;
        }
    }
}


