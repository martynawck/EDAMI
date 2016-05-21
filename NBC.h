//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_NBC_H
#define EDAMI_NBC_H


#include "models/Dataset.h"

class NBC {

public:
    void TI_k_Neighbouthood_Index(Dataset&, int);

private:
    set<Point> TI_k_Neighborhood(Dataset, Point, int);
    set <Point> Find_First_k_Candidate_Neighbours_Forward_and_Backward(Dataset, Point, Point, Point, bool, bool, bool, int, int);
    set <Point> Find_First_k_Candidate_Neighbours_Backward(Dataset, Point, Point, bool, bool, int, int);
    set <Point> Find_First_k_Candidate_Neighbours_Forward (Dataset, Point, Point, bool, bool, int, int);
    void Verify_k_Candidate_Neighbours_Backward(Dataset, Point,Point, bool, bool, int);
    void Verify_k_Candidate_Neihbours_Forward(Dataset,Point,Point,bool,bool,int);
};


#endif //EDAMI_NBC_H
