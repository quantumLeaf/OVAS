/* 
 * File:   Analyser4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:51
 */

#include "Analyser4D.h"
#include "InfoData.h"
#include "PathVisualiser.h"

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
                oc->features->push_back(new Feature(wArea, oc));
                oc->features->push_back(new TopologyFeature(wTop,oc));
                //   oc->features->push_back(new Feature(wCurv,oc));
                oc->features->push_back(new TemporalChangeFeature2(wtChange, oc));

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
                oc->volume4D = dynamic_cast<Volume4D*> (new FlyingSaucersVol4D(oc, 1));
            }
            if (command == "savedRawVolFloat32") {
                 string* dataFilename=new string();
                lineStream >> *dataFilename;
               
                cout << "\tNLoading Vol " << dataFilename << endl;
                //MetaballsVol4D*
                oc->numSteps = 1;
                oc->xDim = oc->yDim = oc->zDim = dims;
                oc->volume4D = dynamic_cast<Volume4D*> (new LoadedVol4D(oc, dataFilename));
            }
        }
    }
}

void Analyser4D::analyse() {
    cout << "analysing all " << numSteps << "steps" << endl;
    for (int i = 0; i < numSteps; i++) {
        oc->volume4D->setToStep(i);
        oc->volume4D->updateActor();
        oc->a3d->evalEachView();
        oc->currentStep++;
    }
}

void Analyser4D::findOptimalPath() {

    InfoData* infoData = new InfoData(oc);
    oc->path = infoData->findOptimalPath();
    oc->bestViews = infoData->findBestViews();

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
    //outputBVs("bvs");
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

void Analyser4D::outputPathVis(string filename) {
    oc->pathVisualiser->VisualisePath(oc->path, oc->numSteps);
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
        filename += ".png";
        oc->viewEvaluator->outputView(oc->geoSphere->getView(oc->bestViews[i]), filename.c_str());
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
    oc->volActor->GetProperty()->SetAmbient(0.3);
    oc->volActor->GetProperty()->SetDiffuse(0.7); //SetShading(0);
    oc->volActor->GetProperty()->SetSpecular(0.7); //SetShading(0);
    oc->volActor->GetProperty()->SetInterpolationToPhong();
    for (int step = 0; step < 1; step++) {
        cout<<"setting to "<<step<<endl;
        //oc->volume4D->setToStep(step);
        oc->volume4D->findCritcalPoints();
        
        oc->volume4D->updateActor();
        cout<<"set to "<<step<<endl;
        oc->viewEvaluator->interact();
    }
}
