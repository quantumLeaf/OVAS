/* 
 * File:   PathVisualiser.cpp
 * Author: zoizoi
 * 
 * Created on 07 March 2011, 06:55
 */

#include "PathVisualiser.h"
#include "GeoPoint.h"

PathVisualiser::PathVisualiser(OVASControl* _oc) {
    oc = _oc;
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderer->SetBackground(0, 0, 0);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(300, 300);
    camera = vtkSmartPointer<vtkCamera>::New();
    renderer->SetActiveCamera(camera);
    //hack
    renderWindow->SetOffScreenRendering(false);
    renderer->SetBackground(0, 0, 0); // Background color dark red

    camera->SetFocalPoint(0, 0, 0);
    camera->SetPosition(2, 0, 0);
    //camera->SetParallelProjection(1);
    //camera->SetClippingRange(0, 8);
    sphereRadius = 0.02;


}

PathVisualiser::PathVisualiser(const PathVisualiser& orig) {
}

PathVisualiser::~PathVisualiser() {
}

void PathVisualiser::VisualisePath(int* path, int len) {

    int totColours = 256 * 3;
    int thisColour;
    renderer->SetBackground(1, 1, 1);
    for (int i = 0; i < len; i++) {
        int viewIndex = path[i];
        GeoPoint* view = oc->geoSphere->getView(oc->path[i]);
        float* pos = view->getPoint();

        vtkSmartPointer<vtkSphereSource> aViewSphereS = vtkSmartPointer<vtkSphereSource>::New();

        aViewSphereS->SetCenter(pos[0], pos[1], pos[2]);
        aViewSphereS->SetRadius(sphereRadius);
        aViewSphereS->SetPhiResolution(20);
        aViewSphereS->SetThetaResolution(20);
        thisColour = (totColours / len) * i;

        float b = 0;
        float g = 0;
        float r = 0;
        float ifl = (float) i;
        float len3rd = (float) (len / 3);
        if (ifl < len3rd) {
            b = ifl / len3rd;
        }
        if (ifl >= len3rd && ifl < (2 * len3rd)) {
            g = (ifl - len3rd) / len3rd;
        }
        if (ifl > (2 * len3rd)) {
            r = (ifl - (2 * len3rd)) / len3rd;
        }


        //
        ////        if(b>1){
        ////            g=--b;
        ////        }
        ////        if(b>1){
        ////            r=--b;
        ////            g--;
        ////        }

        cout << " for view " << i << " view " << viewIndex << " pos " << pos[0] << " " << pos[1] << " " << pos[2] << " colours " << r << " " << g << " " << b << endl;
        aViewSphereS->Update();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(aViewSphereS->GetOutputPort());
        vtkSmartPointer<vtkActor> aViewSphereActor = vtkSmartPointer<vtkActor>::New();
        aViewSphereActor->SetMapper(mapper);
        aViewSphereActor->GetProperty()->SetAmbient(1); //SetShading(0);
        aViewSphereActor->GetProperty()->SetDiffuse(0.5); //SetShading(0);
        aViewSphereActor->GetProperty()->SetSpecular(0.5); //SetShading(0);
        //aViewSphereActor->GetProperty()->SetInterpolationToFlat(); //aViewSphereActor->GetProperty()->SetOpacity(0.5);
        aViewSphereActor->GetProperty()->SetColor(r, g, b);
        renderer->AddActor(aViewSphereActor);
        //cout<<"adding actor at "<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
    }

    // Create a sphere
    //  vtkSmartPointer<vtkSphereSource> sphereSource =
    //    vtkSmartPointer<vtkSphereSource>::New();
    //  sphereSource->SetCenter(0.0, 0.0, 0.0);
    //  sphereSource->SetRadius(2.0);
    //
    //  vtkSmartPointer<vtkPolyDataMapper> mapper =
    //    vtkSmartPointer<vtkPolyDataMapper>::New();
    //  mapper->SetInputConnection(sphereSource->GetOutputPort());
    //
    //  vtkSmartPointer<vtkActor> actor =
    //    vtkSmartPointer<vtkActor>::New();
    //  actor->SetMapper(mapper);
    // renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    renderWindowInteractor->Start();
    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow);
    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetInput(windowToImageFilter->GetOutput());
    string filename = "pathVis.png";
    windowToImageFilter->Update();
    filename = *(oc->resultsPath) + filename;
    cout << "OUTPUTTING to " << filename << endl;
    writer->SetFileName(filename.c_str());
    writer->Write();


}

