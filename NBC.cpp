//
// Created by Martyna on 2016-05-21.
//

#include <iostream>
#include <algorithm>
#include "NBC.h"

void NBC::TI_k_Neighbouthood_Index(Dataset& dataset, int k) {
    dataset.calculateRefPointDistance();
    dataset.sortPoints();
    int i=0;
   for (vector<Point>::iterator it = dataset.getPoints().begin(); it != dataset.getPoints().end(); ++it) {

     //  cout<<it->getDistance()<<endl;
     //  cout<<indx<<endl;
       try {
         //  it->setDistance(1);
          // vector<Point> k_Neighbourhood = vector<Point>();
           it->setKNeighbourhoodIndex(TI_k_Neighborhood(dataset,*it,k));

           it->addPointToKNeighbourhoodIndex(*it);

           cout << i << endl;
       } catch (exception e) {
           cout<<e.what()<<endl;
       }

       i++;
   }
    cout<<endl;
}
vector<Point> NBC::TI_k_Neighborhood(Dataset dataset, Point& point, int k) {
    Point b = point;
    Point f = point;
    bool backwardSearch = dataset.PrecedingPoint(b);
    bool forwardSearch = dataset.FollowingPoint(f);
    vector<Point> k_Neighbourhood = vector<Point>();
    int i = 0;

    // k_Neighbourhood.push_back(f);
    //  it->setKNeighbourhoodIndex(k_Neighbourhood);
    //it->setKNeighbourhoodIndex(TI_k_Neighborhood(*dataset,*it, k));
    //         Point thisPt = *it;
//           thisPt.clearKNeighbourhood();
 //   int i = 0;

    Find_First_k_Candidate_Neighbours_Forward_and_Backward(dataset, point, b, f,
        backwardSearch, forwardSearch, k_Neighbourhood, k, i);

    Find_First_k_Candidate_Neighbours_Backward(dataset, point, b, backwardSearch, k_Neighbourhood, k, i);

    Find_First_k_Candidate_Neighbours_Forward(dataset, point, f, forwardSearch, k_Neighbourhood, k, i);


    cout<<"wielkosc zbioru "<<k_Neighbourhood.size() <<endl;
    vector<Point>::iterator it;

    double epsilon = -1;
    for (it = k_Neighbourhood.begin(); it != k_Neighbourhood.end(); it++) {
        double distance = point.euclideanDistance(*it);
        if (distance > epsilon)
            epsilon = distance;

    }

    point.setEpsilon(epsilon);

    Verify_k_Candidate_Neighbours_Backward(dataset, point, b, backwardSearch, k_Neighbourhood, k);

    Verify_k_Candidate_Neihbours_Forward(dataset, point, f, forwardSearch, k_Neighbourhood, k);

    //if (forwardSearch)
     //   k_Neighbourhood.push_back(f);
    return k_Neighbourhood;
}


bool cmp(const Point &p1, const Point &p2) {
    return p1.getDistance() < p2.getDistance();
}

void NBC::Find_First_k_Candidate_Neighbours_Forward_and_Backward(Dataset dataset, Point p, Point b,
                                                                        Point f, bool backwardSearch, bool forwardSearch,
                                                                          vector<Point>& k_Neighbourhood, int k, int i) {
    while (forwardSearch && backwardSearch && i < k) {
        if (p.getDistance() - b.getDistance() -
                f.getDistance() - p.getDistance()) {
            b.setDistance(b.euclideanDistance(p));
            i++;
            k_Neighbourhood.push_back(b);
            sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
            backwardSearch = dataset.PrecedingPoint(b);
        }
        else {
            f.setDistance(f.euclideanDistance(p));
            i++;
            k_Neighbourhood.push_back(f);
            sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
            forwardSearch = dataset.FollowingPoint(f);
        }
    }

}


