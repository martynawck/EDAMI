//
// Created by Martyna on 2016-05-21.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "NBC.h"

using std::vector;
using std::shared_ptr;
using namespace std;

void Find_First_k_Candidate_Neighbours_Forward_and_Backward(Dataset dataset, shared_ptr<Point>& p, shared_ptr<Point>& b, shared_ptr<Point> &f,
                                                            bool& backwardSearch, bool& forwardSearch,
                                                            std::set<shared_ptr<Point>, Point::classcomp>& k_Neighbourhood, int k, int& i) {
    while (forwardSearch && backwardSearch && i < k) {
        if (p->getDistanceFromReference() - b->getDistanceFromReference() <
                f->getDistanceFromReference() - p->getDistanceFromReference()) {
            auto e = b;
            e->setDistance(b->calculateDistanceMeasure(*p, dataset.getDistanceMeasure(), dataset.getCMinkowski()));
            i++;
            k_Neighbourhood.insert(e);
            backwardSearch = dataset.PrecedingPoint(b);
        }
        else {
            auto e = f;
            e->setDistance(f->calculateDistanceMeasure(*p, dataset.getDistanceMeasure(),dataset.getCMinkowski()));
            i++;
            k_Neighbourhood.insert(e);
            forwardSearch = dataset.FollowingPoint(f);
        }
    }
}

void Find_First_k_Candidate_Neighbours_Backward(Dataset dataset, shared_ptr<Point> &p, shared_ptr<Point>& b, bool& backwardSearch,
                                                std::set<shared_ptr<Point>, Point::classcomp>& k_Neighbourhood, int k, int& i) {
	while (backwardSearch && i < k) {
         auto e = b;
         e->setDistance(b->calculateDistanceMeasure(*p, dataset.getDistanceMeasure(),dataset.getCMinkowski()));
         i++;
         k_Neighbourhood.insert(e);
         backwardSearch = dataset.PrecedingPoint(b);
    }
}

void Find_First_k_Candidate_Neighbours_Forward (Dataset dataset, shared_ptr<Point> &p, shared_ptr<Point>& f, bool& forwardSearch,
                                               std::set<shared_ptr<Point>, Point::classcomp>& k_Neighbourhood, int k, int& i){

    while (forwardSearch && i < k) {
        auto e = f;
        e->setDistance(f->calculateDistanceMeasure(*p, dataset.getDistanceMeasure(), dataset.getCMinkowski()));
        i++;
        k_Neighbourhood.insert(e);
        forwardSearch = dataset.FollowingPoint(f);
    }
}

void Verify_k_Candidate_Neighbours_Backward(Dataset dataset, shared_ptr<Point> &p, shared_ptr<Point>& b, bool& backwardSearch,
                                                 std::set<shared_ptr<Point>, Point::classcomp>& k_Neighbourhood, int k){

    while (backwardSearch && (p->getDistanceFromReference() - b->getDistanceFromReference() <= p->getEpsilon())) {
        double distance = b->calculateDistanceMeasure(*p, dataset.getDistanceMeasure(), dataset.getCMinkowski());
        
		if (distance < p->getEpsilon()) {
            int i = 0;
            for (auto it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); it++) {
                if (p->getEpsilon() == (*it)->getDistance())
                    i++;
            }

            if (k_Neighbourhood.size() - i >= k - 1) {
                // delete each element with distance == p.epsilon
                for (auto it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); ) {
                    if (p->getEpsilon() == (*it)->getDistance()) {
                        it = k_Neighbourhood.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                auto e = b;
                e->setDistance(distance);
                k_Neighbourhood.insert(e);

                int max_dist = 0;
                for (auto point: k_Neighbourhood) {
                    if (point->getDistance() > max_dist)
                        max_dist = point->getDistance();
                }
				p->setEpsilon(p->calculateDistanceMeasure(**(--k_Neighbourhood.end()),
					dataset.getDistanceMeasure(), dataset.getCMinkowski()));

            } else {
                auto e = b;
                e->setDistance(distance);
                k_Neighbourhood.insert(e);
            }
        } else if(distance - p->getEpsilon() < MIN_DIFFERENCE) {
            auto e = b;
            e->setDistance(distance);

            k_Neighbourhood.insert(e);
        }
        backwardSearch = dataset.PrecedingPoint(b);
    }
}

