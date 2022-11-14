QT += core gui widgets

CONFIG += c++17

SOURCES += \
    ColorTables.cpp \
    main.cpp \
    mouseinteractorstyle.cpp \
    ParseFileName.cpp \
    ReadFiles.cpp \
    Settings.cpp \
    SetupDlg.cpp \
    vtuanimationview.cpp

HEADERS += \    
    ColorTables.h \
    mouseinteractorstyle.h \
    ParseFileName.h \
    ReadFiles.h \
    Settings.h \
    SetupDlg.h \
    vtuanimationview.h

INCLUDEPATH += \
    C:/paraview/build/Qt/Core \
    C:/paraview/Qt/Core \
    C:/paraview/build/Qt/Components \
    C:/paraview/build/Qt/Components/pqComponents_autogen/include \
    C:/paraview/Qt/Components \
    C:/paraview/build/Qt/Widgets \
    C:/paraview/Qt/Widgets \
    C:/paraview/build/Qt/Core/pqCore_autogen/include \
    C:/paraview/build/Remoting/Core \
    C:/paraview/Remoting/Core \
    C:/paraview/build/Remoting/ClientServerStream \
    C:/paraview/Remoting/ClientServerStream \
    C:/paraview/build/Remoting/ServerManager \
    C:/paraview/Remoting/ServerManager \
    C:/paraview/build/VTKExtensions/Core \
    C:/paraview/VTKExtensions/Core \
    C:/paraview/build/VTK/ThirdParty/cli11 \
    C:/paraview/VTK/ThirdParty/cli11 \
    C:/paraview/build/ThirdParty/QtTesting/vtkqttesting \
    C:/paraview/ThirdParty/QtTesting/vtkqttesting \
    C:/paraview/build/Remoting/Settings \
    C:/paraview/Remoting/Settings \
    C:/paraview/build/Remoting/Views \
    C:/paraview/Remoting/Views \
    C:/paraview/build/Remoting/Application \
    C:/paraview/Remoting/Application \
    C:/paraview/Remoting/Animation \
    C:/paraview/build/Remoting/Misc \
    C:/paraview/Remoting/Misc \
    C:/paraview/build/Remoting/Animation \
    C:/paraview/build/VTKExtensions/FiltersRendering \
    C:/paraview/VTKExtensions/FiltersRendering \
    C:/paraview/build/VTKExtensions/Extraction \
    C:/paraview/VTKExtensions/Extraction \
    C:/paraview/build/VTKExtensions/Misc \
    C:/paraview/VTKExtensions/Misc \
    C:/paraview/VTK/ThirdParty/doubleconversion \
    C:/paraview/build/ThirdParty/VTK/ThirdParty/doubleconversion/vtkdoubleconversion \
    C:/paraview/build/VTK/Rendering/Parallel \
    C:/paraview/VTK/Rendering/Parallel \
    C:/paraview/VTK/Rendering/Volume \
    C:/paraview/build/VTKExtensions/InteractionStyle \
    C:/paraview/VTKExtensions/InteractionStyle \
    C:/paraview/build/VTK/Filters/ParallelDIY2 \
    C:/paraview/VTK/Filters/ParallelDIY2 \
    C:/paraview/build/CMakeFiles/paraview_client_server \
    C:/paraview/build/CMakeFiles/paraview_server_manager \
    C:/paraview/VTK/ThirdParty/lz4/vtklz4/lib 

LIBS += \
    -LC:/paraview/build/lib/Debug \ 
    -lvtksys-pv5.10d \
    -lvtkCommonCore-pv5.10d \
    -lvtkCommonColor-pv5.10d \
    -lvtkCommonDataModel-pv5.10d \
    -lvtkCommonExecutionModel-pv5.10d \
    -lvtkFiltersCore-pv5.10d \
    -lvtkGUISupportQt-pv5.10d \
    -lvtkInteractionWidgets-pv5.10d \
    -lvtkInteractionStyle-pv5.10d \
    -lvtkRenderingCore-pv5.10d \
    -lvtkRenderingFreeType-pv5.10d \
    -lvtkRenderingImage-pv5.10d \
    -lvtkRenderingOpenGL2-pv5.10d \
    -lvtkRenderingQt-pv5.10d \
    -lvtkRenderingUI-pv5.10d \
    -lvtkRenderingAnnotation-pv5.10d \
    -lvtkIOXML-pv5.10d \
    -lvtkglew-pv5.10d 


RESOURCES = AnimationView.qrc
