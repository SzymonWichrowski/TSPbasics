#include <vector>
#include <iostream>

using namespace std;

class Data {    //class to manage data from input file

    private:
    int number_vertices;
    vector<vector<int>> edges;

    public:
    Data();
    bool loadData(string input_file);

};