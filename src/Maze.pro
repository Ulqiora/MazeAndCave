QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/Maze/View/main.cpp \
    ../src/Maze/View/mainwindow.cpp \
    ../src/Maze/Controller/Controller.cpp \
    ../src/Maze/Model/InitMaze.cpp \
    ../src/Maze/Model/FindPath.cpp \
    ../src/Maze/Model/Matrix.cpp \
    ../src/Maze/View/DrawMaze.cpp \
    ../src/Maze/View/ErrorDialog.cpp \
    ../src/Maze/View/CaveWindow.cpp \
    Maze/Model/Cave.cpp \
    Maze/View/CaveDrawWidget.cpp

HEADERS += \
    ../src/Maze/View/mainwindow.h \
    ../src/Maze/Controller/Controller.h \
    ../src/Maze/Model/InitMaze.h \
    ../src/Maze/Model/FindPath.h \
    ../src/Maze/Model/Matrix.h \
    ../src/Maze/View/DrawMaze.h \
    ../src/Maze/View/ErrorDialog.h \
    ../src/Maze/View/CaveWindow.h \
    Maze/Model/Cave.h \
    Maze/View/CaveDrawWidget.h

FORMS += \
    ../src/Maze/View/mainwindow.ui \
    ../src/Maze/View/ErrorDialog.ui \
    Maze/View/CaveWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
