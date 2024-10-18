#include <iostream>

using namespace std;

class Config {

    private:
    string method;
    string in_file;
    string solution;
    int repeats;
    string out_file;
    int number_info = 5;

    public:
    Config();
    bool loadConfig(string file_name);

};
