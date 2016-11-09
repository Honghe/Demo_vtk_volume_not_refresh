//
// Created by honhe on 11/9/16.
//

#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include "MyDirector.h"
#include "ViewPort1.h"

void MyDirector::init() {
    renderWin = vtkSmartPointer<vtkRenderWindow>::New();
    renderWin->SetSize(500, 500);
    renderInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderInteractor->SetRenderWindow(renderWin);
    renderInteractor->Initialize();
//    setDebug();

    ViewPort1 *viewPort1 = new ViewPort1(renderWin, renderInteractor, this);
    viewPort1->init();
    viewPort1->addScalarBarWidget();
    viewPort1->prepareVolume();
//    viewPort1->SetDebug();
    viewPort1->render();
    viewPort1->setTimeEventObserver(1000);
}

void MyDirector::setDebug() {
    renderWin->SetDebug(true);
}

void MyDirector::startInteractor() {
    renderInteractor->Start();
}