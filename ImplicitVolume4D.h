/* 
 * File:   ImplicitVolume4D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 20:05
 */

#ifndef IMPLICITVOLUME4D_H
#define	IMPLICITVOLUME4D_H

#include "Volume4D.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class ImplicitVolume4D : Volume4D{
public:
    ImplicitVolume4D(){};
    ImplicitVolume4D(int xdim, int ydim, int zdidma,int numSteps);
    ImplicitVolume4D(const ImplicitVolume4D& orig);
    virtual ~ImplicitVolume4D();
    virtual float getVoxelValue(int x,int y,int z,int step){ return 0;}
    
    


private:
    int xdim,ydim,zdim;
};

#endif	/* IMPLICITVOLUME4D_H */

