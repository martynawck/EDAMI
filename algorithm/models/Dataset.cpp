//
// Created by Martyna on 2016-05-21.
//

#include <algorithm>
#include <fstream>
#include <istream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "Dataset.h"

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;


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

Dataset::Dataset(std::vector<std::shared_ptr<Point>> data): points(data), referencePoint(Point())
{
}

std::vector<std::shared_ptr<Point>> Dataset::getPoints() {
    return points;
}

void Dataset::setPoints(std::vector<std::shared_ptr<Point>>) {
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

bool Dataset::PrecedingPoint(shared_ptr<Point>& point) const {
	auto it = find(points.begin(), points.end(), point);
    if (it != points.begin()) {
        point = *(--it);
        return true;
    }
    return false;
}

bool Dataset::FollowingPoint(std::shared_ptr<Point>& point) const {
    auto it = find(points.begin(), points.end(), point);
    if (it != (points.end()-1)) {
        point = *(++it);
        return true;
    }
    return false;
}

bool cmd(shared_ptr<Point> p1, shared_ptr<Point> p2) {
    return p1->getDistance() < p2->getDistance();
}

void Dataset::sortPoints(){
    sort(points.begin(), points.end(), cmd);
}

void Dataset::calculateRefPointDistance() {
    vector<std::tuple<Point, double>> result;

	// HARD CODED REFERENCE POINT
	/*vector <double> vector1 (2, 0.0);
	referencePoint = Point(vector1,-1);*/
	for (auto it = points.begin(); it != points.end(); ++it) {
		double distance = referencePoint.calculateDistanceMeasure(*(it->get()), this->getDistanceMeasure(), this->getCMinkowski());
		it->get()->setDistanceFromReference(distance);
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
	vector<std::shared_ptr<Point>> points;
	for (auto const& it: intoDoubles(values)) {
		points.push_back(std::shared_ptr<Point>(new Point(it, i++)));
	}
	return std::shared_ptr<Dataset>(new Dataset(points));
}

const Point& Dataset::getReferencePoint() const {
    return referencePoint;
}

void Dataset::setReferencePoint(const Point &referencePoint) {
    Dataset::referencePoint = referencePoint;
}



