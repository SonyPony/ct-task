QT += qml quick widgets sql

CONFIG += c++11

SOURCES += main.cpp \
    types/widgets/controlwidget.cpp \
    types/controls/cloneableitem.cpp \
    types/containers/listdroparea.cpp \
    types/containers/ddplaylist.cpp \
    types/loaders/electionsdataloader.cpp \
    types/controls/graphtypeitem.cpp \
    types/adapters/controlqmladapter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    types/widgets/controlwidget.h \
    types/controls/cloneableitem.h \
    types/containers/listdroparea.h \
    types/containers/ddplaylist.h \
    types/loaders/electionsdataloader.h \
    types/controls/graphtypeitem.h \
    types/adapters/controlqmladapter.h
