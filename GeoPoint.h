/* 
 * File:   GeoPoint.h
 * Author: zoizoi
 *
 * Created on 19 December 2010, 22:21
 */

#ifndef _GEOPOINT_H
#define	_GEOPOINT_H
#include <boost/numeric/ublas/vector.hpp>

class GeoPoint {
public:
    GeoPoint(int i,float x,float y,float z);
    GeoPoint(int i);
    GeoPoint(const GeoPoint& orig);
    virtual ~GeoPoint();
    void addNeighbour(int n);
    float x,y,z;
    int index;
    int neighbours[36];
    int neighbourCount;
    float getx(){
        return x;
    }
    float gety(){
        return y;
    }
    float getz(){
        return z;
    }
    
    boost::numeric::ublas::vector<float> getUblasVector(){
        boost::numeric::ublas::vector<float> uvec(3);
        uvec(0)=x;
        uvec(1)=y;
        uvec(2)=z;
        return uvec;

    }

    float* getPoint(float scale=1);

private:

};

#endif	/* _GEOPOINT_H */

