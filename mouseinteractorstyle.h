#ifndef MOUSEINTERACTORSTYLE_H
#define MOUSEINTERACTORSTYLE_H

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkImageData.h>

class VtuAnimationView;

class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    vtkImageData* m_data = nullptr;
    VtuAnimationView* m_pView;
    std::string m_stag;
    double m_tolerance = 0.005;

    MouseInteractorStyle(VtuAnimationView* p) : m_pView(p) {}

    virtual void OnLeftButtonDown() override;
    virtual void OnRightButtonDown() override;
};

#endif // MOUSEINTERACTORSTYLE_H
