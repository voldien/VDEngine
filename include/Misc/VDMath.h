/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_MATH_H_
#define _VD_MATH_H_ 1
#include"VDSystem.h"

/**
 *	Math class.
 */
class VDDECLSPEC VDMath{
public:


	/**
	 *	Clamp number in range.
	 */
	template<class T>
	inline static T clamp(T a, T min, T max){ return VDMath::max<T>( min , VDMath::min<T>( max , a ) ); }
	inline static int clamp(int a, int min, int max){ return VDMath::clamp<int>(a, min ,max);}
	inline static float clampf(float a, float min, float max){ return VDMath::clamp<float>(a, min ,max); }
	inline static double clampd(double a, double min, double max){ return VDMath::clamp<double>(a, min ,max); }

	/**
	 *	Get max value of a and b.
	 */
	template<typename T>
	inline static T max(T a, T b){ return ( (a) < (b) ) ? (b) : (a);}
	inline static float maxf(float a, float b){ return ( (a) < (b) ) ? (b) : (a);}
	inline static float maxd(float a, float b){ return ( (a) < (b) ) ? (b) : (a);}
	inline static float maxi(float a, float b){ return ( (a) < (b) ) ? (b) : (a);}

	/**
	 *	Get min value of a and b.
	 */
	template<typename T>
	inline static T min(T a, T b){ return ( (a) > (b) ) ? (b) : (a);}
	inline static float minf(float a, float b){ return ( (a) > (b) ) ? (b) : (a);}
	inline static float mind(float a, float b){ return ( (a) > (b) ) ? (b) : (a);}
	inline static float mini(float a, float b){ return ( (a) > (b) ) ? (b) : (a);}

	/**
	 *	Get float modular.
	 */
	inline static float modf(float a){double part; return ::modf(a, &part);}
	inline static float modd(double a){ double part; return ::modf(a, &part);}
	inline static float modi(float a, float b){ return ( (a) < (b) ) ? (a) : (b);}

	/**
	 *	Convert degree to radian.
	 */
	template<class T>
	inline static T deg2Rad(T deg) {
		return (deg * VDMath::pi) / 180.0f;
	}

	/**
	 *	Convert radian to degree.
	 */
	template<class T>
	inline static T radToDeg(T deg) {
		return (deg * 180.0f) / VDMath::pi;
	}

	/**
	 * Linear interpolation.
	 */
	template<typename T>
	inline static float lerp(T a, T b, T t) {
		return a + (b - a) * t;
	}

	/**
	 *	Generate 1D guassian.
	 */
	static void VDAPIENTRY guassian1Df(float* guassian, int width, double theta);

	/**
	 *	Generate 2D guassian.
	 */
	static void VDAPIENTRY guassian2Df(float* guassian, int height, float theta);

public:	/*	Mathematical constants.	*/

	static const float pi;
	static const float pi2;
	static const float e;
	static const float infinity;
};


#endif
