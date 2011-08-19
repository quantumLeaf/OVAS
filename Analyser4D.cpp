/*
 * File:   Analyser4D.cpp
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:51
 */

#include "Analyser4D.h"
#include "InfoData.h"
#include "PathVisualiser.h"
#include "TopologyFeature.h"
#include "ViewPathClusterFinder.h"
#include "CurvatureFeature.h"

Analyser4D::Analyser4D() {
    //TemporalChangeFeature2 a;
    oc = new OVASControl();
    oc->geoSphere = new GeoSphere();
    oc->geoSequence = new GeoSequence(oc->geoSphere);
    oc->features = new vector<Feature*>();
    oc->viewEvaluator = new ViewEvaluator(oc);
    oc->pathVisualiser = new PathVisualiser(oc);
    // oc->volume4D=new Volume4D(oc);
    oc->a3d = new Analyser3D(oc);
    oc->filename = new string("");
    oc->volDataFileName = new string("none");

    int startTime = time(NULL);
    char *command = new char[100];
    char* dir = new char[100];

    sprintf(command, "mkdir /home/zoizoi/psyforge/OVASRunData/run%d", (int) startTime);
    system(command);
    sprintf(command, "mkdir /home/zoizoi/psyforge/OVASRunData/run%d/codeDump", (int) startTime);
    system(command);
    sprintf(command, "cp *.cpp /home/zoizoi/psyforge/OVASRunData/run%d/codeDump", (int) startTime);
    system(command);
    sprintf(command, "cp *.h /home/zoizoi/psyforge/OVASRunData/run%d/codeDump", (int) startTime);
    system(command);
    sprintf(command, "cp *.txt /home/zoizoi/psyforge/OVASRunData/run%d/codeDump", (int) startTime);
    system(command);
    sprintf(command, "cp *.config /home/zoizoi/psyforge/OVASRunData/run%d/codeDump", (int) startTime);
    system(command);
    sprintf(command, "cp ./testOVAS /home/zoizoi/psyforge/OVASRunData/run%d/codeDump", (int) startTime);
    system(command);
    sprintf(dir, "/home/zoizoi/psyforge/OVASRunData/run%d/", (int) startTime);
    oc->resultsPath = new string(dir);
}

Analyser4D::Analyser4D(const Analyser4D& orig) {
}

Analyser4D::~Analyser4D() {
}

void Analyser4D::init() {
    cout << "init with fn " << *oc->filename << endl;
    if (*oc->filename != "") {
        loadConfig(*oc->filename);
    }
    oc->a3d->init();

}

