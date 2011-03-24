/* 
 * File:   MovingAAElipsoid.h
 * Author: zoizoi
 *
 * Created on 23 March 2011, 18:54
 */

#ifndef MOVINGAAELIPSOID_H
#define	MOVINGAAELIPSOID_H

#include "OVASControl.h"


class MovingAAElipsoid {
public:
    MovingAAElipsoid(OVASControl* oc,float px,float py,float pz,float vx,float vy,float vz,float sx,float sy,float sz,float w);
    MovingAAElipsoid(const MovingAAElipsoid& orig);
    virtual ~MovingAAElipsoid();
    float getContribAt(int x,int y,int z,int step);


private:
    OVASControl* oc;
    float px,py,pz,vx,vy,vz,sx,sy,sz,weight;

};

#endif	/* MOVINGAAELIPSOID_H */

