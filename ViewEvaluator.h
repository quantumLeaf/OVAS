/* 
 * File:   ViewEvaluator.h
 * Author: zoizoi
 *
 * Created on 03 February 2011, 22:05
 */

#ifndef VIEWEVALUATOR_H
#define	VIEWEVALUATOR_H

#include "vtkEssentials.h"
#include "Volume4D.h"
#include "GeoPoint.h"
#include "testVol4D.h"
#include "Feature.h"
#include "Analyser4D.h"
#include "OVASControl.h"

class Analyser4D;
class ViewEvaluator {
public:
    ViewEvaluator();
    ViewEvaluator(const ViewEvaluator& orig);
    ViewEvaluator(OVASControl* o);
    void setDataActor(vtkActor* da){
        dataActor=da;
    }
    virtual ~ViewEvaluator();
    void readyFeatures();
    void climbDownFeatures();
    void init();
    void evaluate(GeoPoint* view);
    void renderThisView(GeoPoint* view);
    void setScreenRenderOn(){
        onScreen=true;
    }
    Volume4D* vol;
    FeatureWeights* featureWeights;
private:
    
    vtkSmartPointer<vtkCamera> camera;
    Analyser4D* a4d;
    vtkSmartPointer<vtkActor> dataActor;
    OVASControl* oc;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    bool onScreen;
    

};


#endif	/* VIEWEVALUATOR_H */

