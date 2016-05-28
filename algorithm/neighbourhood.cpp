#include <stack>
#include "neighbourhood.h"
#include "models\Point.h"
#include "NBC.h"

using std::set;
using std::vector;

NeighbourhoodAnalyzer::NeighbourhoodAnalyzer(std::shared_ptr<Dataset> data): dataset(data)
{
}

auto NeighbourhoodAnalyzer::clusterize() -> vector<Cluster>
{
	vector<Point> points = annotated_points();
	vector<Cluster> clusters;

	for (Point& point : points) {
		if (point.clustered()) continue;
		if (point.ndf() < 1) continue;

		Cluster cluster;
		cluster.add(point);
		
		auto cluster_candidates = find_cluster_candidates(point);
		for (auto it = cluster_candidates.begin(); it != cluster_candidates.end(); ++it) {
			auto npoint = *it;
			if (npoint.clustered()) continue;
			cluster.add(npoint);
		}

		clusters.push_back(cluster);
	}
	return clusters;
}

auto NeighbourhoodAnalyzer::annotated_points() const -> std::vector<Point>  {
	auto points = TI_k_Neighbourhood_Index(*dataset, nk);
	return points;
}

auto NeighbourhoodAnalyzer::find_cluster_candidates(Point const & point) const -> std::set<Point>
{
	std::set<Point> candidates; 
	std::stack<Point> searches;
	searches.push(point);
	
	while (!searches.empty()) {
		Point base_point = searches.top();
		searches.pop();
		for (Point point : base_point.getKNeighbourhoodIndex()) {
			if (point.ndf() >= 1 && candidates.count(point) == 0) searches.push(point);
			candidates.insert(point);
		}
	}
	return candidates;
}
