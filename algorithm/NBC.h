//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_NBC_H
#define EDAMI_NBC_H

#include <vector>
#include "models/Dataset.h"

static const double MIN_DIFFERENCE = 0.00001;
std::vector<Point> TI_k_Neighbourhood_Index(Dataset&, int);
#endif //EDAMI_NBC_H
