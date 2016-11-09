//
// Created by honhe on 11/9/16.
//

#include <vtkStructuredPoints.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>
#include <vtkScalarBarActor.h>
#include <vtkLookupTable.h>
#include <vtkTextProperty.h>
#include <vtkScalarBarRepresentation.h>
#include <vtkScalarBarWidget.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include "ViewPort1.h"
#include "jet256colormap.h"
#include "TimerCallback.h"


ViewPort1::ViewPort1(vtkSmartPointer<vtkRenderWindow> renderWin,
                     vtkSmartPointer<vtkRenderWindowInteractor> renderInteractor, MyDirector *myDirector) {
    this->renderWin = renderWin;
    this->myDirector = myDirector;
    this->renderInteractor = renderInteractor;
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.1, 0.1, 0.1);
    renderWin->AddRenderer(renderer);
    volumeMapper = vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
}

void ViewPort1::init() {
    colorNumber = 256;
    vector<vector<double>> p((unsigned long) colorNumber, vector<double>(4));
    myLookTable = p;
    volumeData = vtkSmartPointer<vtkStructuredPoints>::New();
    initVolumeDataMemory();
    initVolumeData();
}

void ViewPort1::SetDebug() {
    renderer->SetDebug(true);
    volumeMapper->SetDebug(true);
    volume->SetDebug(true);
}

void ViewPort1::initVolumeDataMemory() {
    volumeData = vtkSmartPointer<vtkStructuredPoints>::New();
    int extent = 10;
    volumeData->SetExtent(0, extent, 0, extent, 0, extent);
    volumeData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
}

void ViewPort1::initVolumeData() {
    int *dims = volumeData->GetDimensions();
    for (int z = 0; z < dims[2]; z++) {
        for (int y = 0; y < dims[1]; y++) {
            for (int x = 0; x < dims[0]; x++) {
                unsigned char *pixel = static_cast<unsigned char *>(volumeData->GetScalarPointer(x, y, z));
                // if the init first frame is a pure color, then the subsequent color change will not be render
                pixel[0] = 1; // pure color, the subsequent color will not be render
//                pixel[0] = rand() % 255; // non pure color, the subsequent color will be render
            }
        }
    }
    printVolumeData();
}

void ViewPort1::updateVolumeData() {
    int *dims = volumeData->GetDimensions();
    for (int z = 0; z < dims[2]; z++) {
        for (int y = 0; y < dims[1]; y++) {
            for (int x = 0; x < dims[0]; x++) {
                unsigned char *pixel = static_cast<unsigned char *>(volumeData->GetScalarPointer(x, y, z));
                pixel[0] = rand() % 255;
            }
        }
    }
    volumeData->Modified();
    printVolumeData();
}

void ViewPort1::printVolumeData() {
    int *dims = volumeData->GetDimensions();
    for (int z = 0; z < dims[2]; z++) {
        for (int y = 0; y < dims[1]; y++) {
            for (int x = 0; x < dims[0]; x++) {
                unsigned char *pixel = static_cast<unsigned char *>(volumeData->GetScalarPointer(x, y, z));
                printf("%03d ", pixel[0]);
            }
            cout << endl;
        }
    }
}

void ViewPort1::setTimeEventObserver(int interval) {
    const vtkSmartPointer<TimerCallback> &timerCallback = vtkSmartPointer<TimerCallback>::New();
    timerCallback->init(this);
    renderInteractor->AddObserver(vtkCommand::TimerEvent, timerCallback);
    renderInteractor->CreateRepeatingTimer(interval);
}

void ViewPort1::addScalarBarWidget() {
    const vtkSmartPointer<vtkScalarBarActor> scalarBarActor = vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBarActor->SetMaximumWidthInPixels(72);
    scalarBarActor->SetOrientationToHorizontal();
    scalarBarActor->UnconstrainedFontSizeOn();
    vtkTextProperty *pProperty = scalarBarActor->GetLabelTextProperty();
    pProperty->SetFontSize(16);
    pProperty->SetColor(1, 1, 1);
    lookupTable = vtkSmartPointer<vtkLookupTable>::New();
    lookupTable->SetRange(0, colorNumber);
    lookupTable->SetRampToLinear();
    lookupTable->SetNumberOfTableValues(colorNumber);
    lookupTable->Build();

    // use jet 256 colormap
    for (int i = 0; i < colorNumber; ++i) {
        vector<double> &row = myLookTable[i];
        float *tableValue = Jet256ColorMap::colormap[i];
        for (int j = 0; j < 4; ++j) {
            row[j] = tableValue[j];
        }
//            printf("%d %03.2f %03.2f %03.2f\n", i, row[0], row[1], row[2]);
    }

    for (int k = 0; k < colorNumber; ++k) {
        vector<double> &row = myLookTable[k];
        lookupTable->SetTableValue(k, row[0], row[1], row[2], row[3]);
    }

    scalarBarActor->SetLookupTable(lookupTable);
    scalarBarWidget = vtkSmartPointer<vtkScalarBarWidget>::New();
    scalarBarWidget->SetInteractor(renderInteractor);
    scalarBarWidget->SetCurrentRenderer(renderer);
    scalarBarWidget->SetScalarBarActor(scalarBarActor);
    vtkScalarBarRepresentation *pRepresentation = scalarBarWidget->GetScalarBarRepresentation();
    pRepresentation->SetPosition(0.9, 0.053796);
    pRepresentation->SetShowBorderToOff();
    scalarBarWidget->On();
}

void ViewPort1::prepareVolume() {
    const vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    for (int i = 2; i < colorNumber; ++i) {
        vector<double> &rgba = myLookTable[i];
        colorTransferFunction->AddRGBPoint(i, rgba[0], rgba[1], rgba[2]);
    }
    const vtkSmartPointer<vtkPiecewiseFunction> alphaChannelFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    alphaChannelFunction->AddPoint(0, 0.2);
    alphaChannelFunction->AddPoint(255, 0.2);

    const vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(colorTransferFunction);
    volumeProperty->SetScalarOpacity(alphaChannelFunction);
    volumeMapper->SetInputData(volumeData);
    volumeMapper->SetSampleDistance(1);
    volumeMapper->SetImageSampleDistance(1);
    volumeMapper->AutoAdjustSampleDistancesOff();   // for better display when rotate
    volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);
    renderer->AddVolume(volume);
}

void ViewPort1::render() {
    renderWin->Render();
}
