/* 
 * File:   ViewPathClusterFinder.cpp
 * Author: zoizoi
 * 
 * Created on 18 June 2011, 10:15
 */

#include "ViewPathClusterFinder.h"
#include "GeoSphere.h"

ViewPathClusterFinder::ViewPathClusterFinder(int plen, OVASControl* o) {
    viewPaths = new vector<int*>();
    pathLength = plen;
    oc = o;
}

ViewPathClusterFinder::ViewPathClusterFinder(const ViewPathClusterFinder& orig) {
}

ViewPathClusterFinder::~ViewPathClusterFinder() {
}

void ViewPathClusterFinder::addPath(int* path) {
    viewPaths->push_back(path);

}

void ViewPathClusterFinder::outputPathsToFile(){
    string filename=string("./lastestTempData/viewPathData");
    cout << "outputing file " << filename << "\n";
    ofstream of;
    of.open(filename.c_str());
    int numPaths=viewPaths->size();
    int numSteps=pathLength;
    of << numSteps << " " <<  " "<<numPaths<< endl;
    
    int* path;
    for (int i = 0; i < numPaths; i++) {
        path=viewPaths->at(i);
        for (int j = 0; j < numSteps; j++) {
            of << path[j] << " ";
        }
        of << endl;
    }
    
    of.close();
    ifstream infile;
}

void ViewPathClusterFinder::loadPathsFromFile(){
    
    string filename=string("./lastestTempData/viewPathData");
    cout << "inputing file " << filename << "\n";
    ifstream inf;
    inf.open(filename.c_str());
    int numPaths;
    int numSteps;
    inf >> numSteps >>numPaths;
    if(numSteps!=oc->numSteps){
        cout<<"error: step count conflict. "<<endl;
        oc->numSteps=numSteps;
    }
    
    int* path;
    for (int i = 0; i < numPaths; i++) {
        path=new int[numSteps]();
        for (int j = 0; j < numSteps; j++) {
            inf>>path[j];
        }
        viewPaths->push_back(path);
    }
    inf.close();
    
    cout<<"vp size "<<viewPaths->size()<<endl;
    
}
vector<int*>* ViewPathClusterFinder::getPathClusterMeans() {
    vector<int*>* meanPaths = new vector<int*>();

    int numberOfClusters = 2;
    vtkSmartPointer<vtkTable> inputData =
            vtkSmartPointer<vtkTable>::New();
   
    for (int c = 0; c < pathLength; ++c) {
        std::stringstream colName;
        colName << "coord " << c*3;
        vtkSmartPointer<vtkDoubleArray> doubleArrayX =
                vtkSmartPointer<vtkDoubleArray>::New();
        doubleArrayX->SetNumberOfComponents(1);
        doubleArrayX->SetName(colName.str().c_str());
        doubleArrayX->SetNumberOfTuples(viewPaths->size());
        colName << "coord " << c*3+1;
        vtkSmartPointer<vtkDoubleArray> doubleArrayY =
                vtkSmartPointer<vtkDoubleArray>::New();
        doubleArrayY->SetNumberOfComponents(1);
        doubleArrayY->SetName(colName.str().c_str());
        doubleArrayY->SetNumberOfTuples(viewPaths->size());
        colName << "coord " << c*3+2;
        vtkSmartPointer<vtkDoubleArray> doubleArrayZ =
                vtkSmartPointer<vtkDoubleArray>::New();
        doubleArrayZ->SetNumberOfComponents(1);
        doubleArrayZ->SetName(colName.str().c_str());
        doubleArrayZ->SetNumberOfTuples(viewPaths->size());

        
        for (int r = 0; r < viewPaths->size(); ++r) {
            vector<int*>::iterator it;
            int* path = viewPaths->at(r); //            int* path=viewPaths->
            //double p[3];;
//            cout<<" test GS c "<<c<<" "<<" path val"<<path[c]<<" r "<<r<<endl;
//            cout<<" test GS c"<<c<<" "<<(float)oc->geoSphere->getView(path[c])->getx()<<" path val"<<path[c]<<endl;
//            
            
            float vx = oc->geoSphere->getView(path[c])->getx();
            //cout<<setprecision(16)<<" using x "<<vx<<endl;
            float vy = oc->geoSphere->getView(path[c])->gety();
            float vz = oc->geoSphere->getView(path[c])->getz();

            //cout<<r<<" adding "<<val<<" to data"<<endl;
            //cout<<"rt "<<randtest<<endl;

            doubleArrayX->SetValue(r, vx);
            doubleArrayY->SetValue(r, vy);
            doubleArrayZ->SetValue(r, vz);
        }

        inputData->AddColumn(doubleArrayX);
        inputData->AddColumn(doubleArrayY);
        inputData->AddColumn(doubleArrayZ);
    }
    vtkSmartPointer<vtkKMeansStatistics> kMeansStatistics =
            vtkSmartPointer<vtkKMeansStatistics>::New();

    kMeansStatistics->SetInput(vtkStatisticsAlgorithm::INPUT_DATA, inputData);
    for (int c = 0; c < pathLength*3; ++c) {
        kMeansStatistics->SetColumnStatus(inputData->GetColumnName(c), 1);
    }
    //    
    //     kMeansStatistics->SetLearnOption( 1 ); // This is on by default.
    //    kMeansStatistics->SetMaxNumIterations( 1 );
    kMeansStatistics->RequestSelectedColumns();
    kMeansStatistics->SetAssessOption(true);
    kMeansStatistics->SetDefaultNumberOfClusters(numberOfClusters);
    kMeansStatistics->Update();
    //kMeansStatistics->GetOutput()->Dump();

    float* minDistances=new float[numberOfClusters];
    int* closestToMin=new int[numberOfClusters];

    pathClusters=new int[viewPaths->size()]();
    for (int i = 0; i < numberOfClusters; i++) {
        minDistances[i]=100;
        int* pathPoints = new int[pathLength*3];
            int clusterCount = 0;
 
            for (unsigned int r = 0; r < kMeansStatistics->GetOutput()->GetNumberOfRows(); r++) {

                vtkVariant cluster = kMeansStatistics->GetOutput()->GetValue(r, kMeansStatistics->GetOutput()->GetNumberOfColumns() - 1);
                vtkVariant distance = kMeansStatistics->GetOutput()->GetValue(r, kMeansStatistics->GetOutput()->GetNumberOfColumns() - 2);
                pathClusters[r]=cluster.ToInt();
                if (pathClusters[r]==1){
                    cout<<" got 1"<<i<<endl;
                }
                //cout<<" cluster is "<<cluster.ToInt()<<" i:"<<i<<endl;
                if (cluster.ToInt() == i) {          
                    if(distance.ToFloat()<minDistances[i]){
                        minDistances[i]=distance.ToFloat();
                        closestToMin[i]=r;
                    }
                }
            }
            //cout<<"closest r was "<<closestToMin[i]<<" dist "<<minDistances[i]<<"viewpaths size:"<<viewPaths->size();
            
        int* path = viewPaths->at(closestToMin[i]);
        meanPaths->push_back(path);
    }

    //    vtkMultiBlockDataSet* outputData = vtkMultiBlockDataSet::SafeDownCast(kMeansStatistics->GetOutputDataObject(vtkStatisticsAlgorithm::OUTPUT_MODEL));
    //    vtkTable* outputMeta = vtkTable::SafeDownCast(outputData->GetBlock(0));
    //    outputMeta->Dump();
    //    cout << " num tabs " << outputData->GetNumberOfBlocks() << endl;
    return meanPaths;

}

