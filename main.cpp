#include <algorithm>
#include <fstream>
#include <iostream>
//#include <rpcndr.h>
#include "algorithm/models/Dataset.h"
#include "algorithm/NBC.h"
#include "algorithm/utils/config.h"
#include "algorithm/neighbourhood.h"
//#include "algorithm\neighbourhood.h"
#include "algorithm/models/Cluster.h"
#include "algorithm/DataReader.h"


using namespace std;

int main()
try {
	Config cfg("edami.cfg");
	string path = cfg.value<string>("nbc.dataset");
	string path2 = cfg.value<string>("nbc.refpoint");

	vector <bool> typeOfAttributes;
	auto dataset = Dataset::readDatasetFile(path, typeOfAttributes, cfg.value<double> ("nbc.alpha"));
	dataset->readReferencePointFile(path2,typeOfAttributes);
	dataset->setDistanceMeasure(cfg.value<int> ("nbc.measure"));
	dataset->setTypeOfAttributes(typeOfAttributes);
	dataset->setImportanceOfNominal(cfg.value<double> ("nbc.nominalimportance"));

	NeighbourhoodAnalyzer analyzer(dataset);
	analyzer.k(5);
	//analyzer.k(cfg.value<int>("nbc.k"));
	auto clusters = analyzer.clusterize();
	for (auto const& cluster : clusters) {
		cout<<cluster.pretty_print();
	}

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
