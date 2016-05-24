//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_POINT_H
#define EDAMI_POINT_H

#include <array>
#include <vector>
#include <set>

using namespace std;

class Point {

public:

    Point (vector <double>, int );
    Point();
    vector <double> getAttributes() const;
    void setAttributes (vector <double> );
    vector <Point>& getKNeighbourhoodIndex();
    void setKNeighbourhoodIndex(vector<Point>);
    void addPointToKNeighbourhoodIndex(Point);
    void deletePointFromKNeighbourhoodIndex(Point);
    int getSizeOfKNeighbourhoodIndex () const;
    double getDistance() const;
    void setDistance(double refPointDistance);
    double euclideanDistance (Point ) const;
    double getEpsilon();
    void clearKNeighbourhood();
    void sortKNeighbours();
    void setEpsilon(double);

    int getId ();
    void setId(int );

    bool operator<(const Point &item) const {
        return (values < item.values);
    }
    bool operator==(const Point &item) const  {
        return (values == item.values);
    }

    Point& operator= (const Point& point) {

        this->values = point.values;
        this->kNeighbourhoodIndex = point.kNeighbourhoodIndex;
        this->dist = point.dist;
        this->epsilon = point.epsilon;

        return *this;
    }

private:
    vector <double> values;
    vector <Point> kNeighbourhoodIndex;
    double dist;
    double epsilon;
    int id;

};


#endif //EDAMI_POINT_H
