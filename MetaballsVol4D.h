/* 
 * File:   MetaballsVol4D.h
 * Author: zoizoi
 *
 * Created on 26 January 2011, 22:10
 */

#ifndef METABALLSVOL4D_H
#define	METABALLSVOL4D_H

#include "ImplicitVolume4D.h"
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_vector.h>


class MetaballsVol4D : public ImplicitVolume4D {
public:
    MetaballsVol4D(OVASControl* oc,float);
    MetaballsVol4D(const MetaballsVol4D& orig);
    virtual ~MetaballsVol4D();
    float getVoxelValue(int x, int y, int z, int step);
private:
    float twist;

};

#endif	/* METABALLSVOL4D_H */

