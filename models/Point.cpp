//
// Created by Martyna on 2016-05-21.
//

#include <cmath>
#include "Point.h"

Point::Point (vector <double> values) {
    this->values = values;
    refPointDistance = 0;
}

Point::Point() {
    refPointDistance = 0;
}

vector <double> Point::getAttributes() const {
    return values;
}

void Point::setAttributes (vector <double> values ) {
    this->values = values;
}

set <Point> Point::getKNeighbourhoodIndex() const {
    return kNeighbourhoodIndex;
}

void Point::addPointToKNeighbourhoodIndex(Point p) {
    std::set<Point>::iterator it;
    it = kNeighbourhoodIndex.find(p);
    if (it != kNeighbourhoodIndex.end())
        kNeighbourhoodIndex.insert(p);
}
void Point::deletePointFromKNeighbourhoodIndex(Point p) {
    std::set<Point>::iterator it;
    it = kNeighbourhoodIndex.find(p);
    if (it != kNeighbourhoodIndex.end())
        kNeighbourhoodIndex.erase(p);
}

int Point::getSizeOfKNeighbourhoodIndex () const {
    return kNeighbourhoodIndex.size();
}

double Point::getRefPointDistance() const {
    return refPointDistance;
}

void Point::setRefPointDistance(double refPointDistance) {
    Point::refPointDistance = refPointDistance;
}

double Point::euclideanDistance (Point point) const {

    vector<double>::const_iterator itPoint = point.values.begin();
    double sum = 0;
    for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

        sum += pow((*it) - (*itPoint), 2.0);
        ++itPoint;
    }

    return sqrt(sum);
}
