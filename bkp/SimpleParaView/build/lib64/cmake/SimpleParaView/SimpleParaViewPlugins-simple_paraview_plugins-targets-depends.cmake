include("${CMAKE_CURRENT_LIST_DIR}/SimpleParaViewCustomFilters-targets.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/SimpleParaViewCustomFilters-vtk-module-properties.cmake")

set(CMAKE_FIND_PACKAGE_NAME_save "${CMAKE_FIND_PACKAGE_NAME}")
set(SimpleParaViewCustomFilters_FIND_QUIETLY "${${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY}")
set(SimpleParaViewCustomFilters_FIND_COMPONENTS)
set(CMAKE_FIND_PACKAGE_NAME "SimpleParaViewCustomFilters")
include("${CMAKE_CURRENT_LIST_DIR}/SimpleParaViewCustomFilters-vtk-module-find-packages.cmake")
set(CMAKE_FIND_PACKAGE_NAME "${CMAKE_FIND_PACKAGE_NAME_save}")
unset(SimpleParaViewCustomFilters_FIND_QUIETLY)
unset(SimpleParaViewCustomFilters_FIND_COMPONENTS)
unset(CMAKE_FIND_PACKAGE_NAME_save)


