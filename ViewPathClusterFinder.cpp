/* 
 * File:   ViewPathClusterFinder.cpp
 * Author: zoizoi
 * 
 * Created on 18 June 2011, 10:15
 */

#include "ViewPathClusterFinder.h"

ViewPathClusterFinder::ViewPathClusterFinder(int plen) {
    viewPaths=new vector<int*>();
    pathLength=plen;
} 


ViewPathClusterFinder::ViewPathClusterFinder(const ViewPathClusterFinder& orig) {
}

ViewPathClusterFinder::~ViewPathClusterFinder() {
}
void ViewPathClusterFinder::addPath(int* path){
    viewPaths->push_back(path);
}

vector<int*> ViewPathClusterFinder::getPathClusterMeans(){
    vtkSmartPointer<vtkTable> inputData =
            vtkSmartPointer<vtkTable>::New();
    
    for (int c = 0; c < pathLength; ++c) {
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
            if (r<5) val = (rand() % 10);
            else{val=(rand() % 10)+4;
                
            }
            //cout<<"rt "<<randtest<<endl;

            doubleArray->SetValue(r, val);
        }

        inputData->AddColumn(doubleArray);
    }
}
void ViewPathClusterFinder::testCluserDetection() {

    int numDims = 40;
    int numPoints = 10;

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
            if (r<5) val = (rand() % 10);
            else{val=(rand() % 10)+4;
                
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
    kMeansStatistics->SetDefaultNumberOfClusters(2);
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

