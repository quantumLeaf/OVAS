/* 
 * File:   GeoPoint.h
 * Author: zoizoi
 *
 * Created on 19 December 2010, 22:21
 */

#ifndef _GEOPOINT_H
#define	_GEOPOINT_H

class GeoPoint {
public:
    GeoPoint(int i);
    GeoPoint(const GeoPoint& orig);
    virtual ~GeoPoint();
    void addNeighbour(int n);
    float x,y,z;
    int index;
    int neighbours[36];
    int neighbourCount;
private:

};

#endif	/* _GEOPOINT_H */

