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
	Dataset(std::vector<std::shared_ptr<Point>>);
	std::vector<std::shared_ptr<Point>> getPoints();
    void setPoints(std::vector<std::shared_ptr<Point>>);
    int getPointsSize();
    bool PrecedingPoint(std::shared_ptr<Point> &point) const;
    bool FollowingPoint(std::shared_ptr<Point> &point) const;
    void sortPoints();
    int getPointIndex(std::shared_ptr<Point> p);
    void calculateRefPointDistance();
    const Point &getReferencePoint() const;
    void setReferencePoint(const Point &referencePoint);
    int getDistanceMeasure();
    void setDistanceMeasure(int);
    double getCMinkowski();
    void setCMinkowski(double);

	static auto readDatasetFile(std::string const& filename)->std::shared_ptr<Dataset>;

private:
    Point referencePoint;
	std::vector<std::shared_ptr<Point>> points;
    int distanceMeasure;
    double cMinkowski;
 };


#endif //EDAMI_DATASET_H
