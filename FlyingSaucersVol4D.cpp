/* 
 * File:   FlyingSaucersVol4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 February 2011, 20:04
 */

#include "FlyingSaucersVol4D.h"

FlyingSaucersVol4D::FlyingSaucersVol4D(OVASControl* oc, int numSaucers) : ImplicitVolume4D(oc) {
    saucers=new vector<MovingAAElipsoid*>();
    srand(28);
    for (int i=0;i<numSaucers;i++){
        
        float x,y,z;
        //float x=((float)rand())/RAND_MAX,y=((float)rand())/RAND_MAX,z=((float)rand())/RAND_MAX,vx=(((float)rand())/RAND_MAX)/2-0.25,vy=(vx/5)*((float)rand())/RAND_MAX,vz=(vx/5)*((float)rand())/RAND_MAX;
        if(i==0){
            x=0.1;y=0.2;z=0.5;
        }
        if(i==1){
            x=0.3;y=0.5;z=0.5;
        }
        if(i==2){
            x=0.6;y=0.7;z=0.7;
        }
        if(i==3){
            x=0.8;y=0.7;z=0.5;
        }
            
        float sx,sy,sz;
        float vx,vy,vz;
//        sy=sz=10;
//        sx=400;
        sx=sy=sz=50;
        vx=vy=vz=0;
        float w=4;
       
        saucers->push_back(new MovingAAElipsoid(oc,x,y,z,vx,vy,vz,sx,sy,sz,w));
        cout<<" add saucer "<<i<<" "<<x*oc->xDim<<" "<<y*oc->yDim<<" "<<z*oc->zDim<<endl;
    }
    
}

FlyingSaucersVol4D::FlyingSaucersVol4D(const FlyingSaucersVol4D& orig) {
}

FlyingSaucersVol4D::~FlyingSaucersVol4D() {
}

//float FlyingSaucersVol4D::getVoxelValue(int x, int y, int z, int step) {
//
//    float time = oc->stepToParamConverter->getParamForStep(step);
//    float tFraction = oc->stepToParamConverter->getParamFractionForStep(step);
//    int noCenters = 3;
//    float spread = 0.3;
//
//    vector<float> centres(3 * noCenters);
//
//    float fieldVal = 0;
//    float cx, cy, cz;
//    float weight = 3.9;
//    for (size_t i = 0; i < noCenters; i++) {
//        cy = 0.3 + 0.25*i;
//        cx = 0.3 + 0.2*i;
//        cz = 0.3 + 0.2*i;
//     //   cx=cy=cz=0.5;
//        float sx, sy, sz;
//        float sinVal=sin(tFraction*(4*3.14152));
//
//        sy = 350+sinVal*300;
//        if(x==16&&y==16&&z==16){
//            cout<<"sinv "<<sinVal<<" sy: "<<sy<<endl;
//        }
//        sx = 3;
//        sz = 3;
//
//        float xv = (float) x / oc->xDim;
//        float yv = (float) y / oc->yDim;
//        float zv = (float) z / oc->zDim;
//        fieldVal += (exp(-1 * (pow(xv - cx, 2) * sx + pow(yv - cy, 2) * sy + pow(zv - cz, 2) * sz))) * weight;
//        //cout<<" for "<<x<<" "<<y<<" "<<z<<" "<<(exp(-1 * (pow(xv - cx, 2))*sx))<<endl;
//    }
//    //cout<<" for "<<x<<" "<<y<<" "<<z<<" "<<fieldVal<<endl;
//    return fieldVal;
//
//}
//

//float FlyingSaucersVol4D::getVoxelValue(int x, int y, int z, int step) {
//
//    float time = oc->stepToParamConverter->getParamForStep(step);
//    float tFraction = oc->stepToParamConverter->getParamFractionForStep(step);
//    int noCenters = 3;
//    float spread = 0.3;
//
//    vector<float> centres(3 * noCenters);
//
//    float fieldVal = 0;
//    float cx, cy, cz;
//    float weight = 3.9;
//    for (size_t i = 0; i < noCenters; i++) {
//        cy = 0.3 + 0.25*i;
//        cx = 0.3 + 0.2*i;
//        cz = 0.3 + 0.2*i;
//     //   cx=cy=cz=0.5;
//        float sx, sy, sz;
//        float sinVal=sin(tFraction*(4*3.14152));
//
//        sy = 350+sinVal*300;
////        if(x==16&&y==16&&z==16){
////            cout<<"sinv "<<sinVal<<" sy: "<<sy<<endl;
////        }
//        sx = 3;
//        sz = 3;
//
//        float xv = (float) x / oc->xDim;
//        float yv = (float) y / oc->yDim;
//        float zv = (float) z / oc->zDim;
//        fieldVal += (exp(-1 * (pow(xv - cx, 2) * sx + pow(yv - cy, 2) * sy + pow(zv - cz, 2) * sz))) * weight;
//        //cout<<" for "<<x<<" "<<y<<" "<<z<<" "<<(exp(-1 * (pow(xv - cx, 2))*sx))<<endl;
//    }
//    //cout<<" for "<<x<<" "<<y<<" "<<z<<" "<<fieldVal<<endl;
//    return fieldVal;
//
//}
//


float FlyingSaucersVol4D::getVoxelValue(int x, int y, int z, int step) {
    
    float time = oc->stepToParamConverter->getParamForStep(step);
    float tFraction = oc->stepToParamConverter->getParamFractionForStep(step);
    
    vector<MovingAAElipsoid*>::iterator it;
    float totalVal=0;
    for (it=saucers->begin();it!=saucers->end();it++){
        MovingAAElipsoid* saucer=*(it);
        
        totalVal+=saucer->getContribAt(x,y,z,step);//*(0.9+0.2*((float)rand())/RAND_MAX);
    }
    //cout<<"returning tv "<<totalVal<<endl;
    //return 0;
    return totalVal;


}