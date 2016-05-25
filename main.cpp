#include <algorithm>
#include <fstream>
#include <iostream>
#include "DatasetReader.h"
#include "models/Dataset.h"
#include "NBC.h"
#include "utils\config.h"

using namespace std;


vector<vector<double>> intoDoubles(vector<vector<string>> vec) {
    vector<vector<double>> vectorx;
    vector<vector<string>>::iterator it;
    vector<string>::iterator it2;

    for(it = vec.begin();it!=vec.end();++it) {
        vector<double> vecd;
        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            vecd.push_back(atof((*it2).c_str()));
        }
        vectorx.push_back(vecd);
    }

    return vectorx;
}

int main()
 try {
	Config cfg("edami.cfg");
	string path = cfg.value<string>("nbc.dataset");
	
    DatasetReader datasetReader = DatasetReader();
    vector<vector<string>> data = datasetReader.readDatasetFile(path);
    vector<vector<double>> doubleData = intoDoubles(data);

    Dataset dataset = Dataset();
    dataset.setDistanceMeasure(1);
    vector<Point> points = vector<Point>();
    int i = 1;
    for (vector<vector<double>>::iterator it = doubleData.begin(); it != doubleData.end(); ++it) {
        points.push_back(Point(*it, i));
        i++;
    }
    dataset.setPoints(points);

	NBC nbc = NBC();
    nbc.TI_k_Neighbouthood_Index(dataset, 1);

	cin.sync();
	cin.get();

    return 0;

}
catch (exception& ex) {
	cout << ex.what() << endl;
	cin.sync();
	cin.get();
	return -1;
}