void Analyser4D::loadConfig(string filename) {
    cout << "\tloading config file " << filename << endl;

    ifstream inf;

    inf.open(filename.c_str());
    string line;

    while (getline(inf, line)) {

        if (line.length() != 0) {
            istringstream lineStream(line);
            string command;
            lineStream >> command;
            if (command == "iframes") {

                float startParam = 0, endParam = 0;

                lineStream >> startParam >> endParam >> numSteps;
                oc->stepToParamConverter = new StepToParamConverter(startParam, endParam, numSteps);
                cout << "\tiframes start " << startParam << " end " << endParam << " steps " << numSteps << endl;
                oc->numSteps = numSteps;
            }
            if (command == "new") {
                cout << " new" << endl;
                float wCurv, wtChange;
                string gsfilename;
                string screenRend;
                string showInterest;
                string ignoreAreaOnCriticalFrameStr;
                float wArea = 1;
                float wbsize = 0; //.25;
                float wTop = 0; //.75;
                lineStream >> dims >> gsfilename >> screenRend >> wArea >> wbsize >> wTop >> wCurv >> wtChange;

                gsfilename = "./sphereData/" + gsfilename;
                oc->geoSphere->loadGeoSphereFile(gsfilename);

                cout << " is " << oc->geoSphere->getNumVs() << endl;
                //                oc->features->push_back(new Feature(wArea, oc, "area"));
                // cout<<"added area Feature with weight "<<wArea<<endl;
                //   oc->features->push_back(new Feature(wCurv,oc));

                //oc->features->push_back(new TemporalChangeFeature2(wtChange, oc));
                //cout<<"added temporal change Feature with weight "<<wtChange<<endl;



                oc->features->push_back(new CurvatureFeature(wTop, oc, "curvature"));
                //                oc->features->push_back(new TopologyFeature(wTop, oc, "topology"));
                cout << "added topology Feature with weight " << wTop << endl;
                if (screenRend == "onScreen") {
                    oc->viewEvaluator->setScreenRenderOn();
                }
                if (ignoreAreaOnCriticalFrameStr == "ignoreAreaOnCriticalFrame") {
                    //frame->ignoreAreaOnCriticalFrame = true;
                    cout << "TODOignoreAreaOnCriticalFrame is On" << endl;
                } else {
                    //frame->ignoreAreaOnCriticalFrame = false;
                }
                if (showInterest == "showInterest") {
                }
            }

            if (command == "metaballs") {
                float twist;
                lineStream >> twist;
                cout << "\tNew Metaballs twist:" << twist << endl;
                //MetaballsVol4D*
                oc->numSteps = numSteps;
                oc->xDim = oc->yDim = oc->zDim = dims;
                oc->volume4D = dynamic_cast<Volume4D*> (new MetaballsVol4D(oc, twist));
            }
            if (command == "flyingsaucers") {
                cout << "\tNew Flying Saucers " << dims << endl;
                //MetaballsVol4D*
                oc->numSteps = numSteps;
                oc->xDim = oc->yDim = oc->zDim = dims;
                oc->volume4D = dynamic_cast<Volume4D*> (new FlyingSaucersVol4D(oc, 4));
            }
            if (command == "savedRawVolFloat32") {
                string* dataFilename = new string();
                lineStream >> *dataFilename;

                cout << "\tNLoading Vol " << *dataFilename << endl;
                //MetaballsVol4D*
                //oc->numSteps = 1;
                oc->xDim = oc->yDim = oc->zDim = dims;
                oc->volume4D = dynamic_cast<Volume4D*> (new LoadedVol4D(oc, dataFilename));
            }
        }
    }
}

void Analyser4D::analyse() {
    cout << "analysing all " << numSteps << "steps" << endl;
    oc->volume4D->setToStep(0);
    oc->volume4D->findCritcalPoints();

    for (int i = 0; i < numSteps; i++) {
        oc->volume4D->setToStep(i);
        oc->volume4D->updateActor();
        oc->a3d->evalEachView();
        cout << " done step" << endl;
        oc->currentStep++;
    }
}

void Analyser4D::findOptimalPath() {

    InfoData* infoData = new InfoData(oc);
    //cout<<"np"<<endl;
    oc->path = infoData->findOptimalPath();
    // oc->bestViews = infoData->findBestViews();

}

void Analyser4D::findAndOutputPaths() {
    int numFeatures = oc->features->size();
    cout << numFeatures << " features" << endl;
    vector<Feature*>::iterator it;
    //    int f = 0;
    //        for (it = oc->features->begin(); it != oc->features->end(); it++,f++) {
    //            if(f==0) (*it)->setWeight(1);
    //            if(f==1) (*it)->setWeight(0);
    //        }
    findOptimalPath();
    outputPath("change");
    outputBVs("bvs");
    outputPathVis("pathVis.png");

    //    f=0;
    //    for (it = oc->features->begin(); it != oc->features->end(); it++,f++) {
    //        if(f==0) (*it)->setWeight(0);
    //        if(f==1) (*it)->setWeight(1);
    //    }
    //    findOptimalPath();
    //    outputPath("tchange");
    //
    //    f=0;
    //    for (it = oc->features->begin(); it != oc->features->end(); it++,f++) {
    //        if(f==0) (*it)->setWeight(1);
    //        if(f==1) (*it)->setWeight(1);
    //    }
    //    findOptimalPath();
    //    outputPath("comb");

}

