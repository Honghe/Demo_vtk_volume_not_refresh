//
// Created by honhe on 11/3/16.
//

#include <vtkRenderWindowInteractor.h>
#include "TimerCallback.h"
#include "ViewPort1.h"
// TimerCallback
//
TimerCallback *TimerCallback::New() {
    TimerCallback *cb = new TimerCallback;
    cb->TimerCount = 0;
    return cb;
}

void TimerCallback::Execute(vtkObject *caller, unsigned long eventId,
                               void *vtkNotUsed(callData)) {
    vtkRenderWindowInteractor *iren =
            static_cast<vtkRenderWindowInteractor *>(caller);

    if (vtkCommand::TimerEvent == eventId) {
        cout << "TimerCount " << TimerCount << endl;
        ++this->TimerCount;
    }

    viewPort1->updateVolumeData();
    viewPort1->render();
}

void TimerCallback::init(ViewPort1 *viewPort1) {
    this->viewPort1 = viewPort1;
}
