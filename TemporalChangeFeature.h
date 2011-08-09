/* 
 * File:   TemporalChangeFeature.h
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#ifndef TEMPORALCHANGEFEATURE_H
#define	TEMPORALCHANGEFEATURE_H
#include "Feature.h"

class TemporalChangeFeature : public Feature{
public:
    TemporalChangeFeature(float weight,OVASControl*,string name);
    TemporalChangeFeature(const TemporalChangeFeature& orig);
    virtual ~TemporalChangeFeature();
    void scoreFeature(GeoPoint* view);
private:
    int** intAreaData;
};

#endif	/* TEMPORALCHANGEFEATURE_H */

