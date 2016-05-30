//
// Created by Martyna on 2016-05-21.
//

#ifndef EDAMI_NBC_H
#define EDAMI_NBC_H

#include <vector>
#include "models/Dataset.h"


std::vector<std::shared_ptr<Point>> TI_k_Neighbourhood_Index(Dataset&, int);
static const double MIN_DIFFERENCE = 0.00001;
#endif //EDAMI_NBC_H
