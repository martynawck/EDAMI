//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_DATASET_H
#define EDAMI_DATASET_H

#include <array>
#include <map>
#include "Point.h"

using namespace std;

class Dataset {

public :
    Dataset();
    Dataset(vector<Point>);
    vector<Point> getPoints();
    void setPoints(vector<Point>);
    int getPointsSize();
    map<string, vector<Point>> getClusters();
    bool PrecedingPoint(Point&, Point) const;
    bool FollowingPoint(Point&, Point) const;
    void sortPoints();
    void calculateRefPointDistance();
    const Point &getReferencePoint() const;
    void setReferencePoint(const Point &referencePoint);

private:
    Point referencePoint;
    vector <Point> points;
    map <string, vector<Point>> clusters;

 };


#endif //EDAMI_DATASET_H
