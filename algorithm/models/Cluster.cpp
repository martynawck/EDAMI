#include <sstream>
#include "Cluster.h"

using std::vector;
using std::string;

int Cluster::ID = 0;

Cluster::Cluster(): cid(ID)
{
	++ID;
}

std::vector<double> Cluster::center() const noexcept
{
	vector<double> coords(points[0]->getAttributes().size(), 0.0);
	for (auto point : points) {
		auto values = point->getAttributes();
		for (int i = 0; i < values.size(); i++) {
			coords[i] += values[i];
		}
	}

	for (int i = 0; i < coords.size(); i++) {
		coords[i] /= points.size();
	}

	return coords;
}

std::string Cluster::pretty_print() const noexcept
{
	std::stringstream ss;
	ss << "Cluster id " << cid << std::endl;
	ss << " Center ";
	for (auto value : center()) {
		ss << value << ", ";
	}
	ss << std::endl;
	ss << " Number of elements " << points.size() << std::endl;

	return ss.str();
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
