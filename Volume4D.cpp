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

    cout << "\t>Creating Vol4D" << endl;
    contourer = vtkSmartPointer<vtkContourFilter>::New();
    vtkVol = vtkSmartPointer<vtkImageData>::New();
    vtkVol->SetDimensions(oc->xDim, oc->yDim, oc->zDim);
    float sp = (float) 1.0 / (oc->xDim - 1);
    vtkVol->SetOrigin(0, 0, 0);
    vtkVol->SetSpacing(sp, sp, sp);
    vtkVol->AllocateScalars();
    isoVal = new float(1.19);
    contourer->SetInput(vtkVol);
    contourer->SetValue(0, *isoVal);
    contourer->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(contourer->GetOutput());
    oc->volActor->SetMapper(mapper);
    oc->volActor->GetProperty()->SetAmbient(1);
    oc->volActor->GetProperty()->SetDiffuse(0); //SetShading(0);
    oc->volActor->GetProperty()->SetSpecular(0); //SetShading(0);
    oc->volActor->GetProperty()->SetInterpolationToFlat();
    charVol = new unsigned char[oc->xDim * oc->yDim * oc->zDim];
    criticalPoints = new vector<CriticalPoint*>();
}

Volume4D::Volume4D(const Volume4D& orig) {
}

Volume4D::~Volume4D() {
}

void Volume4D::setToStep(int step) {
    float fmaxValue = 0;
    float fminValue = 0;
    float val;
    loadFloatVolume(oc->volDataFileName);


    contourer->Update();
    contourer->Modified();

}

void Volume4D::updateActor() {
    contourer->Update();
    contourer->Modified();
}

void Volume4D::loadFloatVolume(string* fileName) {

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
    //    char* re1src=reinterpret_cast<char *>(&fd);
    //    char* re1dest=new char[4];
    //    re1dest[1]=re1src[2];
    //    re1dest[2]=re1src[1];
    //    re1dest[0]=re1src[3];
    //    re1dest[3]=re1src[0];


    //endian_byte_swapper(re1dest,re1src);
    //    endian_byte_swapper(re1dest,re1src);
    int voxCount = 0;
    for (int k = 0; k < oc->zDim; k++) {
        for (int j = 0; j < oc->yDim; j++) {
            for (int i = 0; i < oc->xDim; i++) {
                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, floatData[voxCount++]);
                if (k == 128 && j == 128) {
                    cout << floatData[voxCount - 1] << endl;

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

    float range = fmaxValue - fminValue;
    for (int i = 0; i < totalSize; i++) {
        float val = (((floatData[i] - fminValue) / range)*255);
        unsigned char c = (unsigned char) val;
        charVol[i] = c;
    }

    std::clog << "loaded vol max value was " << fmaxValue << " and min value was " << fminValue << std::endl;

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
    return persistence;
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
    setToStep(0);
    cout << " building contour tree" << endl;

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

    int id = root->extremum;
    unsigned int x, y, z;
    data.convertIndex(id, x, y, z);
    int step = 0;
    float val = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
    criticalPoints->push_back(new CriticalPoint(x, y, z, step, val));
    cout << "   found root id " << id << "location " << x << " " << y << " " << z << " val " << (int) data[id] << " voxval " << val << endl;
    cout << " persistance " << evalPersistence(&data, root) << endl;
    //data.convertIndex(data.maxId, x, y, z);
    //cout << "max val id " << data.maxId << "locati " << x << " " << y << " " << z << " with id " << (int) data.maxId << " val " << (int) data[data.maxId] << endl;
    addPersistentBranches(&data, root, 0.04);
    ctBranch ** map = ct_branchMap(ctx);
    ct_cleanup(ctx);

    //output tree
    //    std::ofstream out(outfile, std::ios::out);
    //    if (out) {
    //        outputTree(out, root);
    //    } else {
    //        cerr << "couldn't open output file " << outfile << endl;
    //    }

}

void Volume4D::addPersistentBranches(Data* data, ctBranch* b, float thresh) {
    float persistence = evalPersistence(data, b);
    if(persistence<-0.03) cout<<"warning stronger negative persistence "<<persistence<<endl;
    if (persistence > thresh) {
        int extId = b->extremum;
        int sadId = b->saddle;
        float eval, sval;
        unsigned int x, y, z;
        data->convertIndex(extId, x, y, z);
        eval = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
        data->convertIndex(sadId, x, y, z);
        sval = vtkVol->GetScalarComponentAsFloat(x, y, z, 0);
        cout << "adding branch ex" << b->extremum << " sad: " << b->saddle << "with persistence " << persistence << endl;
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
