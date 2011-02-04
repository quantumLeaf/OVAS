/* 
 * File:   FeatureWeights.h
 * Author: zoizoi
 *
 * Created on 03 February 2011, 22:00
 */

#ifndef FEATUREWEIGHTS_H
#define	FEATUREWEIGHTS_H

class FeatureWeights {
public:
    FeatureWeights();
    FeatureWeights(const FeatureWeights& orig);
    virtual ~FeatureWeights();
    float areaWeight,topologyWeight,temporalChangeWeight,curvatureWeight;
private:

};

#endif	/* FEATUREWEIGHTS_H */

