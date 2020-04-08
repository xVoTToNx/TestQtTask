QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edit_project_info_http_request.cpp \
    http_request.cpp \
    load_icon_http_request.cpp \
    login_http_request.cpp \
    login_screen.cpp \
    main.cpp \
    main_window.cpp \
    network_protocol.cpp \
    project_info_http_request.cpp \
    project_info_screen.cpp \
    projects_http_request.cpp \
    projects_screen.cpp

HEADERS += \
    edit_project_info_http_request.h \
    http_request.h \
    load_icon_http_request.h \
    login_http_request.h \
    login_screen.h \
    main_window.h \
    network_protocol.h \
    project_info_http_request.h \
    project_info_screen.h \
    projects_http_request.h \
    projects_screen.h

FORMS += \
    main_window.ui
INCLUDEPATH += C:\Program Files\OpenSSL-Win6\include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Res.qrc
