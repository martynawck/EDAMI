//
// Created by Martyna on 2016-05-21.
//

#include <cmath>
#include <algorithm>
#include "Point.h"



Point::Point (vector <double> values, int id) {
    this->values = values;
    this->dist = 0;
    this->kNeighbourhoodIndex = vector<Point>();
    this->epsilon = 0;
    this->id = id;
}

Point::Point() {
    this->values = vector<double>();
    this->dist = 0;
    this->kNeighbourhoodIndex = vector<Point>();
    this->epsilon = 0;
    this->id = 0;
}

vector <double> Point::getAttributes() const {
    return values;
}

void Point::setAttributes (vector <double> values ) {
    this->values = values;
}

vector <Point>& Point::getKNeighbourhoodIndex()  {
    return this->kNeighbourhoodIndex;
}

void Point::addPointToKNeighbourhoodIndex(Point p) {

 //   if (std::find(kNeighbourhoodIndex.begin(), kNeighbourhoodIndex.end(), p)
   //     == kNeighbourhoodIndex.end())
    Point p1 = p;
    p1.clearKNeighbourhood();
    kNeighbourhoodIndex.push_back(p1);
}

void Point::clearKNeighbourhood() {
    this->kNeighbourhoodIndex.clear();
}
void Point::deletePointFromKNeighbourhoodIndex(Point p) {
    std::vector<Point>::const_iterator it = find(kNeighbourhoodIndex.begin(), kNeighbourhoodIndex.end(), p);
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

double Point::getDistance() const {
    return this->dist;
}

void Point::setDistance(double distance) {
    this->dist = distance;
}

void Point::setKNeighbourhoodIndex(vector<Point> kNeighbourhoodIndex) {
    this->kNeighbourhoodIndex = kNeighbourhoodIndex;
}

void Point::setEpsilon(double epsilon) {
    this->epsilon = epsilon;
}

double Point::getEpsilon() {
    return this->epsilon;
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


