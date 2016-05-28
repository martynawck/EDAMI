//
// Created by Martyna on 2016-05-21.
//

#include <cmath>
#include <algorithm>
#include "Cluster.h"
#include "Point.h"

using namespace std;

Point::Point (vector <double> values, int id) {
    this->values = values;
    this->dist = 0;
    this->kNeighbourhoodIndex = set<Point,classcomp>();
    this->epsilon = 0;
    this->id = id;
}

Point::Point() {
    this->values = vector<double>();
    this->dist = 0;
    this->kNeighbourhoodIndex = set<Point,classcomp>();
    this->epsilon = 0;
    this->id = 0;
}

vector <double> Point::getAttributes() const {
    return values;
}

void Point::setAttributes (vector <double> values ) {
    this->values = values;
}

std::set<Point, Point::classcomp>& Point::getKNeighbourhoodIndex()  {
    return this->kNeighbourhoodIndex;
}

void Point::addPointToKNeighbourhoodIndex(Point p) {

    Point p1 = p;
    p1.clearKNeighbourhood();
    kNeighbourhoodIndex.insert(p1);
}

void Point::appendReverseNeighbour(Point point)
{
	reverseNeighbourhood.insert(point);
}

void Point::clearKNeighbourhood() {
    this->kNeighbourhoodIndex.clear();
}
void Point::deletePointFromKNeighbourhoodIndex(Point p) {
    std::set<Point, classcomp>::const_iterator it = find(kNeighbourhoodIndex.begin(), kNeighbourhoodIndex.end(), p);
    if (it != kNeighbourhoodIndex.end())
        kNeighbourhoodIndex.erase(it);
}

int Point::getSizeOfKNeighbourhoodIndex () const {
    return this->kNeighbourhoodIndex.size();
}

int Point::getId() {
    return this->id;
}

void Point::setId( int id) {
    this->id = id;
}

double Point::ndf()
{
	double l = kNeighbourhoodIndex.size();
	double r = reverseNeighbourhood.size();
	return l / r;
}

bool Point::clustered()
{
	return cluster_id != -1;
}

void Point::clusterize(Cluster cluster)
{
	cluster_id = cluster.id();
}

double Point::getDistance() const {
    return this->dist;
}

void Point::setDistance(double distance) {
    this->dist = distance;
}

void Point::setKNeighbourhoodIndex(std::set<Point, classcomp> kNeighbourhoodIndex) {
    this->kNeighbourhoodIndex = kNeighbourhoodIndex;
}

void Point::setEpsilon(double epsilon) {
    this->epsilon = epsilon;
}

double Point::getEpsilon() {
    return this->epsilon;
}


double Point::calculateDistanceMeasure(Point point, int measure, double c) const {

    vector<double>::const_iterator itPoint = point.values.begin();
    double sum = 0;
    double result = 0;

    switch (measure) {
        case 1:
            for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

                sum += pow((*it) - (*itPoint), 2.0);
                ++itPoint;
            }
            result = sqrt(sum);
            break;
        case 2:
            for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

                int res = (*it) - (*itPoint);
                if (res < 0)
                    res*=-1;
                sum += res;
                ++itPoint;
            }
            result = sum;
            break;
        case 3:
            for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

                int res = pow((*it) - (*itPoint), c);
                if (res < 0)
                    res*=-1;
                sum += res;
                ++itPoint;
            }
            result = pow(sum, (1/c));
            break;
    }



    return result;
}


