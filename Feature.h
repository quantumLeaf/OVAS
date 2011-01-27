/* 
 * File:   Feature.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 18:28
 */

#ifndef FEATURE_H
#define	FEATURE_H

class Feature {
public:
    Feature();
    Feature(const Feature& orig);
    virtual ~Feature();
    virtual void scoreThisFrame(float* data);
    virtual void initFeature();

private:
    //vtkActor* actors;
    float** scoreData;
    

};

#endif	/* FEATURE_H */

