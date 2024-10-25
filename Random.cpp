#include "Random.h"

Random::Random() {}

void Random::doRandom(int number_vertices, vector<vector<int>> edges, int number_draws) {
    solution.clear();
    solution.reserve(number_vertices);
    int cost;
    int minCost = INT_MAX;
    random_device rd;
    mt19937 gen(rd());
    vector<int> permutation;
    permutation.reserve(number_vertices);
    for (int i = 0; i < number_vertices; i++) {
        permutation.push_back(i);
    }
    for (int i = 0; i < number_draws; i++) {
        shuffle(permutation.begin(), permutation.end(), gen);
        cost = calcCost(permutation, number_vertices, edges);
        if (cost < minCost) {
            minCost = cost;
            solution = permutation;
        }
    }
    cost_records.push_back(minCost);
}

int Random::calcCost(vector<int> permutation, int number_vertices, vector<vector<int>> edges) {
    int cost = 0;
    for (int i = 0; i < number_vertices - 1; i++) {
        cost += edges[permutation[i]][permutation[i+1]];
    }
    cost += edges[permutation[number_vertices - 1]][permutation[0]];
    return cost;
}

void Random::testRandom(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int number_draws) {
    double time_total = 0;
    time_records.reserve(repeats);
    cost_records.reserve(repeats);
    for (int i = 0; i < repeats; i++) {
        time_utilities.timeStart();
        doRandom(number_vertices, edges, number_draws);
        time_utilities.timeStop();
        time_records.push_back(1000000.0 * time_utilities.getElapsed() / time_utilities.getFrequency()); //[us]
        time_total += time_records[i];
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

bool Random::saveResults(std::string out_file, std::string in_file, int optCost) {
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
            fileCSV << "Random\n";
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
