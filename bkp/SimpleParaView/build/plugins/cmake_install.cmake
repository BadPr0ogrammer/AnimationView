# Install script for directory: /home/mikeuser/VtuAnimationView/SimpleParaView/plugins

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/CMakeFiles/simple_paraview_plugins/simple_paraview_plugins.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE RENAME "SimpleParaViewCustomFilters-vtk-module-find-packages.cmake" FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/CMakeFiles/SimpleParaViewCustomFilters-vtk-module-find-packages.cmake.install")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-simple_paraview_plugins-targets-depends.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets.cmake"
         "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/CMakeFiles/Export/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/CMakeFiles/Export/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/CMakeFiles/Export/lib64/cmake/SimpleParaView/SimpleParaViewPlugins-targets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/SimpleParaView" TYPE FILE FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/lib64/SimpleParaView/SimpleParaView.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/SimpleParaView" TYPE FILE RENAME "SimpleParaViewPlugins-paraview-plugin-properties.cmake" FILES "/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/CMakeFiles/SimpleParaViewPlugins-paraview-plugin-properties.cmake.install")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mikeuser/VtuAnimationView/SimpleParaView/build/plugins/SimpleParaViewCustomFilters/cmake_install.cmake")

endif()

