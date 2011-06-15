/* 
 * File:   Volume4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Volume4D.h"
#include "testVol4D.h"
#include "CriticalPoint.h"

Volume4D::Volume4D() {

}

Volume4D::Volume4D(OVASControl* o) {
    oc = o;
    oc->volActor = vtkSmartPointer<vtkActor>::New();
    oc->volActor->GetProperty()->SetOpacity(0.5);
    //    vtkSmartPointer<vtkTransform> transform =
    //    vtkSmartPointer<vtkTransform>::New();
    //        transform->RotateX(90);
    //        transform->Translate(90,0,0);
    //        
    //
    //    oc->volActor->SetUserTransform(transform);
    cout << "\t>Creating Vol4D" << endl;
    contourer = vtkSmartPointer<vtkContourFilter>::New();
    vtkVol = vtkSmartPointer<vtkImageData>::New();
    //    oc->xDim=104;
    //    oc->yDim=129;
    //    oc->zDim=129;
    vtkVol->SetDimensions(oc->xDim, oc->yDim, oc->zDim);
    float sp = (float) 1.0 / (oc->xDim - 1);
    vtkVol->SetOrigin(0, 0, 0);
    //vtkVol->SetSpacing(((float) 0.3 / (oc->xDim - 1)), sp, sp  );
    vtkVol->SetSpacing(sp, sp, sp);

    vtkVol->AllocateScalars();
    oc->currentIso = 4.2;
    contourer->SetInput(vtkVol);
    contourer->SetValue(0, oc->currentIso);
    contourer->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(contourer->GetOutput());
    oc->volActor->SetMapper(mapper);
    oc->volActor->GetProperty()->SetAmbient(1);
    oc->volActor->GetProperty()->SetDiffuse(0); //SetShading(0);
    oc->volActor->GetProperty()->SetSpecular(0); //SetShading(0);
    oc->volActor->GetProperty()->SetInterpolationToFlat();

    charVol = new unsigned char[oc->xDim * oc->yDim * oc->zDim];
    loaded = false;
    //cout << " address of charvol " << (static_cast<const void*> (charVol)) << endl;

    int* test = new int[3];
    //    /cout<<" current dims are "<<oc->xDim<<endl;
    criticalPoints = new vector<CriticalPoint*>();
}

Volume4D::Volume4D(const Volume4D& orig) {
}

Volume4D::~Volume4D() {
}

void Volume4D::setToStep(int step) {
    cout << "setting vol to step " << step << endl;
            for (int k = 0; k < oc->zDim; k++) {
                for (int j = 0; j < oc->yDim; j++) {
                    for (int i = 0; i < oc->xDim; i++) {
                        float val = getVoxelValue(i, j, k, step);
                        //cout<<" got val "<<val<<endl;
                        vtkVol->SetScalarComponentFromFloat(i, j, k, 0, val);
                        
                    }
                }
            }
             createCharVolume();
    //loadFloatVolume(oc->volDataFileName);
    //string filename = "./data/ns_000" + to_string(step*180 + 1) + "_r.dat";
    string filename;
    //filename = "./data/p5/p_5" + to_string((step));
    //filename = "./data/ns_" + to_string((step)*100 + 1000) + "_e.dat";
    //filename = "./data/ns_" + to_string((step)*25 + 1000) + "_e.dat";
    //filename = "./data/ns_" + to_string((step)*50 + 1001) + "_e.dat";
    //    if (((step)*50 + 651) < 1000) {
    //        filename = "./data/ns_0" + to_string((step)*50 + 651) + "_e.dat";
    //    } else {
    //        filename = "./data/ns_" + to_string((step)*50 + 651) + "_e.dat";
    //    }
    //    if(loaded==false){
    filename = "./data/ns_0751_e.dat";
    //    
    //    cout << "loading file " << filename << endl;
    //
    //loadFloatVolume(&filename);
    //loadFloatVolume(oc->volDataFileName);


    //    loaded=true;
    //    }
//    oc->isoStep = 25;
//    oc->currentIso = 254350 + step * (oc->isoStep);
    oc->isoStep = 0.6;
    oc->currentIso = 1.5 + step * (oc->isoStep);
    
    //oc->currentIso = 254050;
    contourer->SetValue(0, oc->currentIso);
    cout << "setting iso to " << oc->currentIso << endl;
    contourer->Update();
    contourer->Modified();
}

void Volume4D::updateActor() {
    contourer->Update();
    contourer->Modified();
}

void Volume4D::loadFloatVolume(string* fileName) {
    cout << "loading float vol" << *fileName << endl;

    int totalSize = oc->xDim * oc->yDim * oc->zDim;

    std::fstream infile;

    infile.open((*fileName).c_str(), std::ios::in);
    if (!infile) {
        std::clog << "could not open " << *fileName << std::endl;
        return;
    }

    cout << "total size is " << totalSize * 4 << endl;


    float * floatData = new float [totalSize];
    infile.read((char*) floatData, totalSize * 4);

    //    //change byte order
    //    for (int i = 0; i < totalSize; i++) {
    //        float x=floatData[i];
    //        float y;
    //        char* re=reinterpret_cast<char *>(&(floatData[i]));
    //        char t=re[3];
    //        re[3]=re[0];
    //        re[0]=t;
    //        t=re[2];
    //        re[2]=re[1];
    //        re[1]=t;
    //    }

    int voxCount = 0;
    for (int k = 0; k < oc->zDim; k++) {
        for (int j = 0; j < oc->yDim; j++) {
            for (int i = 0; i < oc->xDim; i++) {
                if(k<3||k>oc->zDim-4||j<3||j>oc->yDim-4||i<3||i>oc->xDim-4){
                    vtkVol->SetScalarComponentFromFloat(i, j, k, 0, 0);
                    voxCount++;
                }
                else{
                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, floatData[voxCount++]);
                }
            }
        }
    }
    cout << "loaded checking min max" << endl;

    float fmaxValue = floatData[0];
    float fminValue = floatData[0];
    for (int i = 0; i < totalSize; i++) {
        if (floatData[i] > fmaxValue) fmaxValue = floatData[i];
        if (floatData[i] < fminValue) fminValue = floatData[i];

    }
    //cout<<"load in character data to vol at "<<charVol<<endl;

    //cout << " address of charvol " << (static_cast<const void*> (charVol)) << endl;

    float range = fmaxValue - fminValue;
    for (int i = 0; i < totalSize; i++) {
        float val = (((floatData[i] - fminValue) / range)*255);
        unsigned char c = (unsigned char) val;
        charVol[i] = c;
    }

   

    std::clog << "loaded vol max value was " << fmaxValue << " and min value was " << fminValue << std::endl;
    oc->isoRange = fmaxValue - fminValue;
    oc->isoRangeThreshold = oc->isoRange / 25;

    cout << "resampling vol" << endl;
    
//    vtkImageResample *resample = vtkImageResample::New();
//    float reductionFactor = 0.5;
//
//    resample->SetInput(vtkVol);
//    resample->SetAxisMagnificationFactor(0, reductionFactor);
//    resample->SetAxisMagnificationFactor(1, reductionFactor);
//    resample->SetAxisMagnificationFactor(2, reductionFactor);
//    vtkVol=resample->GetOutput();

    return;
}

void Volume4D::createCharVolume() {

    int totalSize = oc->xDim * oc->yDim * oc->zDim;

    cout << "total size is " << totalSize * 4 << endl;
    float * floatData = new float [totalSize];

    int voxCount = 0;
    for (int k = 0; k < oc->zDim; k++) {
        for (int j = 0; j < oc->yDim; j++) {
            for (int i = 0; i < oc->xDim; i++) {
                floatData[voxCount] = vtkVol->GetScalarComponentAsFloat(i, j, k, 0);
                voxCount++;
            }
        }
    }
    cout << "created char checking min max" << endl;

    float fmaxValue = floatData[0];
    float fminValue = floatData[0];
    for (int i = 0; i < totalSize; i++) {
        if (floatData[i] > fmaxValue) fmaxValue = floatData[i];
        if (floatData[i] < fminValue) fminValue = floatData[i];
    }

    float range = fmaxValue - fminValue;


    std::clog << "loaded vol max value was " << fmaxValue << " and min value was " << fminValue << std::endl;
    oc->isoRange = fmaxValue - fminValue;
    oc->isoRangeThreshold = oc->isoRange / 40;
    
     for (int i = 0; i < totalSize; i++) {
        float val = (((floatData[i] - fminValue) / range)*255);
        unsigned char c = (unsigned char) val;
        charVol[i] = c;
    }

    return;
}

size_t neighbors(size_t v, size_t * nbrs, void * d) {
    Mesh * mesh = static_cast<Mesh*> (d);
    static std::vector<size_t> nbrsBuf;

    nbrsBuf.clear();
    mesh->getNeighbors(v, nbrsBuf);

    for (uint i = 0; i < nbrsBuf.size(); i++) {
        nbrs[i] = nbrsBuf[i];
    }
    return nbrsBuf.size();
}

double value(size_t v, void * d) {
    Mesh * mesh = static_cast<Mesh*> (d);
    return mesh->data[v];
}

float Volume4D::evalPersistence(Data* data, ctBranch* b) {
    int extId = b->extremum;
    int sadId = b->saddle;
    float eval, sval;
    unsigned int x, y, z;
    data->convertIndex(extId, x, y, z);
    eval = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
    data->convertIndex(sadId, x, y, z);
    sval = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
    float persistence = eval - sval;
    //if (persistence < 0) cout << "FOUND NEGATIVE PERSISTENCE Volume4D::evalPersistence(Data data,ctBranch* b)" << persistence<<endl;
    return fabs(persistence);
}

void outputTree(std::ofstream & out, ctBranch * b) {
    out << "(" << b->extremum << ' ' << b->saddle;

    for (ctBranch * c = b->children.head; c != NULL; c = c->nextChild) {
        out << " ";
        outputTree(out, c);
    }

    out << ")";
}

void Volume4D::findCritcalPoints() {
    // setToStep(0);
    if(*oc->volDataFileName!="none"){
        std::fstream infile;
    string ctDatafile = *oc->volDataFileName + string(".ctData");
    infile.open((ctDatafile).c_str(), std::ios::in);
    //    if (infile.is_open()) {
    //        std::clog << "could not open ctData " << ctDatafile << std::endl;
    //        return;
    //    }
    //cout << "unable to load critical points, building contour tree" << endl;

    }
    
    Data data;
    int i = 0;

    data.initData(charVol, vtkVol->GetNumberOfPoints(), oc->xDim); //instead of load from file

    //Create mesh
    Mesh mesh(data);

    std::vector<size_t> totalOrder;
    mesh.createGraph(totalOrder); //this just sorts the vertices according to data.less()

    ctContext * ctx = ct_init(
            data.totalSize, //numVertices
            &(totalOrder.front()), //totalOrder. Take the address of the front of an stl vector, which is the same as a C array
            &value,
            &neighbors,
            &mesh //data for callbacks. The global functions less, value and neighbors are just wrappers which call mesh->getNeighbors, etc
            );

    //create contour tree
    ct_sweepAndMerge(ctx);
    ctBranch * root = ct_decompose(ctx);
    
    unsigned int x, y, z;
    
    int id = root->extremum;
    
    data.convertIndex(id, x, y, z);
    int step = 0;
    float val = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);

    cout << "   found root id " << id << "location " << x << " " << y << " " << z << " val " << (int) data[id] << " voxval " << val << endl;
    cout << " persistance " << evalPersistence(&data, root) << endl;
    //data.convertIndex(data.maxId, x, y, z);
    //cout << "max val id " << data.maxId << "locati " << x << " " << y << " " << z << " with id " << (int) data.maxId << " val " << (int) data[data.maxId] << endl;
    cout << " adding persistant branches as CPs where persistance is greater than " << oc->isoRangeThreshold << endl;
    addPersistentBranches(&data, root, oc->isoRangeThreshold);
    ctBranch ** map = ct_branchMap(ctx);

    ct_cleanup(ctx);

    cout << " Total CPs: " << oc->volume4D->criticalPoints->size() << endl;

    //    ofstream outfile;
    //    outfile.open(ctDatafile.c_str());
    //    
    //        if (outfile.is_open()) {
    //            cout<<"opened output file "<<ctDatafile<<endl;
    //            vector<CriticalPoint*>::iterator it;
    //            cout<<"cp length "<<oc->volume4D->criticalPoints->size()<<endl;
    //            for (it=oc->volume4D->criticalPoints->begin();it!=oc->volume4D->criticalPoints->end();it++){
    //                cout<<"outputting critical point"<<endl;
    //                outfile<<(*it)->x<<" "<<(*it)->y<<" "<<(*it)->z<<" "<<(*it)->step<<" "<<(*it)->value<<endl;
    //            }
    //        } else {
    //            cerr << "couldn't open output file " << outfile << endl;
    //        }

    for (int j = 0; j < 128 * 128 * 128; j++) {

        char a = oc->volume4D->charVol[j];
    }
}

void Volume4D::addPersistentBranches(Data* data, ctBranch* b, float thresh) {
    float persistence = evalPersistence(data, b);
    //if(persistence<-0.03) cout<<"warning stronger negative persistence "<<persistence<<endl;
    //cout<<"eval branch of persist "<<persistence<<endl;
    if (persistence > thresh) {
        int extId = b->extremum;
        int sadId = b->saddle;
        float eval, sval;
        unsigned int x, y, z;
        cout << "adding branch ex" << b->extremum << " sad: " << b->saddle << "with persistence " << persistence << endl;
        data->convertIndex(extId, x, y, z);
        if (!(x == 0 || x == oc->xDim || y == 0 || y == oc->yDim || z == 0 || z == oc->zDim)) {
            eval = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
            CriticalPoint* cp = new CriticalPoint(x, y, z, oc->currentStep, eval, oc->xDim, oc->yDim, oc->zDim);
            criticalPoints->push_back(cp);
            CriticalPoint* lastPoint = criticalPoints->back();
            cout << "add new CP " << lastPoint->getXFloat() << " " << lastPoint->getYFloat() << " " << lastPoint->getZFloat() << " " << lastPoint->value << endl;
        }
        data->convertIndex(sadId, x, y, z);
        if (!(x == 0 || x == oc->xDim || y == 0 || y == oc->yDim || z == 0 || z == oc->zDim)) {
            sval = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
            criticalPoints->push_back(new CriticalPoint(x, y, z, oc->currentStep, sval, oc->xDim, oc->yDim, oc->zDim));
            CriticalPoint* lastPoint = criticalPoints->back();
            cout << "add new CP " << lastPoint->getXFloat() << " " << lastPoint->getYFloat() << " " << lastPoint->getZFloat() << " " << lastPoint->value << endl;
        }
        for (ctBranch * c = b->children.head; c != NULL; c = c->nextChild) {
            addPersistentBranches(data, c, thresh);
        }
    }

}

void Volume4D::testContourTree() {
    cout << " contour tree" << endl;

    char outfile[1024] = "";
    char filename[1024] = "";
    strcpy(outfile, "./nucleon.tree");
    //strcpy(filename, "./ns_0208_e.dat");

    Data data;
    int i = 0;
    //float* rawData=new float[vtkVol->GetNumberOfPoints()]();
    char* rawData = new char[vtkVol->GetNumberOfPoints()]();
    //unsigned char* rawData = new unsigned char[vtkVol->GetNumberOfPoints()]();

    //    cout<<"copying data to array"<<endl;
    //    for (int z = 0; z < oc->zDim; z++) {
    //        for (int y = 0; y < oc->yDim; y++) {
    //            for (int x = 0; x < oc->xDim; x++) {
    //                rawData[i++] = (unsigned int) (65 * vtkVol->GetScalarComponentAsFloat(x, y, z, 0));
    //            }
    //        }
    //    }

    //cout<<"copied data"<<i<<endl;
    //data.initData(rawData, vtkVol->GetNumberOfPoints(), oc->xDim); //instead of load from file
    data.initData(charVol, vtkVol->GetNumberOfPoints(), oc->xDim); //instead of load from file
    //data.loadVol(filename, 128); //instead of load from file

    //Create mesh
    Mesh mesh(data);

    std::vector<size_t> totalOrder;
    mesh.createGraph(totalOrder); //this just sorts the vertices according to data.less()

    //init libtourtre

    ctContext * ctx = ct_init(
            data.totalSize, //numVertices
            &(totalOrder.front()), //totalOrder. Take the address of the front of an stl vector, which is the same as a C array
            &value,
            &neighbors,
            &mesh //data for callbacks. The global functions less, value and neighbors are just wrappers which call mesh->getNeighbors, etc
            );

    //create contour tree
    ct_sweepAndMerge(ctx);
    ctBranch * root = ct_decompose(ctx);


    int id = root->extremum;
    unsigned int x, y, z;
    data.convertIndex(id, x, y, z);


    cout << "   found root id " << id << "location " << x << " " << y << " " << z << " val " << (int) data[id] << endl;


    //data.convertIndex(data.maxId, x, y, z);
    //cout << "max val id " << data.maxId << "locati " << x << " " << y << " " << z << " with id " << (int) data.maxId << " val " << (int) data[data.maxId] << endl;

    ctBranch ** map = ct_branchMap(ctx);
    ct_cleanup(ctx);

    //output tree
    std::ofstream out(outfile, std::ios::out);
    if (out) {
        outputTree(out, root);
    } else {
        cerr << "couldn't open output file " << outfile << endl;
    }



}

void Volume4D::testReebGraph() {
    cout << "reeb graphing" << endl;

    vtkSmartPointer<vtkDataSetTriangleFilter> trifilter = vtkSmartPointer<vtkDataSetTriangleFilter>::New();
    trifilter->SetInput(vtkVol);
    trifilter->Update();

    vtkUnstructuredGridToReebGraphFilter *volumeReebGraphFilter =
            vtkUnstructuredGridToReebGraphFilter::New();


    volumeReebGraphFilter->SetInput(trifilter->GetOutput());
    volumeReebGraphFilter->Update();

    vtkReebGraph *volumeReebGraph = volumeReebGraphFilter->GetOutput();

    vtkReebGraphSimplificationFilter *volumeSimplification =
            vtkReebGraphSimplificationFilter::New();
    volumeSimplification->SetInput(volumeReebGraph);
    volumeSimplification->SetSimplificationThreshold(0.05);
    volumeSimplification->Update();
    vtkReebGraph *simplifiedVolumeReebGraph = volumeSimplification->GetOutput();

    //DisplayReebGraph(simplifiedVolumeReebGraph);

    //cout<<"rg edges: "<<simplifiedVolumeReebGraph->GetNumberOfEdges()<<" "<<simplifiedVolumeReebGraph->GetNumberOfElements(0)<<" "<<simplifiedVolumeReebGraph->GetNumberOfVertices()<<endl;
    //
    //    cout<<" vcount "<<volumeReebGraph->GetNumberOfVertices()<<endl;

}