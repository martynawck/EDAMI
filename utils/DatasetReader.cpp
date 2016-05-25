//
// Created by Martyna on 2016-05-21.
//

#include "DatasetReader.h"

vector<vector<string>> DatasetReader::readDatasetFile (string filename) {
    std::vector<std::vector<string> > values;
    std::ifstream fin(filename);
    for (std::string line; std::getline(fin, line); ) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values.push_back(
                std::vector<string>(std::istream_iterator<string>(in),
                                    std::istream_iterator<string>()));
    }
    return values;
}

vector<string> DatasetReader::readReferencePointParams(string filename) {
    std::vector<string> values;
    std::ifstream fin(filename);
    for (std::string line; std::getline(fin, line); ) {
        std::stringstream ss(line);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        values = vstrings;
    }
    return values;
}

vector<string> DatasetReader::readAlgorithmParams(string filename) {
    std::vector<string> values;
    std::ifstream fin(filename);
    for (std::string line; std::getline(fin, line); ) {
        values.push_back(line);
    }
    return values;
}