
#include "InfoSheet.h"

InfoSheet::InfoSheet(OVASControl* o) {
    oc = o;

    this->info = ArrayTools::allocate2DArray<float>(oc->numSteps, oc->geoSphere->getNumVs());
    nextViewIndex = ArrayTools::allocate3DArray<float>(oc->numSteps, oc->geoSphere->getNumVs(), this->numRegions);
    this->maxInfo = ArrayTools::allocate3DArray<float>(oc->numSteps, oc->geoSphere->getNumVs(), this->numRegions);

    currentInfoTs = 0;



}

InfoSheet::InfoSheet(const InfoSheet& orig) {
}

InfoSheet::~InfoSheet() {
}

void InfoSheet::outputInfoData(const char* filename) {
    cout << "outputing file " << filename << "\n";
    ofstream of;
    of.open(filename);

    of << oc->numSteps << " " << oc->geoSphere->getNumVs() << endl;
    for (int i = 0; i < currentInfoTs; i++) {

        for (int j = 0; j < oc->geoSphere->getNumVs(); j++) {
            of << info[i][j] << " ";
        }
        of << endl;
    }
    of.close();

}

void InfoSheet::loadInfo(const char* filename) {
    cout << "loading " << filename << "\n";
    ifstream inf;

    inf.open(filename);
    assert(inf.is_open());
    inf >> oc->numSteps >> oc->geoSphere->getNumVs();

    cout << " discovered oc->numSteps nvs " << oc->numSteps << " " << oc->geoSphere->getNumVs() << endl;

    for (int i = 0; i < oc->numSteps; i++) {
        for (int j = 0; j < oc->geoSphere->getNumVs(); j++) {
            inf >> info[i][j];
        }
    }
    inf.close();

}

bool InfoSheet::validTransition(GeoPoint* fromV, GeoPoint* toV, GeoPoint* prevV) {
    //transition prevV->fromV->toV
    bool cond = false;
    if (fromV == 276 && prevV == 0 && toV == 0) cond = true;
    if (prevV == toV) return false;

    namespace ub = boost::numeric::ublas;

    ub::vector<float> in(3);
    ub::vector<float> out(3);
    ub::vector<float> a(3);
    ub::vector<float> b(3);
    ub::vector<float> c(3);  

    a = prevV->getUblasVector();
    b = toV->getUblasVector();
    c = fromV->getUblasVector();

    in = c - a;
    out = b - c;


    float inLen = sqrt(in(0) * in(0) + in(1) * in(1) + in(2) * in(2));
    float outLen = sqrt(out(0) * out(0) + out(1) * out(1) + out(2) * out(2));
    float theta = acos((in(0) * out(0) + in(0) * out(0) + in(0) * out(0)) / (inLen * outLen));

    float pi = 3.14152;

    if (theta < ((pi) / 4) && theta > 0) {
        return true;
    } else {
        return false;
    }
    cout << "ERROR should not be reached";
    return false;

}

int* InfoSheet::findPath() {
    this->calcMaxInfo();

    int pos;
    int reg;
    float maxInfoStart = 0;
    path = new int[oc->numSteps];
    for (int v = 0; v < oc->geoSphere->getNumVs(); v++) {
        for (int r = 0; r < views[v]->neighbourCount; r++) {
            if (maxInfo[0][v][r] > maxInfoStart) {
                maxInfoStart = maxInfo[0][v][r];
                pos = v;
                reg = r;

            }
        }
    }
    // cout<<" found pos "<<pos<<" and reg "<<reg<<endl;
    for (int i = 0; i < oc->numSteps; i++) {
        cout << "step " << i << " pos " << pos << " from n:" << reg << " " << views[pos]->neighbours[reg] << endl;

        path[i] = pos;
        //cout<<"new ivr "<<i<<" "<<pos<<" "<<reg<<endl;
        if (i < oc->numSteps - 1) {
            pos = nextViewIndex[i][pos][reg];
            cout << " update pos to " << pos << endl;
            if (path[i] == 389 && pos == 396) cout << " looking up " << endl;
            reg = lookupNeighbourIndex(pos, path[i]);
        }
        //cout << "step " << i << " pos " <<path[i]<<" from n:"<<reg<<" "<<views[pos]->neighbours[reg]<<endl;;
    }

    return path;
}
//void InfoSheet::calcMaxInfo() {
//    for (int v = 0; v < oc->geoSphere->getNumVs(); v++) {
//        maxInfo[oc->numSteps - 1][v] = info[oc->numSteps - 1][v];
//    }
//    for (int i = oc->numSteps - 2; i>-1; i--) {
//        for (int v = 0; v < oc->geoSphere->getNumVs(); v++) {
//            for (int k = 0; k < oc->geoSphere->getNumVs(); k++) {
//                float pathInfo;
//                if(this->validTransition(v,k)){
//                 pathInfo=info[i][v]+maxInfo[i+1][k];
//                }
//                else{
//                    pathInfo=0;
//                }
//                if(pathInfo>maxInfo[i][v]){
//                    maxInfo[i][v]=pathInfo;
//                    nextViewIndex[i][v]=k;
//                }
//            }
//        }
//    }
//}

