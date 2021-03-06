/*
 * File:   CurvatureFeature.cpp
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#include "CurvatureFeature.h"

CurvatureFeature::CurvatureFeature(float weight, OVASControl* oc, string name) : Feature(weight, oc, name) {

    intScoreData = ArrayTools::allocate2DArray<int>(oc->numSteps, oc->geoSphere->getNumVs());
    for (int i = 0; i < oc->numSteps; i++) {
        for (int j = 0; j < oc->geoSphere->getNumVs(); j++) {
            intScoreData[i][j] = 0;

        }
    }
    colourB = 0;
    colourG = 0;
    colourR = 1;

    cout << "new Curvature feature" << endl;
}

CurvatureFeature::CurvatureFeature(const CurvatureFeature& orig) {
}

CurvatureFeature::~CurvatureFeature() {
}

void CurvatureFeature::readyRenderer(vtkSmartPointer<vtkRenderer> _renderer) {
//    cout<<" called readyREND!"<<endl;
    //cout<<"ready rend w "<<weight<<endl;
    renderer = _renderer;
    renderWindow = renderer->GetRenderWindow();
    camera = renderer->GetActiveCamera();
    framebuffer = new FrameBuffer(renderer->GetRenderWindow());

    vtkCurvatures *curv = vtkCurvatures::New();
    curv->SetInputConnection(oc->volume4D->contourer->GetOutputPort());
    curv->SetCurvatureTypeToGaussian();
    //        curv->SetCurvatureTypeToGaussian();
    //curv->SetCurvatureTypeToMinimum();
    //curvaturesFilter->SetCurvatureTypeToMaximum();
    
    vtkLookupTable* lut = vtkLookupTable::New();
    lut->SetHueRange(0.6, 0); //Red to Blue
    lut->SetAlphaRange(1, 1);
    lut->SetValueRange(1, 1.0);
    lut->SetSaturationRange(1.0, 1.0);
    lut->SetNumberOfTableValues(256 * 256 * 256);
    lut->SetRange(0, 10); //altering range appear not to effect output
    lut->Build();


    vtkSmartPointer<vtkUnsignedCharArray> colors =
            vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");

    vtkSmartPointer<vtkPolyData> polyd = curv->GetOutput();
    vtkSmartPointer<vtkPointData> pointd = oc->volume4D->contourer->GetOutput()->GetPointData();
    polyd->Update();
    for (int i = 0; i < polyd->GetNumberOfPoints(); i++) {
        
        double val= log(abs(vtkDoubleArray::SafeDownCast(polyd->GetPointData()->GetScalars())->GetValue(i)));
        double dcolor[3];
        lut->GetColor(val, dcolor);
       
        unsigned char color[3];
        for (unsigned int j = 0; j < 3; j++) {
            color[j] = static_cast<unsigned char> (255.0 * dcolor[j]);
        }

        colors->InsertNextTupleValue(color);
    }
    pointd->SetScalars(colors);
    pointd->Update();
    
     vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    mapper->SetInputConnection(oc->volume4D->contourer->GetOutput()->GetProducerPort());
    //mapper->SetLookupTable(lut);
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbient(1); //SetShading(0);
    actor->GetProperty()->SetDiffuse(0); //SetShading(0);
    actor->GetProperty()->SetSpecular(0); //SetShading(0);
    actor->GetProperty()->SetInterpolationToFlat(); //actor->GetProperty()->SetOpacity(0.5);
    //actor->GetProperty()->SetColor(1, 0, 0);

    //           polyMap2->SetInputConnection(oc->volume4D->contourer->GetOutput()->GetProducerPort());
//  
//    vtkPolyDataMapper* polyMap2 = vtkPolyDataMapper::New();
//   
    //polyMap2->SetInputConnection(oc->volume4D->contourer->GetOutput()->GetProducerPort());
    mapper->GetInput()->Update();
//    
//    
    vtkSmartPointer<vtkXMLPolyDataWriter> writer =
            vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("test.vtp");
    writer->SetInput(mapper->GetInput());

    // Optional - set the mode. The default is binary.
    //writer->SetDataModeToBinary();
    writer->SetDataModeToAscii();

    writer->Write();
//
    oc->volActor->SetMapper(mapper);
    oc->volActor->Modified();
   

}

void CurvatureFeature::climbDown() {
    // vector<CriticalPoint*>::iterator it;
    std::vector< vtkSmartPointer<vtkActor> >::const_iterator it;
    for (it = actors->begin(); it != actors->end(); it++) {
        renderer->RemoveActor((*it));
    }
    delete framebuffer;

    //    for (it=oc->volume4D->criticalPoints->begin();it!=oc->volume4D->criticalPoints->end();it++){
    //        renderer->RemoveActor((*it)->getActor());
    //    }
}

void CurvatureFeature::scoreFeature(GeoPoint* view) {

    if (weight == 0) {
        scoreData[oc->currentStep][oc->currentView] = 0;
        return;
    }
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());

    //cout<<" active redballs "<<redBallCount<<endl;
    renderWindow->Render();

    int redPix = countColour(colourR, colourG, colourB, framebuffer);
    //cout<<" counted "<<redPix<<endl;

    scoreData[oc->currentStep][oc->currentView] = redPix;


}

