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
        bool operator() (std::shared_ptr<Point> const& lhs, std::shared_ptr<Point> const& rhs) const
        {return lhs->getDistance() < rhs->getDistance();}
    };

public:
	Point();
    Point(std::vector<double>, int=0);
    std::vector<double> getAttributes() const;
    void setAttributes (std::vector <double> );
    std::set<std::shared_ptr<Point>, classcomp> getKNeighbourhoodIndex();
    void setKNeighbourhoodIndex(std::set<std::shared_ptr<Point>, classcomp>);
    void addPointToKNeighbourhoodIndex(std::shared_ptr<Point>);
	void appendReverseNeighbour(std::shared_ptr<Point>);
    void deletePointFromKNeighbourhoodIndex(std::shared_ptr<Point>);
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

	bool operator==(Point const& item) const {
		return id == item.id;
	}

private:
    std::set<std::shared_ptr<Point>, classcomp> kNeighbourhoodIndex;
	std::set<std::shared_ptr<Point>, classcomp> reverseNeighbourhood;

    std::vector<double> values;
    double dist;
    double epsilon;
    unsigned int id;

	int cluster_id = -1;
};


#endif //EDAMI_POINT_H
