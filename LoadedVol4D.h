/* 
 * File:   LoadedVol4D.h
 * Author: zoizoi
 *
 * Created on 21 May 2011, 16:32
 */

#ifndef LOADEDVOL4D_H
#define	LOADEDVOL4D_H
#include "OVASControl.h"
#include "ImplicitVolume4D.h"
#include <string>

class LoadedVol4D :public ImplicitVolume4D{
public:
    LoadedVol4D(OVASControl* oc,string* filename);
    LoadedVol4D(const LoadedVol4D& orig);
    virtual ~LoadedVol4D();
    float getVoxelValue(int x, int y, int z, int step);
     
    
    
private:

};

#endif	/* LOADEDVOL4D_H */

