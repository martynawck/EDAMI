//
// Created by Martyna on 2016-06-08.
//

#ifndef EDAMI_DATAREADER_H
#define EDAMI_DATAREADER_H


//#include <rpcndr.h>
#include "models/Dataset.h"

using namespace std;
class DataReader {

public:
    std::shared_ptr<Dataset> readDatasetFile(std::string const& filename, vector<bool>& typeOfAttribute, double& alpha);
    vector<string> readReferencePointFile(std::string const& filename);
};


#endif //EDAMI_DATAREADER_H
