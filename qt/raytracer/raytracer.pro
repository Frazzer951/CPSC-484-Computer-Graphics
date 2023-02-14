QT  += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BRDFs/BRDF.cpp \
    BRDFs/Lambertian.cpp \
    Cameras/Camera.cpp \
    Cameras/Pinhole.cpp \
    GeometricObjects/GeometricObject.cpp \
    GeometricObjects/Plane.cpp \
    GeometricObjects/Sphere.cpp \
    Lights/Ambient.cpp \
    Lights/Directional.cpp \
    Lights/Light.cpp \
    Materials/Material.cpp \
    Materials/Matte.cpp \
    Samplers/Hammersley.cpp \
    Samplers/Jittered.cpp \
    Samplers/MultiJittered.cpp \
    Samplers/NRooks.cpp \
    Samplers/PureRandom.cpp \
    Samplers/Regular.cpp \
    Samplers/Sampler.cpp \
    Samplers/samplers_Sampler.cpp \
    Tracers/MultipleObjects.cpp \
    Tracers/RayCast.cpp \
    Tracers/SingleSphere.cpp \
    Tracers/Tracer.cpp \
    UserInterface/oglwidget.cpp \
    UserInterface/qtraytracer.cpp \
    Utilities/Matrix.cpp \
    Utilities/Normal.cpp \
    Utilities/Point2D.cpp \
    Utilities/Point3D.cpp \
    Utilities/RGBColor.cpp \
    Utilities/RandomUtils.cpp \
    Utilities/Ray.cpp \
    Utilities/ShadeRec.cpp \
    Utilities/Vector3D.cpp \
    World/ViewPlane.cpp \
    World/World.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BRDFs/BRDF.h \
    BRDFs/Lambertian.h \
    Cameras/Camera.h \
    Cameras/Pinhole.h \
    GeometricObjects/GeometricObject.h \
    GeometricObjects/Plane.h \
    GeometricObjects/Sphere.h \
    Lights/Ambient.h \
    Lights/Directional.h \
    Lights/Light.h \
    Materials/Material.h \
    Materials/Matte.h \
    Samplers/Hammersley.h \
    Samplers/Jittered.h \
    Samplers/MultiJittered.h \
    Samplers/NRooks.h \
    Samplers/PureRandom.h \
    Samplers/Regular.h \
    Samplers/Sampler.h \
    Samplers/samplers_Sampler.h \
    Tracers/MultipleObjects.h \
    Tracers/RayCast.h \
    Tracers/SingleSphere.h \
    Tracers/Tracer.h \
    UserInterface/oglwidget.h \
    UserInterface/qtraytracer.h \
    Utilities/Constants.h \
    Utilities/Maths.h \
    Utilities/Matrix.h \
    Utilities/Normal.h \
    Utilities/Point2D.h \
    Utilities/Point3D.h \
    Utilities/RGBColor.h \
    Utilities/RandomUtils.h \
    Utilities/Ray.h \
    Utilities/ShadeRec.h \
    Utilities/Vector3D.h \
    World/ViewPlane.h \
    World/World.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
