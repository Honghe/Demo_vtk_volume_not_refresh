#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>
#include "MyDirector.h"


int main() {
    MyDirector *director = new MyDirector();
    director->init();
    director->startInteractor();
    delete director;

    return 0;
}

