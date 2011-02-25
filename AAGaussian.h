/* 
 * File:   AAGaussian.h
 * Author: zoizoi
 *
 * Created on 23 February 2011, 20:21
 */

#ifndef AAGAUSSIAN_H
#define	AAGAUSSIAN_H

class AAGaussian {
public:
    AAGaussian(float _x,float _y,float _z,float _sx, float _sy, float _sz,float _w);
    AAGaussian(const AAGaussian& orig);
    virtual ~AAGaussian();
    float x,y,z,w;
    float sx,sy,sz;

private:

};

#endif	/* AAGAUSSIAN_H */

