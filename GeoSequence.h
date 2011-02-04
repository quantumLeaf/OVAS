/* 
 * File:   GeoSequence.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 18:30
 */

#ifndef GEOSEQUENCE_H
#define	GEOSEQUENCE_H
#include "GeoSphere.h"
#include <list>

class GeoSequence {
public:
    GeoSequence();
    GeoSequence(GeoSphere* gs);
    GeoSequence(const GeoSequence& orig);
    virtual ~GeoSequence();

   
    std::list<GeoPoint*>* getViewList(){
        return viewList;
    }
private:
    std::list<GeoPoint*>* viewList;
    std::list<GeoPoint*>::iterator it;
};

#endif	/* GEOSEQUENCE_H */

