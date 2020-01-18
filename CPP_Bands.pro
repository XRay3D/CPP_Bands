TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

#win32-g++ {
#   QMAKE_CXXFLAGS += -Werror
#}
#win32-msvc*{
#   QMAKE_CXXFLAGS += /WX
#}

DEFINES += __TEST__


SOURCES += \
    main.cpp

DISTFILES += \
    main_.cpp \
    matrix_sum.cpp \
    main_2.cpp \
    TeamTasks.cpp \
