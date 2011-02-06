/* 
 * File:   MetaballsVol4D.cpp
 * Author: zoizoi
 * 
 * Created on 26 January 2011, 22:10
 */

#include "MetaballsVol4D.h"

MetaballsVol4D::MetaballsVol4D(int xDim, int yDim, int zDim, int numSteps, float twist) : ImplicitVolume4D(xDim, yDim, zDim, numSteps), twist(twist) {

}

MetaballsVol4D::MetaballsVol4D(const MetaballsVol4D& orig) {
}

MetaballsVol4D::~MetaballsVol4D() {
}

float MetaballsVol4D::getVoxelValue(int x, int y, int z, int step) {
    float uberTwist = 3.0;
    float time = stepConverter->getParamForStep(step);
    int noCenters = 5;
    float spread = 0.3;
    std::vector<float> centres(3 * noCenters);
    for (size_t i = 0; i < noCenters; i++) {
        centres[3 * i + 0] = 0.5 + spread * sin(time + sin(0.1 * time) * i);
        // cout<<" C "<<centres[3 * i + 0]<<" ";
        centres[3 * i + 1] = 0.5 + spread * cos(0.9 * time + sin(0.1 * time) * i);
        //cout<<" C "<<centres[3 * i + 1]<<" ";
        centres[3 * i + 2] = 0.5 + spread * cos(0.7 * time + sin(0.01 * time) * i);
        //cout<<" C "<<centres[3 * i + 2]<<" "<<endl;
    }

    float twist = uberTwist * sin(0.1f * time);

    for (int k = 0; k < zDim; k++) {
        for (int j = 0; j < yDim; j++) {
            for (int i = 0; i < xDim; i++) {
                cout<<"in the space"<<i<<j<<k<<endl;
                vnl_vector<float> p(3);
                p[0] = (float) i / xDim;
                p[1] = (float) j / yDim;
                p[2] = (float) k / zDim;

                p = p * 2.0 - 1;

                float rot1 = twist * p[2];
                float rot2 = 0.7 * twist * p[1];
                vnl_matrix<float> rotM1(3, 3);
                vnl_matrix<float> rotM2(3, 3);


                rotM1(0, 0) = cos(rot1);
                rotM1(0, 1) = -sin(rot1);
                rotM1(0, 2) = 0;
                rotM1(1, 0) = sin(rot1);
                rotM1(1, 1) = cos(rot1);
                rotM1(1, 2) = 0;
                rotM1(2, 0) = 0;
                rotM1(2, 1) = 0;
                rotM1(2, 2) = 1;
                rotM2(0, 0) = cos(rot2);
                rotM2(0, 1) = 0;
                rotM2(0, 2) = -sin(rot2);
                rotM2(1, 0) = 0;
                rotM2(1, 1) = 1;
                rotM2(1, 2) = 0;
                rotM2(2, 0) = sin(rot2);
                rotM2(2, 1) = 0;
                rotM2(2, 2) = cos(rot2);

                p *= rotM1;
                p *= rotM2;
                p = (p + 1) / 2;

                //
                //vnl_vector<float> rp=(rotM1*rotM2*p)/2-0.5;
                vnl_vector<float> rp = p;
                float s = 0.0;
                for (int ind = 0; ind < (int) noCenters; ind++) {
                    vnl_vector<float> centrei(3);
                    centrei[0] = centres[3 * ind + 0];
                    centrei[1] = centres[3 * ind + 1];
                    centrei[2] = centres[3 * ind + 2];

                    vnl_vector<float> r(3);

                    r = rp - centrei;

                    s += 0.05 / dot_product(r, r);
                    //if(i==30&&j==30) cout<<"ind "<<ind<<"cent "<<centrei<<endl;
                }
                //if(i==30&&j==30) cout<<"k "<<k<<"r val here "<<s<<endl;

                float val = s; //vol->GetScalarComponentAsFloat(i, j, k, 0);
                //                    /index = i + j * (yDim) + k * (xDim * yDim);
                //                if(k==16&&j==16&&i==16){
                //                    cout<<" at323232 "<<val<<endl;
                //                }
                //   if(val<0.000001) val=0;
                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, val);

            }
        }
    }
}

