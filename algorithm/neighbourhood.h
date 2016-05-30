#pragma once
#include <memory>
#include <vector>
#include "models/Dataset.h"
#include "models\Cluster.h"
#include "models\Point.h"


class NeighbourhoodAnalyzer {
	std::shared_ptr<Dataset> dataset;
	int nk = 5;
public:
	NeighbourhoodAnalyzer(std::shared_ptr<Dataset> dataset);
	auto clusterize() -> std::vector<Cluster>;

	inline int k() { return nk; };
	inline void k(int k) { nk = k; }
private:
	auto annotated_points() const -> std::vector<std::shared_ptr<Point>> ;
	auto find_cluster_candidates(std::shared_ptr<Point>) const -> std::set<std::shared_ptr<Point>>;
};