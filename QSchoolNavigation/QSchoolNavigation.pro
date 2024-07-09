#-------------------------------------------------
#
# Project created by QtCreator
# 项目由QtCreator创建
#
#-------------------------------------------------

# 使用Qt的core和gui模块
QT       += core gui

# 如果Qt的主版本号大于4，添加widgets模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 目标目录设置为当前项目文件夹下的bin目录
DESTDIR = $$PWD/bin

# 目标文件名设置为QSchoolNavigation
TARGET = QSchoolNavigation

# 模板类型为应用程序
TEMPLATE = app

# 以下定义使得编译器在使用被标记为弃用的Qt功能时发出警告
# 根据你的编译器不同，具体的警告也会有所不同
# 请查阅弃用API的文档以了解如何将代码移植到新的API上
DEFINES += QT_DEPRECATED_WARNINGS

# 你还可以使你的代码在使用弃用的API时无法编译
# 为了做到这一点，取消以下行的注释
# 你也可以选择仅禁用特定版本之前弃用的API
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # 禁用Qt 6.0.0之前弃用的所有API

# 源文件列表
SOURCES += \
    aboutwidget.cpp \
    campusprofilewidget.cpp \
    exhibitionwidget.cpp \
    main.cpp \
    mainwidget.cpp \
    mapcorewidget.cpp \
    navigationwidget.cpp

# 头文件列表
HEADERS += \
    aboutwidget.h \
    campusprofilewidget.h \
    exhibitionwidget.h \
    mainwidget.h \
    mapcorewidget.h \
    navigationwidget.h

# UI文件列表
FORMS += \
    aboutwidget.ui \
    campusprofilewidget.ui \
    exhibitionwidget.ui \
    mainwidget.ui \
    navigationwidget.ui

# 资源文件列表
RESOURCES += \
    pictures.qrc \
    other/qss.qrc \
    other/main.qrc

# 在Windows平台上，指定资源文件
win32:RC_FILE   = other/main.rc
