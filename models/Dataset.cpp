//
// Created by Martyna on 2016-05-21.
//

#include <algorithm>
#include "Dataset.h"


Dataset::Dataset() {}

Dataset::Dataset(vector<Point> points) {
    this->points = points;
}

vector<Point> Dataset::getPoints() {
    return this->points;
}

void Dataset::setPoints(vector<Point> points) {
    this->points = points;
}

map<string, vector<Point>> Dataset::getClusters() {
    return this->clusters;
};

int Dataset::getPointsSize() {
    return points.size();
}

bool Dataset::PrecedingPoint(Point& preceding, Point point) const {

    vector<Point>::const_iterator it = find(points.begin(), points.end(), point);
    if (it != points.begin()) {
        preceding = *it;
        return true;
    }
    return false;
}

bool Dataset::FollowingPoint(Point& following, Point point) const {
    vector<Point>::const_iterator it = find(points.begin(), points.end(), point);
    if (it != points.end()) {
        following = *it;
        return true;
    }
    return false;
}

bool cmd(const Point &p1, const Point &p2) {
    return p1.getRefPointDistance() < p2.getRefPointDistance();
}

void Dataset::sortPoints(){
    sort(points.begin(), points.end(), cmd);
}

void Dataset::calculateRefPointDistance() {

    vector <double> vector1 (9, 0.0);
    Point refPoint = Point(vector1);
    for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
        double distance = refPoint.euclideanDistance(*it);
        it->setRefPointDistance(distance);
    }
}



