/* 
 * File:   Feature.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 18:28
 */

#include "Feature.h"
#include "testVol4D.h"

Feature::Feature(float weight) : weight(weight) {

}

Feature::Feature(const Feature& orig) {
}

Feature::~Feature() {
}

void Feature::readyRenderer(vtkSmartPointer<vtkRenderer> _renderer) {
    
    renderer = _renderer;
    camera=renderer->GetActiveCamera();
    std::vector< vtkSmartPointer<vtkActor> >::iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        renderer->AddActor((*it));
    }
    framebuffer=new FrameBuffer(renderer->GetRenderWindow());
}
void Feature::climbDown() {

    std::vector< vtkSmartPointer<vtkActor> >::const_iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        renderer->RemoveActor((*it));
    }
    delete framebuffer;
}
int Feature::scoreFeature(GeoPoint* view) {
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange *  view->getz());
    renderer->Render();
    return countColour(framebuffer);

}


int Feature::countColour(float r, float g, float b, FrameBuffer* fb) {

    int count = 0;
    int len = fb->getLen();
    cout<<" len is "<<len<<endl;
    fb->grabData();
    float* data = fb->getData();
    for (int i = 0; i < len; i++) {
        int j = i * 4;
        if (data[j] == r && data[j + 1] == g && data[j + 2] == b) {
            count++;
        }
    }

    return count;

}