void ViewPathClusterFinder::testCluserDetection() {

    int numDims = 40;
    int numPoints = 10;
    int numberOfClusters = 2;

    // Get the points into the format needed for KMeans
    vtkSmartPointer<vtkTable> inputData =
            vtkSmartPointer<vtkTable>::New();

    for (int c = 0; c < numDims; ++c) {
        std::stringstream colName;
        colName << "coord " << c;
        vtkSmartPointer<vtkDoubleArray> doubleArray =
                vtkSmartPointer<vtkDoubleArray>::New();
        doubleArray->SetNumberOfComponents(1);
        doubleArray->SetName(colName.str().c_str());
        doubleArray->SetNumberOfTuples(numPoints);

        for (int r = 0; r < numPoints; ++r) {
            //double p[3];;
            double val;
            if (r < 5) val = (rand() % 10);
            else {
                val = (rand() % 10) + 4;

            }
            //cout<<"rt "<<randtest<<endl;

            doubleArray->SetValue(r, val);
        }
        inputData->AddColumn(doubleArray);
    }

    vtkSmartPointer<vtkKMeansStatistics> kMeansStatistics =
            vtkSmartPointer<vtkKMeansStatistics>::New();

    kMeansStatistics->SetInput(vtkStatisticsAlgorithm::INPUT_DATA, inputData);
    for (int c = 0; c < numDims; ++c) {
        kMeansStatistics->SetColumnStatus(inputData->GetColumnName(c), 1);
    }
    //kMeansStatistics->SetColumnStatus( "Testing", 1 );
    kMeansStatistics->RequestSelectedColumns();
    kMeansStatistics->SetAssessOption(true);
    kMeansStatistics->SetDefaultNumberOfClusters(numberOfClusters);
    kMeansStatistics->Update();

    // Display the results
    kMeansStatistics->GetOutput()->Dump();

    vtkSmartPointer<vtkIntArray> clusterArray =
            vtkSmartPointer<vtkIntArray>::New();
    clusterArray->SetNumberOfComponents(1);
    clusterArray->SetName("ClusterId");

    for (unsigned int r = 0; r < kMeansStatistics->GetOutput()->GetNumberOfRows(); r++) {
        vtkVariant v = kMeansStatistics->GetOutput()->GetValue(r, kMeansStatistics->GetOutput()->GetNumberOfColumns() - 1);
        std::cout << "Point " << r << " is in cluster " << v.ToInt() << std::endl;
        clusterArray->InsertNextValue(v.ToInt());
    }
}

