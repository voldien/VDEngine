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
#ifndef _VD_RANDOM_H_
#define _VD_RANDOM_H_ 1
#include"VDSystem.h"

/**
 *	Class used for generating
 *	random numbers.
 */
class VDDECLSPEC VDRandom{
public:

	VDRandom(unsigned long long seed = 7564231ULL);

	/**
	 *	Override the seed.
	 */
	void setSeed(unsigned long long seed);

	/**
	 *	Get next random value.
	 */
	unsigned int VDAPIENTRY rand(void);

	/**
	 *	Get next normalized random value.
	 */
	float VDAPIENTRY randfNormalize(void);

	/**
	 *	Get next random float value.
	 */
	float VDAPIENTRY randf(void)const;


private:	/*	Attributes.	*/

	unsigned long long seed;	/*	*/
	unsigned long long mult;	/*	*/
	unsigned long long llong_max;	/*	*/
	float float_max;		/*	*/

};

#endif
