/*
 * File:   TemporalChangeFeature2.h
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#ifndef TEMPORALCHANGEFEATURE2_H
#define	TEMPORALCHANGEFEATURE2_H
#include "Feature.h"

class TemporalChangeFeature2 : public Feature{
public:
    TemporalChangeFeature2(float weight,OVASControl*,string name);
    TemporalChangeFeature2(const TemporalChangeFeature2& orig);
    virtual ~TemporalChangeFeature2();
    void scoreFeature(GeoPoint* view);
private:
    float** prevFrameData;
};

#endif	/* TEMPORALCHANGEFEATURE2_H */

