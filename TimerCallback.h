//
// Created by honhe on 11/3/16.
//

#ifndef DEMO_VTK_TUTORIAL_VTKTIMERCALLBACK_H
#define DEMO_VTK_TUTORIAL_VTKTIMERCALLBACK_H

#include <vtkCommand.h>
#include <vtkObject.h>

class ViewPort1;

class TimerCallback : public vtkCommand {
public:
    vtkTypeMacro(TimerCallback, vtkCommand);

    static TimerCallback *New();

    void init(ViewPort1*);

    virtual void Execute(vtkObject *caller, unsigned long eventId,
                         void *vtkNotUsed(callData));

private:
    int TimerCount;
    ViewPort1 *viewPort1;
};

#endif //DEMO_VTK_TUTORIAL_VTKTIMERCALLBACK_H
