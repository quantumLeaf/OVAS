/* 
 * File:   FlyingSaucersVol4D.h
 * Author: zoizoi
 *
 * Created on 23 February 2011, 20:04
 */

#ifndef FLYINGSAUCERSVOL4D_H
#define	FLYINGSAUCERSVOL4D_H
#include "OVASControl.h"
#include "ImplicitVolume4D.h"
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_vector.h>


class FlyingSaucersVol4D : public ImplicitVolume4D{
public:
    FlyingSaucersVol4D(OVASControl* oc);
    FlyingSaucersVol4D(const FlyingSaucersVol4D& orig);
    virtual ~FlyingSaucersVol4D();
    float getVoxelValue(int x, int y, int z, int step);
private:

};

#endif	/* FLYINGSAUCERSVOL4D_H */