void NBC::Find_First_k_Candidate_Neighbours_Backward(Dataset dataset, Point p, Point b, bool backwardSearch,

                                                            vector<Point>& k_Neighbourhood, int k, int i) {
     while (backwardSearch && i < k) {
         b.setDistance(p.euclideanDistance(b));
         i++;
         k_Neighbourhood.push_back(b);
         sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
         backwardSearch = dataset.PrecedingPoint(b);
    }
}
void NBC::Find_First_k_Candidate_Neighbours_Forward (Dataset dataset, Point p, Point f, bool forwardSearch,
                                                                                   vector<Point>& k_Neighbourhood, int k, int i){
    while (forwardSearch && i < k) {
        f.setDistance(p.euclideanDistance(f));
        i++;
        k_Neighbourhood.push_back(f);
        sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
        forwardSearch = dataset.FollowingPoint(f);
    }
}
void NBC::Verify_k_Candidate_Neighbours_Backward(Dataset dataset, Point p, Point b, bool backwardSearch,
                                                 vector<Point>& k_Neighbourhood, int k){
    while (backwardSearch && (p.getDistance() - b.getDistance() <= p.getEpsilon())) {
        double distance = b.euclideanDistance(p);
        double epsil = p.getEpsilon();
        if (distance < p.getEpsilon()) {
            int i = 0;
            for (vector<Point>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                if (p.getEpsilon() == it->getDistance())
                    i++;
            }

            cout <<i<<endl;
            if (k_Neighbourhood.size() - i >= k - 1) {
                cout<<"ERASE"<<endl;
                auto it = std::remove_if(k_Neighbourhood.begin(), k_Neighbourhood.end(), [&p](const Point& point)
                { return point.getDistance() == p.getEpsilon(); });
                k_Neighbourhood.erase(it, k_Neighbourhood.end());

                Point e = b;
                e.setDistance(distance);
                e.clearKNeighbourhood();
                k_Neighbourhood.push_back(e);
                sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);

                int max_dist = 0;
                for (vector<Point>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                    if (it->getDistance() > max_dist)
                        max_dist = it->getDistance();
                }
                p.setEpsilon(max_dist);
            } else {
                Point e = b;
                e.setDistance(distance);
                e.clearKNeighbourhood();
                k_Neighbourhood.push_back(e);
                sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);

            }

        } else {
            Point e = b;
            distance = p.getEpsilon();
            e.setDistance(distance);
            e.clearKNeighbourhood();
            k_Neighbourhood.push_back(e);
            sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
        }
        backwardSearch = dataset.PrecedingPoint(b);
    }
}
void NBC::Verify_k_Candidate_Neihbours_Forward(Dataset dataset, Point p, Point f, bool forwardSearch,
                                               vector<Point>& k_Neighbourhood, int k) {

    while (forwardSearch && (f.getDistance() - p.getDistance() <= p.getEpsilon())) {
        double distance = f.euclideanDistance(p);
        if (distance < p.getEpsilon()) {
            int i = 0;
            for (vector<Point>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                if (p.getEpsilon() == it->getDistance())
                    i++;
            }

            if (k_Neighbourhood.size() - i >= k - 1) {
                auto it = std::remove_if(k_Neighbourhood.begin(), k_Neighbourhood.end(), [&p](const Point& point)
                { return point.getDistance() == p.getEpsilon(); });
                k_Neighbourhood.erase(it, k_Neighbourhood.end());

                Point e = f;
                e.setDistance(distance);
                e.clearKNeighbourhood();
                k_Neighbourhood.push_back(e);
                sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);

                int max_dist = 0;
                for (vector<Point>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                    if (it->getDistance() > max_dist)
                        max_dist = it->getDistance();
                }
                p.setEpsilon(max_dist);
            } else {
                Point e = f;
                e.setDistance(distance);
                e.clearKNeighbourhood();
                k_Neighbourhood.push_back(e);
                sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
            }

        } else {
            Point e = f;
            distance = p.getEpsilon();
            e.setDistance(distance);
            e.clearKNeighbourhood();
            k_Neighbourhood.push_back(e);
            sort(k_Neighbourhood.begin(), k_Neighbourhood.end(), cmp);
        }
        forwardSearch = dataset.PrecedingPoint(f);
    }
}