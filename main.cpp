#include <algorithm>
#include <fstream>
#include <iostream>
#include "DatasetReader.h"
#include "models/Dataset.h"
#include "NBC.h"

using namespace std;



vector<vector <double>> intoDoubles(vector<vector<string>> vec) {
    vector<vector<double>> vectorx;
    vector<vector<string> >::iterator it;
    vector<string> ::iterator it2;

    for(it = vec.begin();it!=vec.end();++it) {
        vector<double> vecd;
        for(it2 = (*it).begin();it2!=(*it).end();++it2) {
            vecd.push_back(atof((*it2).c_str()));
        }
        vectorx.push_back(vecd);
    }

    return vectorx;
}

int main()
{
    DatasetReader datasetReader = DatasetReader();

    vector<vector<string>> values = datasetReader.readDatasetFile("C:\\Users\\Martyna\\git\\EDAMI\\sponge.data");
    vector<string> values1 = datasetReader.readAlgorithmParams("C:\\Users\\Martyna\\git\\EDAMI\\someParams.txt");
    vector <string> values2 = datasetReader.readReferencePointParams("C:\\Users\\Martyna\\git\\EDAMI\\refPoint.txt");
    vector <vector<string>> data = datasetReader.readDatasetFile("C:\\Users\\Martyna\\git\\EDAMI\\fertility_Diagnosis.txt");
    vector<vector<double>> doubleData = intoDoubles(data);

    Dataset dataset = Dataset();
    vector<Point> points;

    for (vector<vector<double>>::iterator it = doubleData.begin(); it!= doubleData.end(); ++it) {

        points.push_back(Point(*it));
    }
    dataset.setPoints(points);

    NBC nbc = NBC();
    nbc.TI_k_Neighbouthood_Index(dataset,1);

    cout<<dataset.getPointsSize()<<endl;

    return 0;

}
