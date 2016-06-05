#include <algorithm>
#include <fstream>
#include <iostream>
#include "algorithm/models/Dataset.h"
#include "algorithm/NBC.h"
#include "algorithm/utils/config.h"
#include "algorithm\neighbourhood.h"


using namespace std;

int main()
try {
	Config cfg("edami.cfg");
	string path = cfg.value<string>("nbc.dataset");

	auto dataset = Dataset::readDatasetFile(path);
	dataset->setDistanceMeasure(cfg.value<int> ("nbc.measure"));
	
	NeighbourhoodAnalyzer analyzer(dataset);
	analyzer.k(cfg.value<int>("nbc.k"));
	auto clusters = analyzer.clusterize();
	for (auto const& cluster : clusters) {
		cout << cluster.pretty_print();
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
