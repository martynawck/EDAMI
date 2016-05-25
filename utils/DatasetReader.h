//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_DATASETREADER_H
#define EDAMI_DATASETREADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

class DatasetReader {

    public:
        vector<vector<string>> readDatasetFile (string filename);
        vector<string> readReferencePointParams (string filename);
        vector<string> readAlgorithmParams (string filename);

};


#endif //EDAMI_DATASETREADER_H
