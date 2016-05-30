#pragma once
#include <memory>
#include <vector>
#include "Point.h"

class Cluster {
	static int ID;
	const int cid;
	std::vector<std::shared_ptr<Point>> points;
public:
	Cluster();
	void add(std::shared_ptr<Point> point);
	int size() const;
	inline int id() { return cid; };
};