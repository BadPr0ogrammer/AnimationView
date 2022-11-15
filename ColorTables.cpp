#include <vtkColorTransferFunction.h>

#include "ColorTables.h"

const char* ColorTables_names[ColorTables_num] = {
	"Jet", "Cold and Hot", "Rainbow", "Spectrum", "Cool", "HSV"
};
const int ColorTables_num_p_1 = 41;
const int cmap_off[ColorTables_num + 1] = { 0, 7, 12, 20, 27, 34,  ColorTables_num_p_1 };
const bool rgb_hsv[ColorTables_num] = { true, true, true, false, false, true };
float cmap[ColorTables_num_p_1][5] =
{
	// Jet(RGB)
	{ 0    , 0  , 0, 0.562},//0
	{ 0.167, 0  , 0, 1    },
	{ 0.333, 0  , 1, 1    },
	{ 0.5  , 0.5, 1, 0.5  },
	{ 0.667, 1  , 1, 0    },
	{ 0.833, 1  , 0, 0    },
	{ 1    , 0.5, 0, 0    },
	// Cold and Hot(RGB)
	{ 0.0,  0.0, 1.0, 1.0, 0.0  },//7
	{ 0.45, 0.0, 0.0, 1.0, 0.45 },
	{ 0.5,  0.0, 0.0, 0.5, 0.5  },
	{ 0.55, 1.0, 0.0, 0.0, 0.55 },
	{ 1.0,  1.0, 1.0, 0.0, 1.0  },
	// Rainbow Desaturated(RGB)
	{ 0.0,   0.278, 0.278, 0.859, 0.0   },//12
	{ 0.143, 0.0,   0.0,   0.361, 0.143 },
	{ 0.285, 0.0,   1.0,   1.0,   0.285 },
	{ 0.429, 0.0,   0.502, 0.0,   0.429 },
	{ 0.571, 1.0,   1.0,   0.0,   0.571 },
	{ 0.714, 1.0,   0.380, 0.0,   0.714 },
	{ 0.857, 0.420, 0.0,   0.0,   0.857 },
	{ 1.0,   0.878, 0.302, 0.302, 1.0   },
	// Spectrum(HSV)
	{ 0    , 0,     0,     0,     1.0 },//20
	{ 0.167, 0.894, 0.102, 0.110, 1.0 },
	{ 0.333, 0.216, 0.494, 0.721, 1.0 },
	{ 0.5  , 0.302, 0.686, 0.290, 1.0 },
	{ 0.667, 0.596, 0.306, 0.639, 1.0 },
	{ 0.833, 1,     0.498, 0,     1.0 },
	{ 1    , 0.651, 0.337, 0.157, 1.0 },
	// Cool(HSV)
	{ 0    , 0.459, 0.694, 0.005, 1.0 },//27
	{ 0.167, 0.345, 0.502, 0.161, 1.0 },
	{ 0.333, 0.314, 0.843, 0.749, 1.0 },
	{ 0.5  , 0.110, 0.584, 0.804, 1.0 },
	{ 0.667, 0.231, 0.408, 0.670, 1.0 },
	{ 0.833, 0.604, 0.408, 1    , 1.0 },
	{ 1    , 0.372, 0.2  , 0.502, 1.0 },
	// HSV(RGB)
	{ 0    , 1, 0, 0, 1.0 },//34
	{ 0.167, 1, 0, 1, 1.0 },
	{ 0.333, 0, 0, 1, 1.0 },
	{ 0.5  , 0, 1, 1, 1.0 },
	{ 0.667, 0, 1, 0, 1.0 },
	{ 0.833, 1, 1, 0, 1.0 },
	{ 1    , 1, 0, 0, 1.0 },
	//41
};

vtkSmartPointer<vtkLookupTable> generate_lookup_table_by_idx(int idx, double rg0, double rg1)
{
	if (idx >= 0 && idx < ColorTables_num) {
		vtkSmartPointer<vtkLookupTable> lookup_table = vtkSmartPointer<vtkLookupTable>::New();
		int num_colors = 256;
		lookup_table->SetNumberOfTableValues(num_colors);

		int it0 = cmap_off[idx];
		int it1 = cmap_off[idx + 1];
		int sz = it1 - it0;
		auto transfer_func = vtkSmartPointer<vtkColorTransferFunction>::New();
		for (int i = 0; i < sz; i++)
			if (rgb_hsv[idx])
				transfer_func->AddRGBPoint(rg0 + (rg1 - rg0) * cmap[it0 + i][0], cmap[it0 + i][1], cmap[it0 + i][2], cmap[it0 + i][3]);
			else
				transfer_func->AddHSVPoint(rg0 + (rg1 - rg0) * cmap[it0 + i][0], cmap[it0 + i][1], cmap[it0 + i][2], cmap[it0 + i][3]);

		for (int i = 0; i < num_colors; i++) {
			double s = rg0 + (rg1 - rg0) * i / num_colors;
			double* cc = transfer_func->GetColor(s);
			lookup_table->SetTableValue(i, cc[0], cc[1], cc[2], 1.0);
		}
		lookup_table->Build();
		return lookup_table;
	}
	return nullptr;
}
