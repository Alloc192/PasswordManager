QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Encoder/vigenerencoder.cpp \
    Passwords/accountitem.cpp \
    Passwords/passwordgenerator.cpp \
    Passwords/passworditem.cpp \
    Passwords/passwordlistcontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    passwordwindow.cpp

HEADERS += \
    Encoder/iencoder.h \
    Encoder/vigenerencoder.h \
    Passwords/accountitem.h \
    Passwords/passwordgenerator.h \
    Passwords/passworditem.h \
    Passwords/passwordlistcontroller.h \
    mainwindow.h \
    passwordwindow.h

FORMS += \
    mainwindow.ui \
    passwordwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

