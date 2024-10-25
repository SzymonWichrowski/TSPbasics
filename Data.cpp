#include "Data.h"
#include <fstream>
#include <sstream>

Data::Data() {
    this -> number_vertices = 0;
}

bool Data::loadData(string input_file) {
    fstream file;
    file.open(input_file, ios::in);
    if (!file.good()) {
        return false;
    }
    else { // file was found
        if (!file.is_open()) {
            return false;
        }
        else { // file is open
            if (!(file >> number_vertices)) {
                file.close();
                return false;
                // error with loading number of vertices
            }
            else { // loading number of vertices succesfully
                if (number_vertices <= 1) {
                    file.close();
                    return false;
                }
                else { // number of vertices is correct
                    string line;
                    getline(file, line);
                    vector<vector<int>> matrix(number_vertices, vector<int>(number_vertices, 0));
                    for (int i = 0; i < number_vertices; i++) {
                        getline(file, line);
                        if(file.fail() || line.empty()) {
                            file.close();
                            return false;
                        }
                        else { // loading not failed
                            istringstream in_ss(line);
                            for (int j = 0; j < number_vertices; j++) {
                                if(!(in_ss >> matrix[i][j])) {
                                    file.close();
                                    return false;
                                }
                            }
                        }
                    }
                    edges = matrix;
                    return true;
                }
            }
        }
    }
}

int Data::getNumberVertices() {
    return number_vertices;
}

vector<vector<int>> Data::getEdges() {
    return edges;
}
