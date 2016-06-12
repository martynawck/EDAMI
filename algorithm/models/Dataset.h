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
	std::vector<bool> getTypeOfAttributes();
	void setTypeOfAttributes(std::vector<bool>);
	void setImportanceOfNominal(double);
	double getImportanceOfNominal();

	static auto readDatasetFile(std::string const& filename, std::vector<bool>& typeOfAttribute, double alpha, int typeOfNormalization)->std::shared_ptr<Dataset>;
	void readReferencePointFile(std::string const& filename, std::vector<bool>& typeOfAttribute);
	double findMaxInAttributeColumn(int column, bool typeOfAttribute);
	double findMinInAttributeColumn(int column, bool typeOfAttribute);
private:
    Point referencePoint;
	std::vector<std::shared_ptr<Point>> points;
    int distanceMeasure;
    double cMinkowski;
	std::vector<bool> typeOfAttributes;
	double importanceOfNominal;


};


#endif //EDAMI_DATASET_H
