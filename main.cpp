#include <iostream>
#include "Config.h"
#include "Data.h"
#include "BruteForce.h"
#include "NN.h"

using namespace std;

int main() {

    Config config;
    Data data;

    if (!config.loadConfig("config.txt")) {
        cout << "Error with config file!" << endl;
    }
    else {
        string method, in_file, out_file;
        int optCost, repeats;
        method = config.getMethod();
        in_file = config.getInFile();
        optCost = config.getOptCost();
        repeats = config.getRepeats();
        out_file = config.getOutFile();

        if (!data.loadData(in_file)) {
            cout << "Error with data input file!" << endl;
        }
        else {
            if (method == "r") {
                cout << "Method: RANDOM" << endl;
                cout << "Instance: " + in_file << endl;
                cout << "Optimal cost: " << optCost << endl;

            }
            else if (method == "n") {
                cout << "Method: NEAREST NEIGHBOUR" << endl;
                cout << "Instance: " + in_file << endl;
                cout << "Optimal cost: " << optCost << endl;
                NN nn;
                nn.testNN(data.getNumberVertices(), data.getEdges(), repeats);
                if (!nn.saveResults(out_file, in_file, optCost)){
                    cout << "Data not saved!";
                }
            }
            else if (method == "b") {
                cout << "Method: BRUTE-FORCE" << endl;
                cout << "Instance: " + in_file << endl;
                cout << "Optimal cost: " << optCost << endl;
                BruteForce bf;
                bf.testBF(data.getNumberVertices(), data.getEdges(), repeats);
                if (!bf.saveResults(out_file, in_file, optCost)){
                    cout << "Data not saved!";
                }
            }
            else {
                cout << "Incorrect method!" << endl;
            }
        }
    }

    return 0;
}
