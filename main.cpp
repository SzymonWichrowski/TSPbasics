#include <iostream>
#include "Config.h"
#include "Data.h"

using namespace std;

int main() {

    Config config;
    Data data;

    if (!config.loadConfig("config.txt")) {
        cout << "Error with config file!" << endl;
    }
    else {
        string method, in_file, solution, out_file;
        int repeats;
        method = config.getMethod();
        in_file = config.getInFile();
        solution = config.getSolution();
        repeats = config.getRepeats();
        out_file = config.getOutFile();

        if (!data.loadData(in_file)) {
            cout << "Error with data input file!" << endl;
        }
    }

    return 0;
}
