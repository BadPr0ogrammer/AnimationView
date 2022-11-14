#include <QApplication>
#include <QStyleFactory>

#include "QVTKRenderWidget.h"

#include "VtuAnimationView.h"

//GeneratedFiles\$(ConfigurationName);GeneratedFiles;.;..\paraview\build\Clients\ParaView;..\paraview\build\VTKExtensions\IOCore;..\paraview\VTKExtensions\IOCore;..\VTK\build\Rendering\Context2D;..\VTK\Rendering\Context2D;..\VTK\build\Charts\Core;..\VTK\Charts\Core;..\paraview\build\Qt\ApplicationComponents;..\paraview\Qt\ApplicationComponents;..\paraview\build\Qt\Core;..\paraview\Qt\Core;..\paraview\build\Qt\Components;../paraview/build/Qt/Components/pqComponents_autogen/include;..\paraview\Qt\Components;..\paraview\build\Qt\Widgets;..\paraview\Qt\Widgets;../paraview/build/Qt/Core/pqCore_autogen/include;..\paraview\build\Remoting\Core;..\paraview\Remoting\Core;..\paraview\build\Remoting\ClientServerStream;..\paraview\Remoting\ClientServerStream;..\paraview\build\Remoting\ServerManager;..\paraview\Remoting\ServerManager;..\paraview\build\VTKExtensions\Core;..\paraview\VTKExtensions\Core;..\VTK\build\ThirdParty\cli11;..\VTK\ThirdParty\cli11;..\paraview\build\ThirdParty\QtTesting\vtkqttesting;..\paraview\ThirdParty\QtTesting\vtkqttesting;..\paraview\build\Remoting\Settings;..\paraview\Remoting\Settings;..\paraview\build\Remoting\Views;..\paraview\Remoting\Views;..\paraview\build\Remoting\Application;..\paraview\Remoting\Application;..\paraview\Remoting\Animation;..\paraview\build\Remoting\Misc;..\paraview\Remoting\Misc;..\paraview\build\Remoting\Animation;..\paraview\build\VTKExtensions\FiltersRendering;..\paraview\VTKExtensions\FiltersRendering;..\paraview\build\VTKExtensions\Extraction;..\paraview\VTKExtensions\Extraction;..\paraview\build\VTKExtensions\Misc;..\paraview\VTKExtensions\Misc;..\VTK\ThirdParty\doubleconversion;../paraview/build/ThirdParty/VTK/ThirdParty/doubleconversion/vtkdoubleconversion;..\VTK\build\Rendering\Parallel;..\VTK\Rendering\Parallel;..\VTK\Rendering\Volume;..\paraview\build\VTKExtensions\InteractionStyle;..\paraview\VTKExtensions\InteractionStyle;..\VTK\build\Filters\ParallelDIY2;..\VTK\Filters\ParallelDIY2;..\paraview\build\CMakeFiles\paraview_client_server;..\paraview\build\CMakeFiles\paraview_server_manager;..\VTK\build\Rendering\Core;..\VTK\Rendering\Core;..\VTK\build\Common\Core;..\VTK\Common\Core;..\VTK\ThirdParty\lz4\vtklz4\lib;..\VTK\build\Filters\Core;..\VTK\Filters\Core;..\VTK\Utilities\KWIML;..\VTK\Common\DataModel;..\VTK\build\IO\XML;..\VTK\IO\XML;..\VTK\build\Rendering\Annotation;..\VTK\Rendering\Annotation;..\VTK\build\Common\DataModel;..\VTK\build\GUISupport\Qt;..\VTK\GUISupport\Qt;..\VTK\build\Common\ExecutionModel;..\VTK\Common\ExecutionModel;..\VTK\build\Common\Color;..\VTK\Common\Color;..\VTK\build\Common\Math;..\VTK\Common\Math;..\VTK\build\Interaction\Style;..\VTK\Interaction\Style;..\VTK\build\Rendering\Image;..\VTK\Rendering\Image;..\VTK\build\Interaction\Widgets;..\VTK\Interaction\Widgets;..\VTK\build\Rendering\OpenGL2;..\VTK\Rendering\OpenGL2;..\VTK\build\Common\Transforms;..\VTK\Common\Transforms;..\VTK\build\Rendering\UI;..\VTK\Rendering\UI;..\VTK\build\Imaging\Core;..\VTK\Imaging\Core;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5\QtWidgets;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5\QtGui;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5\QtCore;debug;%(AdditionalIncludeDirectories)
//C:\paraview\build\lib\Release;C:\vcpkg\installed\x64-windows\lib;C:\vcpkg\installed\x64-windows\lib\manual-link;%(AdditionalLibraryDirectories)
//C:\paraview\build\lib\Debug;C:\vcpkg\installed\x64-windows\debug\lib;C:\vcpkg\installed\x64-windows\debug\lib\manual-link;%(AdditionalLibraryDirectories)
//pqCore-pv5.10d.lib;pqComponents-pv5.10d.lib;pqWidgets-pv5.10d.lib;pqApplicationComponents-pv5.10d.lib;vtkRemotingApplication-pv5.10d.lib;vtkRemotingServerManager-pv5.10d.lib;vtkRemotingCore-pv5.10d.lib;vtkPVVTKExtensionsCore-pv5.10d.lib;vtkCommonCore-pv5.10d.lib;vtkCommonColor-pv5.10d.lib;vtkCommonDataModel-pv5.10d.lib;vtkCommonExecutionModel-pv5.10d.lib;vtkFiltersCore-pv5.10d.lib;vtkGUISupportQt-pv5.10d.lib;vtkInteractionWidgets-pv5.10d.lib;vtkInteractionStyle-pv5.10d.lib;vtkRenderingCore-pv5.10d.lib;vtkRenderingFreeType-pv5.10d.lib;vtkRenderingImage-pv5.10d.lib;vtkRenderingOpenGL2-pv5.10d.lib;vtkRenderingQt-pv5.10d.lib;vtkRenderingUI-pv5.10d.lib;vtkRenderingAnnotation-pv5.10d.lib;vtkIOXML-pv5.10d.lib;vtkglew-pv5.10d.lib;Qt5Widgetsd.lib;Qt5Cored.lib;Qt5Guid.lib;qtmaind.lib;vtksys-pv5.10d.lib