void InfoSheet::calcMaxInfo() {
    

    for (int v = 0; v < oc->geoSphere->getNumVs(); v++) {
        for (int r = 0; r < oc->geoSphere->getView(v)->neighbourCount; r++) {
            maxInfo[oc->numSteps - 1][v][r] = info[oc->numSteps - 1][v];
        }
    }

    for (int i = oc->numSteps - 2; i>-1; i--) {
        for (int v = 0; v < oc->geoSphere->getNumVs(); v++) {
            for (int r = 0; r < oc->geoSphere->getView(v)->neighbourCount; r++) {
                int p = views[v]->neighbours[r];
                maxInfo[i][v][r] = -1;
                nextViewIndex[i][v][r] = -1;

                for (int t = 0; t < views[v]->neighbourCount; t++) {

                    int k = views[v]->neighbours[t];

                    // if(k==396&&v==389) cout<<" k is "<<k<<" v "<<v<<" t "<<t<<endl;
                    float pathInfo;

                    if (this->validTransition(v, k, p)) {
                        pathInfo = info[i][v] + maxInfo[i + 1][k][lookupNeighbourIndex(k, v)];
                    } else {
                        pathInfo = 0;
                    }

                    if (pathInfo > maxInfo[i][v][r]) {
                        //if (i == 7 && v == 134) cout << "For IVR " << i << " " << v << " " << r << " with pi" << pathInfo << " sett nvi to " << k << " p was " << p << endl;
                        maxInfo[i][v][r] = pathInfo;
                        //    if(v==389&&k==396) cout<<"strange but true \n";
                        nextViewIndex[i][v][r] = k;
                        // if(v==389&&i==0) cout<<" for r "<<r<<" k is "<<k<<endl;
                    }
                }
            }
        }
    }
}

void InfoSheet::addTimeInfo(float* timeInfo) {
    if (currentInfoTs > oc->numSteps) cout << "error exceeding num ts" << endl;
    info[currentInfoTs] = timeInfo;
    currentInfoTs++;
}

int InfoSheet::lookupNeighbourIndex(int k, int v) {
    //index of v in k's neighbour list
    for (int i = 0; i < views[k]->neighbourCount; i++) {
        if (views[k]->neighbours[i] == v) return i;
    }
    cout << "Error !!!!!failed to find v: " << v << " in lookup of k: " << k << endl;
    //cout<<" ks nc is "<<views[k]->neighbourCount<<endl;
    assert(false);
}

int InfoSheet::getNeighbour(int k, int v) {
    return views[k]->neighbours[v];
}

int* InfoSheet::returnBestViews() {
    int* bestViews;
    cout << " view vals: ";
    bestViews = new int[oc->numSteps];
    for (int i = 0; i < oc->numSteps; i++) {
        int maxView = 0;
        float maxViewInfo = 0;
        for (int j = 0; j < oc->geoSphere->getNumVs(); j++) {
            float thisViewInfo = info[i][j];
            if (thisViewInfo > maxViewInfo) {
                maxViewInfo = thisViewInfo;
                maxView = j;
            }
        }
        bestViews[i] = maxView;
        cout << i << " v: " << maxView << ": " << info[i][maxView] << "   ";

    }
    cout << endl;
    return bestViews;
}





