#include "Config.h"
#include <fstream>

Config::Config() {
    this -> repeats = 0;
}

bool Config::loadConfig(string file_name) {
    fstream config_file;
    config_file.open(file_name, ios::in);
    if (!config_file.good()) {
        return false;
    }
    else {
        if (!config_file.is_open()) {
            return false;
        }
        else {
            string config_data[number_info];
            for (int i = 0; i < number_info; i++) {
                getline(config_file, config_data[i]);
                if (config_file.fail() || config_data[i].empty()) {
                    config_file.close();
                    return false;
                }
            }
            method = config_data[0];
            in_file = config_data[1];
            solution = config_data[2];
            repeats = stoi(config_data[3]);
            out_file = config_data[4];
            return true;
        }
    }

}

string Config::getMethod() {
    return method;
}

string Config::getInFile() {
    return in_file;
}

string Config::getSolution() {
    return solution;
}

int Config::getRepeats() {
    return repeats;
}

string Config::getOutFile() {
    return out_file;
}
