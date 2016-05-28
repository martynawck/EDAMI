//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_DATASET_H
#define EDAMI_DATASET_H

#include <array>
#include <map>
#include <memory>
#include "Point.h"


class Dataset {

public:
    std::vector<Point> getPoints();
    void setPoints(std::vector<Point>);
    int getPointsSize();
    bool PrecedingPoint(Point&) const;
    bool FollowingPoint(Point&) const;
    void sortPoints();
    int getPointIndex(Point p);
    void calculateRefPointDistance();
    const Point &getReferencePoint() const;
    void setReferencePoint(const Point &referencePoint);
    int getDistanceMeasure();
    void setDistanceMeasure(int);
    double getCMinkowski();
    void setCMinkowski(double);

	static auto readDatasetFile(std::string const& filename)->std::shared_ptr<Dataset>;

private:
	Dataset(std::vector<Point>);
    Point referencePoint;
    std::vector<Point> points;
    int distanceMeasure;
    double cMinkowski;
 };


#endif //EDAMI_DATASET_H
