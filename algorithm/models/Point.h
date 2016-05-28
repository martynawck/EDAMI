//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_POINT_H
#define EDAMI_POINT_H

#include <array>
#include <memory>
#include <set>
#include <vector>

class Cluster;

class Point {

public:

    struct classcomp {
        bool operator() (const Point& lhs, const Point& rhs) const
        {return lhs.getDistance() <rhs.getDistance();}
    };

public:
	Point();
    Point(std::vector <double>, int=0);
    std::vector<double> getAttributes() const;
    void setAttributes (std::vector <double> );
    std::set<Point,classcomp>& getKNeighbourhoodIndex();
    void setKNeighbourhoodIndex(std::set<Point, classcomp>);
    void addPointToKNeighbourhoodIndex(Point);
	void appendReverseNeighbour(Point);
    void deletePointFromKNeighbourhoodIndex(Point);
    int getSizeOfKNeighbourhoodIndex () const;
    double getDistance() const;
    void setDistance(double refPointDistance);
    double calculateDistanceMeasure(Point, int, double) const;
    double getEpsilon();
    void clearKNeighbourhood();
    void sortKNeighbours();
    void setEpsilon(double);

    int getId ();
    void setId(int);

	double ndf();
	bool clustered();
	void clusterize(Cluster cluster);

    bool operator<(const Point &item) const {
        return (values < item.values);
    }
    bool operator==(const Point &item) const  {
        return (id == item.id);
    }

    Point& operator= (const Point& point) {

        this->values = point.values;
        this->kNeighbourhoodIndex = point.kNeighbourhoodIndex;
        this->dist = point.dist;
        this->epsilon = point.epsilon;
        this->id = point.id;

        return *this;
    }

private:


    std::set<Point, classcomp> kNeighbourhoodIndex;
	std::set<Point> reverseNeighbourhood;

    std::vector<double> values;
    double dist;
    double epsilon;
    unsigned int id;

	int cluster_id = -1;
};


#endif //EDAMI_POINT_H
