# Install script for directory: /home/mikeuser/VtuAnimationView/SimpleParaView/plugins/SimpleParaViewCustomFilters

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets.cmake"
         "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/SimpleParaViewCustomFilters/CMakeFiles/Export/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/SimpleParaViewCustomFilters/CMakeFiles/Export/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/SimpleParaViewCustomFilters/CMakeFiles/Export/lib64/cmake/SimpleParaView/SimpleParaViewCustomFilters-targets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE RENAME "SimpleParaViewCustomFilters-vtk-module-properties.cmake" FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/SimpleParaViewCustomFilters/CMakeFiles/SimpleParaViewCustomFilters-vtk-module-properties.cmake.install")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/lib64/libElevationFiltersCS.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so"
         RPATH "$ORIGIN:$ORIGIN/../../")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters" TYPE MODULE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so"
         OLD_RPATH "/home/mikeuser/paraview-bin/lib64:"
         NEW_RPATH "$ORIGIN:$ORIGIN/../../")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView/SimpleParaViewCustomFilters/SimpleParaViewCustomFilters.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/SimpleParaViewCustomFilters/ElevationFilters/cmake_install.cmake")

endif()

