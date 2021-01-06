// #pragma once
#ifndef COLORS_H
#define COLORS_H

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

/* 
 ? This header file defines a struct called Color and provides some
 ? already defined colors that can be used for drawing stuff.
 */

struct Color {
    GLubyte rgb[3];
};

const Color black = {0, 0, 0};
const Color white = {255, 255, 255};
const Color red = {194, 17, 17};
const Color orange = {227, 88, 7};
const Color yellow = {242, 216, 15};
const Color aqua = {141, 227, 20};
const Color lightBlue = {20, 217, 227};
const Color blue = {20, 137, 227};
const Color purple = {124, 20, 227};
const Color pink = {217, 20, 227};

#endif // COLORS_H
                