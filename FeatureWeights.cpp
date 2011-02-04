/* 
 * File:   FeatureWeights.cpp
 * Author: zoizoi
 * 
 * Created on 03 February 2011, 22:00
 */

#include "FeatureWeights.h"

FeatureWeights::FeatureWeights() {
    areaWeight = 0;
    topologyWeight = 0;
    curvatureWeight = 0;
    temporalChangeWeight = 0;
}

FeatureWeights::FeatureWeights(const FeatureWeights& orig) {
}

FeatureWeights::~FeatureWeights() {
}

