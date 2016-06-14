#include <stack>
#include <iostream>
#include "neighbourhood.h"
#include "models/Point.h"
#include "NBC.h"
#include "models/Cluster.h"

using std::set;
using std::vector;
using std::shared_ptr;
using std::stack;

NeighbourhoodAnalyzer::NeighbourhoodAnalyzer(std::shared_ptr<Dataset> data): dataset(data)
{
}

auto NeighbourhoodAnalyzer::clusterize() -> vector<Cluster>
{
	auto points = annotated_points();
	vector<Cluster> clusters;

	for (auto point: points) {
		if (point->clustered()) continue;
		if (point->ndf() < 1) continue;

		Cluster cluster;
		cluster.add(point);
		
		auto cluster_candidates = find_cluster_candidates(point);
		for (auto it = cluster_candidates.begin(); it != cluster_candidates.end(); ++it) {
			auto npoint = *it;
			if (npoint->clustered()) continue;
			cluster.add(npoint);
		}

		clusters.push_back(cluster);
	}
	return clusters;
}

auto NeighbourhoodAnalyzer::annotated_points() const -> std::vector<shared_ptr<Point>>  {
	auto points = TI_k_Neighbourhood_Index(*dataset, nk);
	return points;
}

auto NeighbourhoodAnalyzer::find_cluster_candidates(shared_ptr<Point> point) const -> set<shared_ptr<Point>>
{
	set<shared_ptr<Point>> candidates;
	stack<shared_ptr<Point>> searches;
	searches.push(point);
	
	while (!searches.empty()) {
		auto base_point = searches.top();
		searches.pop();
		auto points = base_point->getKNeighbourhoodIndex();
		for (auto point : points) {
			if (point->ndf() >= 1 && candidates.count(point) == 0) searches.push(point);
			candidates.insert(point);
		}
	}
	return candidates;
}
