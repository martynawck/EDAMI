//
// Created by Martyna on 2016-05-21.
//

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include "Dataset.h"

using std::map;
using std::string;
using std::vector;

vector<vector<double>> intoDoubles(vector<vector<string>> vec) {
	vector<vector<double>> vectorx;
	vector<vector<string>>::iterator it;
	vector<string>::iterator it2;

	for (it = vec.begin(); it != vec.end(); ++it) {
		vector<double> vecd;
		for (it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			vecd.push_back(atof((*it2).c_str()));
		}
		vectorx.push_back(vecd);
	}

	return vectorx;
}

Dataset::Dataset(vector<Point> points): points(points), referencePoint(Point())
{
}

vector<Point> Dataset::getPoints() {
    return this->points;
}

void Dataset::setPoints(vector<Point> points) {
    this->points = points;
}

int Dataset::getPointsSize() {
    return points.size();
}

int Dataset::getDistanceMeasure() {
    return this->distanceMeasure;
}

void Dataset::setDistanceMeasure(int measure) {
    this->distanceMeasure = measure;
}

int Dataset::getPointIndex(Point p) {
    return find(points.begin(), points.end(), p) - points.begin();
}

bool Dataset::PrecedingPoint(Point& point) const {

    vector<Point>::const_iterator it = find(points.begin(), points.end(), point);
    if (it != points.begin()) {
        point = *(--it);
        return true;
    }
    return false;
}

bool Dataset::FollowingPoint(Point& point) const {
    vector<Point>::const_iterator it = find(points.begin(), points.end(), point);
    if (it != (points.end()-1)) {
        point = *(++it);
        return true;
    }
    return false;
}

bool cmd(const Point &p1, const Point &p2) {
    return p1.getDistance() < p2.getDistance();
}

void Dataset::sortPoints(){
    sort(points.begin(), points.end(), cmd);
}

void Dataset::calculateRefPointDistance() {
    vector<std::tuple<Point, double>> result;
	for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		double distance = referencePoint.calculateDistanceMeasure(*it, this->getDistanceMeasure(), this->getCMinkowski());
		it->setDistance(distance);
	}
}

double Dataset::getCMinkowski() {
    return  this->cMinkowski;
}

void Dataset::setCMinkowski(double c) {
    this->cMinkowski = c;
}

auto Dataset::readDatasetFile(string const& filename) -> std::shared_ptr<Dataset>
{
	std::vector<std::vector<string> > values;
	std::ifstream fin(filename);
	for (std::string line; std::getline(fin, line); ) {
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream in(line);
		values.push_back(
			std::vector<string>(std::istream_iterator<string>(in),
				std::istream_iterator<string>()));
	}

	int i = 1;
	vector<Point> points;
	for (auto const& it: intoDoubles(values)) {
		points.emplace_back(it, i++);
	}

	return std::shared_ptr<Dataset>(new Dataset(points));
}

const Point& Dataset::getReferencePoint() const {
    return referencePoint;
}

void Dataset::setReferencePoint(const Point &referencePoint) {
    Dataset::referencePoint = referencePoint;
}



