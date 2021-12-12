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
#ifndef _VD_TOOL_BASE_H_
#define _VD_TOOL_BASE_H_ 1
#include"../Core/VDEvent.h"

/**
 *
 */
class VDDECLSPEC VDToolBase : public VDEvent{
public:

	VDToolBase(){}
	~VDToolBase(){}

	/**
	 *	Draw method call.
	 */
	virtual void VDAPIENTRY draw() = 0;

	/**
	 *	Release resources call.
	 */
	virtual void VDAPIENTRY release() = 0;

	/**
	 *	Logic update call.
	 */
	virtual void VDAPIENTRY update() = 0;

};

#endif
