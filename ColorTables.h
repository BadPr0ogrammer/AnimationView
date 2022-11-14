#pragma once

#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>

vtkSmartPointer<vtkLookupTable> generate_lookup_table_by_idx(int idx, double rg0, double rg1);

const int ColorTables_num = 6;
extern const char* ColorTables_names[ColorTables_num];
