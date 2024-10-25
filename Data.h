#include <vector>
#include <iostream>

using namespace std;

class Data {    //class to manage data from input file

    private:
    int number_vertices;
    vector<vector<int>> edges;

    public:
    Data();
    // Loads data as an integer matrix. Also returns false when loading is not successful
    bool loadData(string input_file);
    int getNumberVertices();
    vector<vector<int>> getEdges();


};