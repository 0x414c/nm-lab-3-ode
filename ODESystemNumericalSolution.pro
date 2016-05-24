#-------------------------------------------------
#
# Project created by QtCreator 2016-03-19T18:40:37
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ODESystemNumericalSolution

TEMPLATE = app

CONFIG += c++14 warn_on

#QMAKE_CXX = ccache g++

CONFIG(release, debug|release) {
  message("Building `release' target")
#  QMAKE_CXXFLAGS_RELEASE += -O2 -mtune=generic
#  QMAKE_CXXFLAGS_RELEASE += -O3 -mtune=native
  QMAKE_CXXFLAGS_RELEASE += -O3 -march=native
} else {
  message("Building `debug' target")
  QMAKE_CXXFLAGS_DEBUG += -O0 -march=native
}

equals(QT_ARCH, x86_64) {
  message("Building for `x86_64' target")
  QMAKE_CXXFLAGS += -m64 -mno-fp-ret-in-387
} else {
  equals(QT_ARCH, i386) {
    message("Building for `i386' target")
    QMAKE_CXXFLAGS += -m32
  } else {
    message("Unknown arch `$$QT_ARCH' detected")
  }
}

QMAKE_CXXFLAGS += \
  -msse -msse2 -mfpmath=sse \
  -mieee-fp -mno-fancy-math-387 -malign-double -mpc80 \
  -ffp-contract=off -ffloat-store -frounding-math -fsignaling-nans
#QMAKE_CXXFLAGS += -fext-numeric-literals
#QMAKE_CXXFLAGS += -fopenmp -ftree-parallelize-loops=4 -pthread

QMAKE_CXXFLAGS_WARN_ON += \
  -fdiagnostics-color=auto \
  -Wpedantic -Wall -Wextra -Wdouble-promotion -Wformat

QMAKE_EXT_CPP += cxx

QMAKE_EXT_H += hxx

#DEFINES += QCUSTOMPLOT_CHECK_DATA
#DEFINES += QUAD_PRECISION_ENABLED

INCLUDEPATH += \
  $$PWD/lib/qcustomplot

#LIBS += -lquadmath
#LIBS += -lgomp

SOURCES += \
  lib/qcustomplot/qcustomplot/qcustomplot.cpp \
  src/gui/mainwindow.cxx \
  src/main.cxx \
  src/math/eulerodesolver.cxx \
  src/math/functions.cxx \
  src/math/mathutils.cxx

HEADERS += \
  lib/qcustomplot/qcustomplot/qcustomplot.h \
  src/config.hxx \
  src/globaldefinitions.hxx \
  src/gui/mainwindow.hxx \
  src/math/eulerodesolver.hxx \
  src/math/functions.hxx \
  src/math/mathutils.hxx \
  src/math/numerictypes.hxx

FORMS += forms/mainwindow.ui
