#ifndef JPEGTOBPLIB_H
#define JPEGTOBPLIB_H

#include "Resource.h"
#define JPEGTOBMP_LIB

#ifdef JPEGTOBMP_LIB
#define  JPEGTOBMP_LIB_CLASS _declspec(dllexport)
#define  JPEGTOBMP_LIB_API   _declspec(dllexport)
#else
#define  JPEGTOBMP_LIB_CLASS _declspec(dllimport)
#define  JPEGTOBMP_LIB_API   _declspec(dllimport)
#endif



#endif