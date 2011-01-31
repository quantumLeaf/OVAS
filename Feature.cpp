/* 
 * File:   Feature.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 18:28
 */

#include "Feature.h"

Feature::Feature() {
}

Feature::Feature(const Feature& orig) {
}

Feature::~Feature() {
}

void Feature::addActor(vtkActor* actor) {
    Actors.push_back(actor);
}

void Feature::renderActors(vtkRenderer* renderer) {
    std::vector<vtkActor*>::const_iterator it;
    for (it = Actors.begin(); it != Actors.end(); it++) {
        renderer->AddActor((*it));
    }


}

int Feature::countColour(float r, float g, float b, FrameBuffer* fb) {

    int count = 0;
    int* len=fb->GetLen();
    float* data=fb->GetData();
    for (int i = 0; i < *len; i++) {
        int j = i * 4;
        //if (fabs(data[j] - data[j + 1]) < 0.001 && fabs(data[j] - data[j + 2]) < 0.001 && data[j] > 0.001) {
        if (data[j] == r && data[j + 1] == g && data[j + 2] == b) {
            count++;
        }
    }

    return count;

}