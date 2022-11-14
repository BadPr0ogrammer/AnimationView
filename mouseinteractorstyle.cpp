#include <QLabel>
#include <qDebug>

#include <vtkSmartPointer.h>
#include <vtkNamedColors.h>
#include <vtkCellPicker.h>
#include <vtkUnstructuredGrid.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkCellData.h>

#include "VtuAnimationView.h"
#include "MouseInteractorStyle.h"

void MouseInteractorStyle::OnLeftButtonDown()
{
    vtkNew<vtkNamedColors> colors;
    int* pos = this->GetInteractor()->GetEventPosition();
    vtkNew<vtkCellPicker> picker;
    picker->SetTolerance(m_tolerance);
    picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());
    if (picker->GetCellId() != -1) {
        vtkIdType id = picker->GetCellId();
        if (m_data) {
            vtkDataArray* vf = m_data->GetCellData()->GetArray(m_stag.c_str());
            if (vf) {
                double* val = vf->GetTuple(id);
                if (val) {
                    char buf[40] = { 0 };
                    sprintf(buf, "%.4f", *val);
                    m_pView->m_picked_val_lb->setText(buf);
                    return;
                }
            }
        }
    }
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void MouseInteractorStyle::OnRightButtonDown()
{
    m_pView->resetInteractor();
}
