QT += qml quick widgets sql

CONFIG += c++11

SOURCES += main.cpp \
    widgets/controlwidget.cpp \
    controls/cloneableitem.cpp \
    containers/listdroparea.cpp \
    containers/ddplaylist.cpp \
    loaders/electionsdataloader.cpp \
    controls/graphtypeitem.cpp \
    adapters/controlqmladapter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    widgets/controlwidget.h \
    controls/cloneableitem.h \
    containers/listdroparea.h \
    containers/ddplaylist.h \
    loaders/electionsdataloader.h \
    controls/graphtypeitem.h \
    adapters/controlqmladapter.h
