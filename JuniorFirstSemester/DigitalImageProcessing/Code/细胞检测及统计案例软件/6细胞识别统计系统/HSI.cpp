/**$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

#include "stdafx.h"
#include "HSI.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define DEGREES_PER_RADIAN	(180.0 / 3.14159265358979)

// define UNDEFINED_HUE -1.000
#define UNDEFINED_HUE	0.000
#define ZERO_SATURATION 0.0

/**
 =======================================================================================================================
 *
 =======================================================================================================================
 */

int RgbToHsi(RGB *RgbPtr, HSI *HsiPtr)
{
	double	R, G, B, Sum, Quotient;
	double	Radians, Angle, MinValue, MaxValue, TempDouble1, TempDouble2;
	R = ((double) RgbPtr->r) / 255.0;
	G = ((double) RgbPtr->g) / 255.0;
	B = ((double) RgbPtr->b) / 255.0;
	Sum = R + G + B;
	HsiPtr->Intensity = Sum / 3.0;
	MinValue = (R < G) ? R : G;
	MinValue = (B < MinValue) ? B : MinValue;
	MaxValue = (R > G) ? R : G;
	MaxValue = (B > MaxValue) ? B : MaxValue;
	if(HsiPtr->Intensity < 0.00001)
		HsiPtr->Saturation = ZERO_SATURATION;
	else
		HsiPtr->Saturation = 1.0 - (3.0 * MinValue) / Sum;
	if(MinValue == MaxValue)
	{
		HsiPtr->Hue = UNDEFINED_HUE;
		HsiPtr->Saturation = ZERO_SATURATION;
		return 0;
	}

	TempDouble1 = (((R - G) + (R - B)) / 2.0);
	TempDouble2 = (R - G) * (R - G) + (R - B) * (G - B);
	Quotient = (TempDouble1 / sqrt(TempDouble2));
	if(Quotient > 0.99999999999999999)
		Radians = 0.0;
	else if(Quotient < -0.99999999999999999)
		Radians = 3.1415926535;
	else
		Radians = acos(TempDouble1 / sqrt(TempDouble2));
	Angle = Radians * DEGREES_PER_RADIAN;
	if(B > G)
		HsiPtr->Hue = 360.0 - Angle;
	else
		HsiPtr->Hue = Angle;
	return 0;
}
