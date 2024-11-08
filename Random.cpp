#include "Random.h"

Random::Random() {}

void Random::doRandom(int number_vertices, vector<vector<int>> edges, int optCost, int limit) {
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

    auto time_started = chrono::steady_clock::now();
    const auto time_limit = chrono::seconds(limit);

    do {
        shuffle(permutation.begin(), permutation.end(), gen);
        cost = calcCost(permutation, number_vertices, edges);

        if (cost < minCost) {
            minCost = cost;
            solution = permutation;
        }

        auto time_current = chrono::steady_clock::now();
        if (time_current - time_started > time_limit) {
            break;
        }
    } while (cost != optCost);

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

void Random::testRandom(int number_vertices, vector<vector<int>> edges, int repeats, int optCost, int time_limit) {
    double time_total = 0, relative_error_total = 0;
    int absolute_error_total = 0;

    time_records.reserve(repeats);
    cost_records.reserve(repeats);
    absolute_errors.reserve(repeats);
    relative_errors.reserve(repeats);

    for (int i = 0; i < repeats; i++) {
        time_utilities.timeStart();
        doRandom(number_vertices, edges, optCost, time_limit);
        time_utilities.timeStop();

        time_records.push_back(1000000.0 * time_utilities.getElapsed() / time_utilities.getFrequency()); //[us]
        time_total += time_records[i];
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
