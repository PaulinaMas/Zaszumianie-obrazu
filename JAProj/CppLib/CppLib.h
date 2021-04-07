// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef CPPLIB_EXPORTS
#define CPPLIB_API __declspec(dllexport)
#else
#define CPPLIB_API __declspec(dllimport)
#endif
#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
// The Fibonacci recurrence relation describes a sequence F
// where F(n) is { n = 0, a
//               { n = 1, b
//               { n > 1, F(n-2) + F(n-1)
// for some initial integral values a and b.
// If the sequence is initialized F(0) = 1, F(1) = 1,
// then this relation produces the well-known Fibonacci
// sequence: 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
//extern "C" CPPLIB_API void fibonacci_init(
//    const unsigned long long a, const unsigned long long b);

extern "C" CPPLIB_API void zaszum(RGBApixel ** bitmapa, RGBApixel ** bitmapanowa,  int stopien, int llinii, int k, int szer, int wys);