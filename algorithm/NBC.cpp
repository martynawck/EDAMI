//
// Created by Martyna on 2016-05-21.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "NBC.h"

using std::vector;

void Find_First_k_Candidate_Neighbours_Forward_and_Backward(Dataset dataset, Point p, Point b,
                                                                        Point f, bool backwardSearch, bool forwardSearch,
                                                                 std::set<Point, Point::classcomp>& k_Neighbourhood, int k, int i) {
    while (forwardSearch && backwardSearch && i < k) {
        if (p.getDistance() - b.getDistance() -
                f.getDistance() - p.getDistance()) {
            Point e = b;
            e.setDistance(b.calculateDistanceMeasure(p,dataset.getDistanceMeasure(),dataset.getCMinkowski()));
            i++;
            k_Neighbourhood.insert(e);
            backwardSearch = dataset.PrecedingPoint(b);
        }
        else {
            Point e = f;
            e.setDistance(f.calculateDistanceMeasure(p,dataset.getDistanceMeasure(),dataset.getCMinkowski()));
            i++;
            k_Neighbourhood.insert(e);
            forwardSearch = dataset.FollowingPoint(f);
        }
    }

}


void Find_First_k_Candidate_Neighbours_Backward(Dataset dataset, Point p, Point b, bool backwardSearch,
                                                     std::set<Point, Point::classcomp>& k_Neighbourhood, int k, int i) {
     while (backwardSearch && i < k) {
         Point e = b;
         e.setDistance(b.calculateDistanceMeasure(p,dataset.getDistanceMeasure(),dataset.getCMinkowski()));
         i++;
         k_Neighbourhood.insert(e);
         backwardSearch = dataset.PrecedingPoint(b);
    }
}
void Find_First_k_Candidate_Neighbours_Forward (Dataset dataset, Point p, Point f, bool forwardSearch,
                                                     std::set<Point, Point::classcomp>& k_Neighbourhood, int k, int i){
    while (forwardSearch && i < k) {
        Point e = f;
        e.setDistance(f.calculateDistanceMeasure(p,dataset.getDistanceMeasure(), dataset.getCMinkowski()));
        i++;
        k_Neighbourhood.insert(e);
        forwardSearch = dataset.FollowingPoint(f);
    }
}
void Verify_k_Candidate_Neighbours_Backward(Dataset dataset, Point p, Point b, bool backwardSearch,
                                                 std::set<Point, Point::classcomp>& k_Neighbourhood, int k){
    while (backwardSearch && (p.getDistance() - b.getDistance() <= p.getEpsilon())) {
        double distance = b.calculateDistanceMeasure(p, dataset.getDistanceMeasure(), dataset.getCMinkowski());
        if (distance < p.getEpsilon()) {
            int i = 0;
            for (std::set<Point, Point::classcomp>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                if (p.getEpsilon() == it->getDistance())
                    i++;
            }

            if (k_Neighbourhood.size() - i >= k - 1) {
                // delete each element with distance == p.epsilon
                for (std::set<Point, Point::classcomp>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); ) {
                    if (p.getEpsilon() == it->getDistance()) {
                        it = k_Neighbourhood.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                Point e = b;
                e.setDistance(distance);
                k_Neighbourhood.insert(e);

                int max_dist = 0;
                for (std::set<Point, Point::classcomp>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                    if (it->getDistance() > max_dist)
                        max_dist = it->getDistance();
                }
                p.setEpsilon(max_dist);
            } else {
                Point e = b;
                e.setDistance(distance);
                k_Neighbourhood.insert(e);
            }

        } else if(distance == p.getEpsilon()) {
            Point e = b;
            e.setDistance(distance);
            k_Neighbourhood.insert(e);
        }
        backwardSearch = dataset.PrecedingPoint(b);
    }
}
void Verify_k_Candidate_Neihbours_Forward(Dataset dataset, Point p, Point f, bool forwardSearch,
                                               std::set<Point,Point::classcomp>& k_Neighbourhood, int k) {

    while (forwardSearch && (f.getDistance() - p.getDistance() <= p.getEpsilon())) {
        double distance = f.calculateDistanceMeasure(p,dataset.getDistanceMeasure(),dataset.getCMinkowski());
        if (distance < p.getEpsilon()) {
            int i = 0;
            for (std::set<Point,Point::classcomp>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                if (p.getEpsilon() == it->getDistance())
                    i++;
            }

            if (k_Neighbourhood.size() - i >= k - 1) {

                for (std::set<Point, Point::classcomp>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); ) {
                    if (p.getEpsilon() == it->getDistance()) {
                        it = k_Neighbourhood.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
                Point e = f;
                e.setDistance(distance);
                k_Neighbourhood.insert(e);

                int max_dist = 0;
                for (std::set<Point, Point::classcomp>::iterator it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                    if (it->getDistance() > max_dist)
                        max_dist = it->getDistance();
                }
                p.setEpsilon(max_dist);
            } else {
                Point e = f;
                e.setDistance(distance);
                k_Neighbourhood.insert(e);
            }

        } else if(distance == p.getEpsilon()) {
            Point e = f;
            e.setDistance(distance);
            k_Neighbourhood.insert(e);
        }
        forwardSearch = dataset.FollowingPoint(f);
    }
}

std::set<Point, Point::classcomp> TI_k_Neighborhood(Dataset dataset, Point& point, int k) {
	Point b = point;
	Point f = point;
	// search for preceding and following points
	bool backwardSearch = dataset.PrecedingPoint(b);
	bool forwardSearch = dataset.FollowingPoint(f);

	//initialize set
	std::set<Point, Point::classcomp> k_Neighbourhood = std::set<Point, Point::classcomp>();
	int i = 0;

	Find_First_k_Candidate_Neighbours_Forward_and_Backward(dataset, point, b, f,
		backwardSearch, forwardSearch, k_Neighbourhood, k, i);
	Find_First_k_Candidate_Neighbours_Backward(dataset, point, b, backwardSearch, k_Neighbourhood, k, i);
	Find_First_k_Candidate_Neighbours_Forward(dataset, point, f, forwardSearch, k_Neighbourhood, k, i);

	// find epsilon for point -> max of the distances of its neighbours
	double epsilon = -1;
	for (std::set<Point, Point::classcomp>::iterator it = k_Neighbourhood.begin(); it != k_Neighbourhood.end(); it++) {
		double distance = point.calculateDistanceMeasure(*it, dataset.getDistanceMeasure(), dataset.getCMinkowski());
		if (distance > epsilon)
			epsilon = distance;

	}
	point.setEpsilon(epsilon);

	//verify candidates
	Verify_k_Candidate_Neighbours_Backward(dataset, point, b, backwardSearch, k_Neighbourhood, k);
	Verify_k_Candidate_Neihbours_Forward(dataset, point, f, forwardSearch, k_Neighbourhood, k);

	return k_Neighbourhood;
}


vector<Point> TI_k_Neighbourhood_Index(Dataset& dataset, int k) {
    // calculate distances between point and the reference points
    dataset.calculateRefPointDistance();
    // sort points in non decreasing order
    dataset.sortPoints();
    int i=0;
    // for each point in the dataset
   for (Point& point: dataset.getPoints()) {
       try {
           // insert this set into its neighbourhood list
		   auto neighbours = TI_k_Neighborhood(dataset, point, k);
		   point.setKNeighbourhoodIndex(neighbours);
		   for (std::set<Point, Point::classcomp>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
			   auto neighbour = *it;
			   neighbour.appendReverseNeighbour(point);
		   }
       } catch (std::exception e) {
           std::cout << e.what() << std::endl;
       }

       ++i;
   }
    std::cout << std::endl;

	return dataset.getPoints();
}