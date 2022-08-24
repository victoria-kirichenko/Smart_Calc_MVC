QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backend/controller.cpp \
    frontend/credit.cpp \
    frontend/graphics.cpp \
    main.cpp \
    frontend/consoleview.cpp \
    backend/model.cpp \
    qcustomplot.cpp \
    backend/validator.cpp \
    backend/modelcredit.cpp

HEADERS += \
    frontend/consoleview.h \
    backend/controller.h \
    frontend/credit.h \
    frontend/graphics.h \
    backend/model.h \
    qcustomplot.h \
    backend/validator.h \
    backend/modelcredit.h

FORMS += \
    frontend/consoleview.ui \
    frontend/credit.ui \
    frontend/graphics.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx::ICON = logo\calc_picture.icns
