#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
//#include <rpcndr.h>
#include "algorithm/models/Dataset.h"
#include "algorithm/NBC.h"
#include "algorithm/utils/config.h"
#include "algorithm/neighbourhood.h"
//#include "algorithm\neighbourhood.h"
#include "algorithm/models/Cluster.h"
//#include "algorithm/DataReader.h"
#include "algorithm\utils\config.h"

using namespace std;

int main()
try {
	Config cfg("edami.cfg");
	string path = cfg.value<string>("nbc.dataset");
	string path2 = cfg.value<string>("nbc.refpoint");
	double alpha = cfg.value<double>("nbc.alpha");


	vector <bool> typeOfAttributes;
	// NORMALIZATION -> 0 - nop, 1 - range, 2 - z_score, 3 - euclidean
	int normalization = cfg.value<int>("nbc.normalization");;
	auto dataset = Dataset::readDatasetFile(path, typeOfAttributes, alpha, normalization);

	dataset->setTypeOfAttributes(typeOfAttributes);
	dataset->readReferencePointFile(path2,typeOfAttributes);
	dataset->setDistanceMeasure(2);
	dataset->setImportanceOfNominal(cfg.value<double>("nbc.nominalimportance"));

	const time_t begin_time = clock();
	NeighbourhoodAnalyzer analyzer(dataset);
	//analyzer.k(10);
	analyzer.k(cfg.value<int>("nbc.k"));
	auto clusters = analyzer.clusterize();
	cout << "TIME  "<< float(clock() - begin_time) / CLOCKS_PER_SEC << endl<<endl;
	cout << "Cluster count " << clusters.size() << endl;
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
