/* 
 * File:   MovingAAElipsoid.h
 * Author: zoizoi
 *
 * Created on 23 March 2011, 18:54
 */

#ifndef MOVINGAAELIPSOID_H
#define	MOVINGAAELIPSOID_H

class MovingAAElipsoid {
public:
    MovingAAElipsoid(float px,float py,float pz,float vx,float vy,float vz,float sx,float sy,float sz,float w);
    MovingAAElipsoid(const MovingAAElipsoid& orig);
    virtual ~MovingAAElipsoid();
    float getContribAt(int x,int y,int z,int t);


private:

};

#endif	/* MOVINGAAELIPSOID_H */

