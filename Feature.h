/* 
 * File:   Feature.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 18:28
 */

#ifndef FEATURE_H
#define	FEATURE_H
#include <vtkActor.h>
#include <vector>
#include "vtkEssentials.h"
#include "FrameBuffer.h"


class Feature {
public:
    Feature();
    Feature(const Feature& orig);
    virtual ~Feature();
    virtual void scoreThisFrame(float* data){};
    virtual void initFeature(){};
    void addActor(vtkActor*);
    void renderActors(vtkRenderer* ren);
    virtual int countColour(float r, float g, float b, FrameBuffer* data);
private:
    //vtkActor* actors;
    float** scoreData;
    std::vector<vtkActor*> Actors;

    

    

};

#endif	/* FEATURE_H */

