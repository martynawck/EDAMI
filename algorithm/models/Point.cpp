//
// Created by Martyna on 2016-05-21.
//

#include <cmath>
#include <algorithm>
#include <iostream>
#include "Cluster.h"
#include "Point.h"

using namespace std;


Point::Point() : Point(vector<double>(), 0)
{
}

Point::Point (vector <double> v, int i):
	values(v), 
	dist(0), 
	epsilon(0), 
	id(i),
    distanceFromReference(0)
{
}

void Point::setDistanceFromReference (double distance) {
    this->distanceFromReference = distance;
}

double Point::getDistanceFromReference() const {
    return this->distanceFromReference;
}

vector <double> Point::getAttributes() const {
    return values;
}

void Point::setAttributes (vector <double> values ) {
    this->values = values;
}

std::set<shared_ptr<Point>, Point::classcomp> Point::getKNeighbourhoodIndex()  {
    return kNeighbourhoodIndex;
}

void Point::addPointToKNeighbourhoodIndex(shared_ptr<Point> p) {

    auto p1 = p;
    p1->clearKNeighbourhood();
    kNeighbourhoodIndex.insert(p1);
}

void Point::appendReverseNeighbour(shared_ptr<Point> point)
{
	reverseNeighbourhood.insert(point);
}

void Point::clearKNeighbourhood() {
    this->kNeighbourhoodIndex.clear();
}
void Point::deletePointFromKNeighbourhoodIndex(shared_ptr<Point> p) {
    auto it = kNeighbourhoodIndex.find(p);
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

void Point::setKNeighbourhoodIndex(std::set<shared_ptr<Point>, classcomp> kNeighbourhoodIndex) {
    this->kNeighbourhoodIndex = kNeighbourhoodIndex;
}

void Point::setEpsilon(double epsilon) {
    this->epsilon = epsilon;
}

double Point::getEpsilon() {
    return this->epsilon;
}


double Point::calculateDistanceMeasure(Point const& point, int measure, double c, std::vector<bool> attributeTypes, double importanceOfNominal) const {

    vector<double>::const_iterator itPoint = point.values.begin();
    double sum = 0;
    double result = 0;
    int i = 0;

    switch (measure) {
        case 1:
            for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

                if (attributeTypes.at(i) == 0) {
                    sum += pow((*it) - (*itPoint), 2.0);
                } else {
                    if ((*it) == (*itPoint))
                        sum += 0;
                    else
                        sum += importanceOfNominal;
                }
                ++itPoint;
                ++i;
            }
            result = sqrt(sum);
            break;
        case 2:
            for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

                if (attributeTypes.at(i) == 0) {
                    int res = (*it) - (*itPoint);
                    if (res < 0)
                        res *= -1;
                    sum += res;
                }  else {
                    if ((*it) == (*itPoint))
                        sum += 0;
                    else
                        sum += importanceOfNominal;
                }
                ++i;
                ++itPoint;
            }
            result = sum;
            break;
        case 3:
            for (vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {

                if (attributeTypes.at(i) == 0) {
                    int res = pow((*it) - (*itPoint), c);
                    if (res < 0)
                        res *= -1;
                    sum += res;
                }  else {
                    if ((*it) == (*itPoint))
                        sum += 0;
                    else
                        sum += importanceOfNominal;
                }
                ++i;
                ++itPoint;
            }
            result = pow(sum, (1/c));
            break;
    }



    return result;
}