int main(int argc, char *argv[])
{
    setlocale(LC_NUMERIC, "C");
    QSurfaceFormat::setDefaultFormat(QVTKRenderWidget::defaultFormat());

    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

    VtuAnimationView w;
    w.show();

    return a.exec();
}
/*
#include <pqPVApplicationCore.h>

#include "mymainwindow.h"
#include "pqparaviewInitializer.h"
#include "vtkPVPlugin.h"
#include "vtkPVInitializer.h"

// pqCore-pv5.10d.lib;pqComponents-pv5.10d.lib;pqWidgets-pv5.10d.lib;pqApplicationComponents-pv5.10d.lib;vtkRemotingApplication-pv5.10d.lib;vtkRemotingServerManager-pv5.10d.lib;vtkRemotingCore-pv5.10d.lib;vtkPVVTKExtensionsCore-pv5.10d.lib;vtkCommonCore-pv5.10d.lib;vtkCommonColor-pv5.10d.lib;vtkCommonDataModel-pv5.10d.lib;vtkCommonExecutionModel-pv5.10d.lib;vtkFiltersCore-pv5.10d.lib;vtkGUISupportQt-pv5.10d.lib;vtkInteractionWidgets-pv5.10d.lib;vtkInteractionStyle-pv5.10d.lib;vtkRenderingCore-pv5.10d.lib;vtkRenderingFreeType-pv5.10d.lib;vtkRenderingImage-pv5.10d.lib;vtkRenderingOpenGL2-pv5.10d.lib;vtkRenderingQt-pv5.10d.lib;vtkRenderingUI-pv5.10d.lib;vtkRenderingAnnotation-pv5.10d.lib;vtkIOXML-pv5.10d.lib;vtkglew-pv5.10d.lib;Qt5Widgets-pv5.10d.lib;Qt5Core-pv5.10d.lib;Qt5Gui-pv5.10d.lib;qtmain-pv5.10d.lib;vtksys-pv5.10d.lib

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    pqPVApplicationCore appCore(argc, argv);

    myMainWindow w;
    w.show();

    return app.exec();
}
*/