void Analyser4D::findPathClusters() {
    cout << " aaa" << endl;
    ViewPathClusterFinder* vpcf = new ViewPathClusterFinder(oc->numSteps, oc);
    int numFeatures = oc->features->size();
    cout << numFeatures << " features being considered" << endl;
    vector<Feature*>::iterator it;

    if (numFeatures == 2) {
        for (int i = 1; i < 1000; i++) {
            int j = 1000 - i;
            // for (int j = 1; j < 10; j++) {
            //if (i==0&&j==0) j=1;//quick fix for 0 total weight case.
            //set up path combination
            float areaW = ((float) i) / 1000;
            float topoW = ((float) j) / 1000;
            it = oc->features->begin();
            (*it)->setWeight(areaW);
            it++;
            (*it)->setWeight(topoW);

            //find path for this combination
            cout << " finding path where a =" << areaW << " and t= " << topoW << endl;
            findOptimalPath();

            //save path to vpcf
            int* path = new int[oc->numSteps];
            for (int i3 = 0; i3 < oc->numSteps; i3++) {
                path[i3] = oc->path[i3];
            }
            vpcf->addPath(path);

        }
    } else if (numFeatures == 1) {
        for (int j = 1; j < 11; j++) {

            //set up path combination
            float areaW = ((float) j) / 10;
            it = oc->features->begin();
            cout << " wei set to " << areaW << endl;
            (*it)->setWeight(areaW);
            findOptimalPath();

            //save path to vpcf
            //            int* path=new int(oc->numSteps);
            //            for (int i3=0;i3<oc->numSteps;i3++){
            //                path[i3]=oc->path[i3];
            //            }
            //            vpcf->addPath(path);
        }
    } else {
        cout << " incorrect number of features for path combinations!! " << endl;
        assert(false);
    }
    meanPaths = vpcf->getPathClusterMeans();
    for (int i = 0; i < meanPaths->size(); i++) {
        cout << " path " << i;
        for (int j = 0; j < oc->numSteps; j++) {
            cout << " " << meanPaths->at(i)[j];
        }
        cout << endl;
    }

    vpcf->outputPathsToFile();

}

void Analyser4D::outputPathVis(string filename) {
    oc->pathVisualiser->VisualisePath(oc->path, oc->numSteps);
}

void Analyser4D::outputMeanPaths(string filestem) {
    for (int i = 0; i < meanPaths->size(); i++) {
        cout << "outputting path for cluster " << i << endl;
        stringstream filenameStem;
        filenameStem << filestem << "cluster" << i;
        oc->path = meanPaths->at(i);
        outputPath(filestem);
    }

}

void Analyser4D::outputPath(string filestem) {

    for (int i = 0; i < numSteps; i++) {
        oc->volume4D->setToStep(i);
        oc->volume4D->updateActor();
        string filename(filestem);
        stringstream s;
        s << i;
        filename += s.str();
        filename += ".png";
        cout << " outputting step " << i << " view " << oc->path[i] << endl;
        oc->viewEvaluator->outputView(oc->geoSphere->getView(oc->path[i]), filename.c_str());
    }
}

void Analyser4D::outputBVs(string filestem) {


    for (int i = 0; i < numSteps; i++) {
        oc->volume4D->setToStep(i);
        oc->volume4D->updateActor();
        string filename(filestem);
        stringstream s;
        s << i;
        filename += s.str();
        filename += ".png";
        oc->viewEvaluator->outputView(oc->geoSphere->getView(oc->bestViews[i]), filename.c_str());
    }
}

void Analyser4D::outputFeatureScores() {
    vector<Feature*>::iterator it;
    for (it = oc->features->begin(); it != oc->features->end(); it++) {
        (*it)->saveScoreToFile();
    }

}

