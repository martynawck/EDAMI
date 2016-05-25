//
// Created by Martyna on 2016-05-21.
//

#include <algorithm>
#include "Dataset.h"


Dataset::Dataset() {
    this->points = vector<Point>();
    this->referencePoint = Point();
    this->clusters = map<string,vector<Point>>();
    this->cMinkowski = 0;
}

Dataset::Dataset(vector<Point> points) {
    this->points = points;
    this->referencePoint = Point();
    clusters = map<string,vector<Point>>();
}

vector<Point>& Dataset::getPoints() {
    return this->points;
}

void Dataset::setPoints(vector<Point> points) {
    this->points = points;
}

map<string, vector<Point>>& Dataset::getClusters() {
    return this->clusters;
};

int Dataset::getPointsSize() {
    return points.size();
}

int Dataset::getDistanceMeasure() {
    return  this->distanceMeasure;
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

    vector <double> vector1 (9, 0.0);
    referencePoint = Point(vector1,-1);
    for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
        double distance = referencePoint.calculateDistanceMeasure(*it,this->getDistanceMeasure(), this->getCMinkowski());
        it->setDistance(distance);
    }
}

double Dataset::getCMinkowski() {
    return  this->cMinkowski;
}

void Dataset::setCMinkowski(double c) {
    this->cMinkowski = c;
}

const Point& Dataset::getReferencePoint() const {
    return referencePoint;
}

void Dataset::setReferencePoint(const Point &referencePoint) {
    Dataset::referencePoint = referencePoint;
}



