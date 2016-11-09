//
// Created by honhe on 11/9/16.
//

#ifndef DEMO_VTK_VOLUME_NOT_REFRESH_VIEWPORT1_H
#define DEMO_VTK_VOLUME_NOT_REFRESH_VIEWPORT1_H

#include <vtkStructuredPoints.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarWidget.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>
#include "MyDirector.h"

using namespace std;

class ViewPort1 {
public:
    ViewPort1(vtkSmartPointer<vtkRenderWindow> renderWin, vtkSmartPointer<vtkRenderWindowInteractor> renderInteractor,
                  MyDirector *myDirector);

    void init();

    vtkSmartPointer<vtkStructuredPoints> volumeData;

    void initVolumeData();

    vtkSmartPointer<vtkRenderWindow> renderWin;
    MyDirector *myDirector;
    vtkSmartPointer<vtkRenderWindowInteractor> renderInteractor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper> volumeMapper;

    void addScalarBarWidget();

    vtkSmartPointer<vtkLookupTable> lookupTable;
    vtkIdType colorNumber;
    vector<vector<double>> myLookTable;
    vtkSmartPointer<vtkScalarBarWidget> scalarBarWidget;

    void prepareVolume();

    vtkSmartPointer<vtkVolume> volume;

    void render();

    void initVolumeDataMemory();

    void updateVolumeData();

    void setTimeEventObserver(int interval);

    void printVolumeData();

    void SetDebug();
};


#endif //DEMO_VTK_VOLUME_NOT_REFRESH_VIEWPORT1_H
