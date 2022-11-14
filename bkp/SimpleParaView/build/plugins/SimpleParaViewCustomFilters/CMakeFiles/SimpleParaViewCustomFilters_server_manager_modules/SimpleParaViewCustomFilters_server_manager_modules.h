#ifndef SimpleParaViewCustomFilters_server_manager_modules_h
#define SimpleParaViewCustomFilters_server_manager_modules_h

#include "SimpleParaViewCustomFilters_server_manager_modules_data.h"
#include <string>
#include <vector>

inline void SimpleParaViewCustomFilters_server_manager_modules_initialize(std::vector<std::string>& xmls)
{
  (void)xmls;
  {
    char *init_string = SimpleParaViewCustomFilters_server_manager_modulesMyElevationFilterGetInterfaces();
    xmls.emplace_back(init_string);
    delete [] init_string;
  }
}

#endif
