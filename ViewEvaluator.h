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
#include "testVol4D.h"
#include "FeatureWeights.h"
#include "Analyser4D.h"



class ViewEvaluator {
public:
    ViewEvaluator();
    ViewEvaluator(const ViewEvaluator& orig);
    ViewEvaluator(Analyser4D* a);
    void setDataActor(vtkActor* da){
        dataActor=da;
    }
    virtual ~ViewEvaluator();
    void evaluate(GeoPoint* view);
    void renderThisView(GeoPoint* view);
    void setScreenRenderOn(){
        onScreen=true;
    }
    Volume4D* vol;
    FeatureWeights* featureWeights;
private:
    Analyser4D* a4d;
    vtkSmartPointer<vtkActor> dataActor;
    
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    bool onScreen;
    vtkSmartPointer<vtkCamera> camera;

};


#endif	/* VIEWEVALUATOR_H */

