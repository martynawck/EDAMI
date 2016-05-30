#include "Cluster.h"


int Cluster::ID = 0;

Cluster::Cluster(): cid(ID)
{
	++ID;
}

void Cluster::add(std::shared_ptr<Point> point)
{
	point->clusterize(*this);
	points.push_back(point);
}

int Cluster::size() const
{
	return points.size();
}