void PathVisualiser::vizMeanPaths() {
    ViewPathClusterFinder* vpcf = new ViewPathClusterFinder(oc->numSteps, oc);
    int numFeatures = oc->features->size();
    cout << numFeatures << " features being considered" << endl;
    vector<Feature*>::iterator it;

    vpcf->loadPathsFromFile();
    vector<int*>* meanPaths = vpcf->getPathClusterMeans();

    for (int i = 0; i < meanPaths->size(); i++) {
        cout << " path " << i;
        for (int j = 0; j < oc->numSteps; j++) {
            cout << " " << meanPaths->at(i)[j];
        }
        cout << endl;
    }
    int numPaths = vpcf->getNumPaths();
    int numSteps = vpcf->getNumSteps();
    int len = numSteps;

    int totColours = 256;
    int thisColour;
    renderer->SetBackground(1, 1, 1);
    int* clusters = vpcf->getPathClusters();
    for (int i = 0; i < numPaths; i++) {
        for (int j = 0; j < numSteps - 1; j++) {
            int v1Index = vpcf->getPathViewIndex(i, j);
            int v2Index = vpcf->getPathViewIndex(i, j + 1);
            //cout<<"ij "<<i<<" "<<j<<endl;
            GeoPoint* view1 = oc->geoSphere->getView(v1Index);
            GeoPoint* view2 = oc->geoSphere->getView(v2Index);

            float* pos1 = view1->getPoint();
            float* pos2 = view2->getPoint();

            vtkSmartPointer<vtkLineSource> aViewLineS = vtkSmartPointer<vtkLineSource>::New();

            aViewLineS->SetPoint1(pos1);
            aViewLineS->SetPoint2(pos2);

            thisColour = (totColours / len) * i;

            float b = 0;
            float g = 0;
            float r = 0;
            float value = ((float) i) / totColours;


            if (clusters[i] == 0) {
                r = i;
            }
            if (clusters[i] == 1) {
                b = i;
            }

            //cout << " for view " << i << " view " << vIndex << " pos " << pos[0] << " " << pos[1] << " " << pos[2] << " colours " << r << " " << g << " " << b << endl;
            aViewLineS->Update();
            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputConnection(aViewLineS->GetOutputPort());
            vtkSmartPointer<vtkActor> aViewLineActor = vtkSmartPointer<vtkActor>::New();
            aViewLineActor->SetMapper(mapper);
            aViewLineActor->GetProperty()->SetAmbient(1); //SetShading(0);
            aViewLineActor->GetProperty()->SetDiffuse(0.5); //SetShading(0);
            aViewLineActor->GetProperty()->SetSpecular(0.5); //SetShading(0);
            aViewLineActor->GetProperty()->SetOpacity(0.5);
            //aViewLineActor->GetProperty()->SetInterpolationToFlat(); //aViewLineActor->GetProperty()->SetOpacity(0.5);
            aViewLineActor->GetProperty()->SetColor(r, g, b);
            renderer->AddActor(aViewLineActor);
            //cout<<"adding actor at "<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
        }

    }



    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (int i = 0; i < oc->geoSphere->n_vertices; i++) {
        float x = oc->geoSphere->vertices[i * 3];
        float y = oc->geoSphere->vertices[i * 3 + 1];
        float z = oc->geoSphere->vertices[i * 3 + 2];
        points->InsertNextPoint(x, y, z);


    }
    vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
    //triangle->GetPointIds()->SetId ( 0, 0 );
    //  triangle->GetPointIds()->SetId ( 1, 1 );
    //  triangle->GetPointIds()->SetId ( 2, 2 );
    for (int i = 0; i < oc->geoSphere->n_faces; i++) {
        vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();

        triangle->GetPointIds()->SetId(0, oc->geoSphere->faces[i * 3]);
        triangle->GetPointIds()->SetId(1, oc->geoSphere->faces[i * 3 + 1]);
        triangle->GetPointIds()->SetId(2, oc->geoSphere->faces[i * 3 + 2]);
        triangles->InsertNextCell(triangle);
    }

    //triangles->InsertNextCell ( triangle );
    //Create a polydata object
    vtkSmartPointer<vtkPolyData> trianglePolyData = vtkSmartPointer<vtkPolyData>::New();

    //Add the geometry and topology to the polydata
    trianglePolyData->SetPoints(points);
    trianglePolyData->SetPolys(triangles);

    //Create mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(trianglePolyData);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->GetProperty()->SetColor(0, 0.9, 0.2);
    actor->GetProperty()->SetOpacity(0.15);
    actor->SetMapper(mapper);

    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    renderWindowInteractor->Start();
    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow);
    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetInput(windowToImageFilter->GetOutput());
    string filename = "pathVis.png";
    windowToImageFilter->Update();
    filename = *(oc->resultsPath) + filename;
    cout << "OUTPUTTING to " << filename << endl;
    writer->SetFileName(filename.c_str());
    writer->Write();
}

