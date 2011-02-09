/* 
 * File:   Feature.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 18:28
 */

#ifndef FEATURE_H
#define	FEATURE_H
#include <vector>
#include "vtkEssentials.h"
#include "FrameBuffer.h"
#include "GeoPoint.h"

//enum FeatureType {Area, Topology, TemporalChange, Curvature};

class Feature {
public:

    Feature(float weight);
    Feature(const Feature& orig);
    virtual ~Feature();
    
    virtual void initFeature(){};
    void addActor(vtkSmartPointer<vtkActor> actor){
        actors.push_back(actor);
    }
    void readyRenderer(vtkSmartPointer<vtkRenderer> _renderer);
    void climbDown();
    int scoreFeature(GeoPoint* view);
    
    int countColour(float r, float g, float b, FrameBuffer* data);
    int countColour(FrameBuffer* data){
        countColour(colourR,colourG,colourB,data);
    }
    int a;
private:
    int rawScore;
    FrameBuffer* framebuffer;
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    float weight;
  //  FeatureType type;
    //vtkActor* actors;
    float** scoreData;
    float colourR,colourB,colourG;
    std::vector< vtkSmartPointer<vtkActor> > actors;

    

    

};

#endif	/* FEATURE_H */

