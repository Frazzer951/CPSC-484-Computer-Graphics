QT       += core gui
QT       += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BRDFs/BRDF.cpp \
    BRDFs/GlossySpecular.cpp \
    BRDFs/Lambertian.cpp \
    BRDFs/PerfectSpecular.cpp \
    Cameras/Camera.cpp \
    Cameras/Fisheye.cpp \
    Cameras/Orthographic.cpp \
    Cameras/Pinhole.cpp \
    Cameras/Spherical.cpp \
    Cameras/Stereo.cpp \
    Cameras/ThinLens.cpp \
    GeometricObjects/BeveledObjects/BeveledBox.cpp \
    GeometricObjects/BeveledObjects/BeveledWedge.cpp \
    GeometricObjects/CompoundObjects/Archway.cpp \
    GeometricObjects/CompoundObjects/Compound.cpp \
    GeometricObjects/CompoundObjects/Grid.cpp \
    GeometricObjects/CompoundObjects/Rosette.cpp \
    GeometricObjects/GeometricObject.cpp \
    GeometricObjects/Instance.cpp \
    GeometricObjects/PartObjects/ConvexPartSphere.cpp \
    GeometricObjects/Primitives/OpenCylinder.cpp \
    GeometricObjects/Primitives/Plane.cpp \
    GeometricObjects/Primitives/Rect.cpp \
    GeometricObjects/Primitives/Sphere.cpp \
    GeometricObjects/Primitives/Torus.cpp \
    GeometricObjects/Triangles/FlatMeshTriangle.cpp \
    GeometricObjects/Triangles/MeshTriangle.cpp \
    GeometricObjects/Triangles/SmoothMeshTriangle.cpp \
    GeometricObjects/Triangles/SmoothTriangle.cpp \
    GeometricObjects/Triangles/Triangle.cpp \
    Lights/Ambient.cpp \
    Lights/AreaLight.cpp \
    Lights/Directional.cpp \
    Lights/Light.cpp \
    Materials/Emissive.cpp \
    Materials/Material.cpp \
    Materials/Matte.cpp \
    Materials/Reflective.cpp \
    Samplers/Hammersley.cpp \
    Samplers/Jittered.cpp \
    Samplers/MultiJittered.cpp \
    Samplers/NRooks.cpp \
    Samplers/PureRandom.cpp \
    Samplers/Regular.cpp \
    Samplers/Sampler.cpp \
    Samplers/samplers_Sampler.cpp \
    Textures/checker3D.cpp \
    Textures/texture.cpp \
    Tracers/AreaLighting.cpp \
    Tracers/MultipleObjects.cpp \
    Tracers/RayCast.cpp \
    Tracers/SingleSphere.cpp \
    Tracers/Tracer.cpp \
    Tracers/Whitted.cpp \
    UserInterface/oglwidget.cpp \
    UserInterface/qtraytracer.cpp \
    Utilities/BBox.cpp \
    Utilities/Matrix.cpp \
    Utilities/Mesh.cpp \
    Utilities/Normal.cpp \
    Utilities/Point2D.cpp \
    Utilities/Point3D.cpp \
    Utilities/RGBColor.cpp \
    Utilities/RandomUtils.cpp \
    Utilities/Ray.cpp \
    Utilities/ShadeRec.cpp \
    Utilities/Vector3D.cpp \
    Utilities/maths.cpp \
    Utilities/ply.c \
    World/ViewPlane.cpp \
    World/World.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BRDFs/BRDF.h \
    BRDFs/GlossySpecular.h \
    BRDFs/Lambertian.h \
    BRDFs/PerfectSpecular.h \
    Cameras/Camera.h \
    Cameras/Fisheye.h \
    Cameras/Orthographic.h \
    Cameras/Pinhole.h \
    Cameras/Spherical.h \
    Cameras/Stereo.h \
    Cameras/ThinLens.h \
    GeometricObjects/BeveledObjects/BeveledBox.h \
    GeometricObjects/BeveledObjects/BeveledWedge.h \
    GeometricObjects/CompoundObjects/Archway.h \
    GeometricObjects/CompoundObjects/Compound.h \
    GeometricObjects/CompoundObjects/Grid.h \
    GeometricObjects/CompoundObjects/Rosette.h \
    GeometricObjects/GeometricObject.h \
    GeometricObjects/Instance.h \
    GeometricObjects/PartObjects/ConvexPartSphere.h \
    GeometricObjects/Primitives/OpenCylinder.h \
    GeometricObjects/Primitives/Plane.h \
    GeometricObjects/Primitives/Rect.h \
    GeometricObjects/Primitives/Sphere.h \
    GeometricObjects/Primitives/Torus.h \
    GeometricObjects/Triangles/FlatMeshTriangle.h \
    GeometricObjects/Triangles/MeshTriangle.h \
    GeometricObjects/Triangles/SmoothMeshTriangle.h \
    GeometricObjects/Triangles/SmoothTriangle.h \
    GeometricObjects/Triangles/Triangle.h \
    Lights/Ambient.h \
    Lights/AreaLight.h \
    Lights/Directional.h \
    Lights/Light.h \
    Materials/Emissive.h \
    Materials/Material.h \
    Materials/Matte.h \
    Materials/Reflective.h \
    Samplers/Hammersley.h \
    Samplers/Jittered.h \
    Samplers/MultiJittered.h \
    Samplers/NRooks.h \
    Samplers/PureRandom.h \
    Samplers/Regular.h \
    Samplers/Sampler.h \
    Samplers/samplers_Sampler.h \
    Textures/checker3D.h \
    Textures/texture.h \
    Tracers/AreaLighting.h \
    Tracers/MultipleObjects.h \
    Tracers/RayCast.h \
    Tracers/SingleSphere.h \
    Tracers/Tracer.h \
    Tracers/Whitted.h \
    UserInterface/oglwidget.h \
    UserInterface/qtraytracer.h \
    Utilities/BBox.h \
    Utilities/Constants.h \
    Utilities/Maths.h \
    Utilities/Matrix.h \
    Utilities/Mesh.h \
    Utilities/Normal.h \
    Utilities/Point2D.h \
    Utilities/Point3D.h \
    Utilities/RGBColor.h \
    Utilities/RandomUtils.h \
    Utilities/Ray.h \
    Utilities/ShadeRec.h \
    Utilities/Vector3D.h \
    Utilities/ply.h \
    World/ViewPlane.h \
    World/World.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
