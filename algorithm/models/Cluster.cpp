#include "Cluster.h"


int Cluster::ID = 0;

Cluster::Cluster(): cid(ID)
{
	++ID;
}

void Cluster::add(Point point)
{
	points.push_back(point);
}

int Cluster::size() const
{
	return points.size();
}