void Analyser4D::inputFeatureScores() {
    vector<Feature*>::iterator it;
    for (it = oc->features->begin(); it != oc->features->end(); it++) {
        (*it)->loadScoreFromFile();
    }

}

void Analyser4D::testContourTree() {
    oc->volume4D->setToStep(0);
    oc->volume4D->testContourTree();
}

void Analyser4D::testReebGraph() {
    oc->volume4D->setToStep(0);
    oc->volume4D->testReebGraph();
}

void Analyser4D::interactSteps() {
    oc->volActor->GetProperty()->SetAmbient(1);
    oc->volActor->GetProperty()->SetDiffuse(0); //SetShading(0);
    oc->volActor->GetProperty()->SetSpecular(0); //SetShading(0);
    //oc->volActor->GetProperty()->SetAmbient(0.3);
    //    oc->volActor->GetProperty()->SetDiffuse(0.7); //SetShading(0);
    //    oc->volActor->GetProperty()->SetSpecular(0.7); //SetShading(0);
    oc->volActor->GetProperty()->SetInterpolationToFlat();
    for (int step = 0; step < oc->numSteps; step++) {
        cout << "setting to " << step << endl;
        oc->volume4D->setToStep(step);
        //oc->volume4D->findCritcalPoints();
        oc->viewEvaluator->readyFeatures();
        oc->volume4D->updateActor();
        cout << "set to " << step << endl;
        oc->viewEvaluator->interact();
    }
}

void Analyser4D::vizMeanPaths() {

    oc->pathVisualiser->vizMeanPaths();
}

void Analyser4D::testFunc() {
    cout << " test code" << endl;

    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    float radius = 1000;
    sphereSource->SetCenter(0, 0, 0);
    sphereSource->SetRadius(radius);
    sphereSource->SetPhiResolution(500);
    sphereSource->SetThetaResolution(500);

    sphereSource->Update();

    vtkPolyData* polyd = sphereSource->GetOutput();
    vtkPointData* pointd = polyd->GetPointData();
    
    vtkSmartPointer<vtkUnsignedCharArray> colors = 
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");
    
    
    vtkLookupTable* lut = vtkLookupTable::New();
    lut->SetHueRange(0, 1); //Red to Blue
    lut->SetAlphaRange(1, 1);
    lut->SetValueRange(1, 1.0);
    lut->SetSaturationRange(1.0, 1.0);
    lut->SetNumberOfTableValues(256 * 256 * 256);
    lut->SetNumberOfColors(256 * 256 * 256);
    lut->SetRange(-1000, 1000); //altering range appear not to effect output
    //        lut->SetTableRange(-100000,10000);
    lut->Build();
    
    
    for (int i = 0; i < polyd->GetNumberOfPoints(); i++) {
        double p[3];
    polyd->GetPoint(i,p);
 
    double dcolor[3];
    lut->GetColor(p[2], dcolor);

    unsigned char color[3];
    for(unsigned int j = 0; j < 3; j++)
      {
      color[j] = static_cast<unsigned char>(255.0 * dcolor[j]);
      }
  
 
    colors->InsertNextTupleValue(color);
    }
    pointd->SetScalars(colors);
   
    //    


    //    
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    mapper->SetInputConnection(polyd->GetProducerPort());
    //mapper->SetLookupTable(lut);
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbient(1); //SetShading(0);
    actor->GetProperty()->SetDiffuse(0); //SetShading(0);
    actor->GetProperty()->SetSpecular(0); //SetShading(0);
    actor->GetProperty()->SetInterpolationToFlat(); //actor->GetProperty()->SetOpacity(0.5);
    //actor->GetProperty()->SetColor(1, 0, 0);

    //        
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderer->SetBackground(0, 0, 0);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(300, 300);

    

    renderer->SetBackground(0, 0, 0);
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->Render();
    renderWindowInteractor->Start();

}