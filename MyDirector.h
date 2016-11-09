//
// Created by honhe on 11/9/16.
//

#ifndef DEMO_VTK_VOLUME_NOT_REFRESH_MYDIRECTOR_H
#define DEMO_VTK_VOLUME_NOT_REFRESH_MYDIRECTOR_H

#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkVolumeProperty.h>
#include <vtkRenderWindowInteractor.h>


class MyDirector {
public:
    void init();

    vtkSmartPointer<vtkRenderWindow> renderWin;
    vtkSmartPointer<vtkRenderWindowInteractor> renderInteractor;

    void startInteractor();

    void setDebug();
};


#endif //DEMO_VTK_VOLUME_NOT_REFRESH_MYDIRECTOR_H
