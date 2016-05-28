#pragma once
#include "Point.h"

#include <vector>
#include "Point.h"

class Cluster {
	static int ID;
	const int cid;
	std::vector<Point> points;
public:
	Cluster();
	void add(Point point);
	int size() const;
	inline int id() { return cid; };

};