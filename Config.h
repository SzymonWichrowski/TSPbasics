#include <iostream>

using namespace std;

class Config {      // class to manage data from configuration file

    private:
    string method;
    string in_file;
    int optCost;
    int repeats;
    string out_file;
    int random_repeats;
    int number_info = 6;    // number of parameters in config file

    public:
    Config();
    // Loads data from configuration file. Also returns false when loading is not successful
    bool loadConfig(string file_name);
    string getMethod();
    string getInFile();
    int getOptCost();
    int getRepeats();
    string getOutFile();
    int getRandomRepeats();

};
