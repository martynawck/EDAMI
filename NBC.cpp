//
// Created by Martyna on 2016-05-21.
//

#include "NBC.h"

void NBC::TI_k_Neighbouthood_Index(Dataset& dataset, int k) {
    dataset.calculateRefPointDistance();
    dataset.sortPoints();

    for (vector<Point>::iterator it = dataset.getPoints().begin(); it != dataset.getPoints().end(); ++it) {

    }
}
set<Point> NBC::TI_k_Neighborhood(Dataset dataset, Point point, int k) {

}
set <Point> NBC::Find_First_k_Candidate_Neighbours_Forward_and_Backward(Dataset, Point, Point, Point, bool, bool, bool, int, int) {

}
set <Point> NBC::Find_First_k_Candidate_Neighbours_Backward(Dataset, Point, Point, bool, bool, int, int) {

}
set <Point> NBC::Find_First_k_Candidate_Neighbours_Forward (Dataset, Point, Point, bool, bool, int, int){

}
void NBC::Verify_k_Candidate_Neighbours_Backward(Dataset, Point,Point, bool, bool, int){

}
void NBC::Verify_k_Candidate_Neihbours_Forward(Dataset,Point,Point,bool,bool,int) {

}