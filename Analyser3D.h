/* 
 * File:   Analyser3D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:45
 */

#ifndef ANALYSER3D_H
#define	ANALYSER3D_H
#include "Feature.h"
#include "GeoSequence.h"

class Analyser3D {
public:
    Analyser3D();
    Analyser3D(const Analyser3D& orig);
    virtual ~Analyser3D();
    void initFeatures();
    void evalEachView();
    void setDataActor(vtkActor* da){
        dataActor=da;
    }
    vtkSmartPointer<vtkActor> getDataActor(){
        return dataActor;
    }
private:
    Feature* listOfFeatures;
    GeoSequence geoSequence;
    vtkSmartPointer<vtkActor> dataActor;
    

};

#endif	/* ANALYSER3D_H */