void Verify_k_Candidate_Neihbours_Forward(Dataset dataset, shared_ptr<Point>& p, shared_ptr<Point>& f, bool& forwardSearch,
                                               std::set<std::shared_ptr<Point>, Point::classcomp>& k_Neighbourhood, int k) {
    while (forwardSearch && (f->getDistanceFromReference() - p->getDistanceFromReference() <= p->getEpsilon())) {
        double distance = f->calculateDistanceMeasure(*p, dataset.getDistanceMeasure(), dataset.getCMinkowski());
        if (distance < p->getEpsilon()) {
            int i = 0;
            for (auto point: k_Neighbourhood) {
                if (p->getEpsilon() == point->getDistance())
                    i++;
            }

            if (k_Neighbourhood.size() - i >= k - 1) {


                for (auto it = k_Neighbourhood.begin(); it!= k_Neighbourhood.end(); ) {
                    if (p->getEpsilon() == (*it)->getDistance()) {
                        it = k_Neighbourhood.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
                auto e = f;
                e->setDistance(distance);
                k_Neighbourhood.insert(e);

                p->setEpsilon(p->calculateDistanceMeasure(**(--k_Neighbourhood.end()), 
					dataset.getDistanceMeasure(), dataset.getCMinkowski()));
            } else {

                auto e = f;
                e->setDistance(distance);
                k_Neighbourhood.insert(e);
            }
        } else if(abs(distance - p->getEpsilon()) < MIN_DIFFERENCE) {

            auto e = f;
            e->setDistance(distance);
            k_Neighbourhood.insert(e);
        }
        forwardSearch = dataset.FollowingPoint(f);
    }
}

std::set<shared_ptr<Point>, Point::classcomp> TI_k_Neighborhood(Dataset dataset, shared_ptr<Point> point, int k) {
	auto b = point;
	auto f = point;
	// search for preceding and following points

    bool backwardSearch = dataset.PrecedingPoint(b);
    bool forwardSearch = dataset.FollowingPoint(f);
	//initialize set
	std::set<shared_ptr<Point>, Point::classcomp> k_Neighbourhood;
	int i = 0;

	Find_First_k_Candidate_Neighbours_Forward_and_Backward(dataset, point, b, f, backwardSearch, forwardSearch, k_Neighbourhood, k, i);
	Find_First_k_Candidate_Neighbours_Backward(dataset, point, b, backwardSearch, k_Neighbourhood, k, i);
	Find_First_k_Candidate_Neighbours_Forward(dataset, point, f, forwardSearch, k_Neighbourhood, k, i);

	// find epsilon for point -> max of the distances of its neighbours

	point->setEpsilon(point->calculateDistanceMeasure(**(--k_Neighbourhood.end()), 
		dataset.getDistanceMeasure(), dataset.getCMinkowski()));

    //verify candidates
	Verify_k_Candidate_Neighbours_Backward(dataset, point, b, backwardSearch, k_Neighbourhood, k);
	Verify_k_Candidate_Neihbours_Forward(dataset, point, f, forwardSearch, k_Neighbourhood, k);

	return k_Neighbourhood;
}


vector<shared_ptr<Point>> TI_k_Neighbourhood_Index(Dataset& dataset, int k) {
    // calculate distances between point and the reference points
    dataset.calculateRefPointDistance();
    dataset.sortPoints();

    // sort points in non decreasing order
    int i=0;
    // for each point in the dataset
   for (auto point: dataset.getPoints()) {
       try {

           // insert this set into its neighbourhood list
		   auto neighbours = TI_k_Neighborhood(dataset, point, k);

		   point->setKNeighbourhoodIndex(neighbours);
		   for (auto neighbour: neighbours) {
			   neighbour->appendReverseNeighbour(point);
		   }
       } catch (std::exception e) {
           std::cout << e.what() << std::endl;
       }

       ++i;
   }
    std::cout << std::endl;

	return dataset.getPoints();
}