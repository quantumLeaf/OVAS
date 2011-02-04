/* 
 * File:   ViewEvaluator.h
 * Author: zoizoi
 *
 * Created on 03 February 2011, 22:05
 */

#ifndef VIEWEVALUATOR_H
#define	VIEWEVALUATOR_H

#include "FeatureWeights.h"
#include "vtkEssentials.h"
#include "Volume4D.h"
#include "GeoPoint.h"


class ViewEvaluator {
public:
    ViewEvaluator();
    ViewEvaluator(const ViewEvaluator& orig);
    ViewEvaluator(FeatureWeights* fw,Volume4D* v);
    void setDataActor(vtkActor* da){
        dataActor=da;
    }
    virtual ~ViewEvaluator();
    void evaluate(GeoPoint* view);
    void setScreenRenderOn(){
        onScreen=true;
    }
private:
    FeatureWeights* featureWeights;
    vtkSmartPointer<vtkActor> dataActor;
    Volume4D* vol;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    bool onScreen;
    vtkSmartPointer<vtkCamera> camera;

};


#endif	/* VIEWEVALUATOR_H */

