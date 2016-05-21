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
    Point (vector <double> );
    Point();
    vector <double> getAttributes() const;
    void setAttributes (vector <double> );
    set <Point> getKNeighbourhoodIndex() const;
    void addPointToKNeighbourhoodIndex(Point);
    void deletePointFromKNeighbourhoodIndex(Point);
    int getSizeOfKNeighbourhoodIndex () const;
    double getRefPointDistance() const;
    void setRefPointDistance(double refPointDistance);

    double euclideanDistance (Point point) const;

    bool operator<(const Point &item) const {
        return (values < item.values);
    }
    bool operator==(const Point &item) const  {
        return (values == item.values);
    }




private:
    vector <double> values;
    set <Point> kNeighbourhoodIndex;
    double refPointDistance;

};


#endif //EDAMI_POINT_H
