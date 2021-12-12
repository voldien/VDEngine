/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_RESOURCES_H_
#define _VD_RESOURCES_H_ 1
#include "../Core/VDTypes.h"
#include "../VDSystemInfo.h"

/**
 *
 */
class VDDECLSPEC VDResources {
  public:
	template <class T> static inline T *load(const char *cfilename, ...) {
		return (T *)load(cfilename, VDTypeInfo::getType<T>());
	}

	/**
	 *	@Return
	 */
	static void *VDAPIENTRY load(const char *cfilename, const VDTypeInfo &info);

	template <class T> static inline T *loadAll(const char *cfilename, ...) {
		return (T *)loadAll(cfilename, VDTypeInfo::getType<T>());
	}

	/**
	 *	@Return
	 */
	static void *VDAPIENTRY loadAll(const char *cfilename, const VDTypeInfo &info);

	/**
	 *	TODO determine if used.
	 */
	template <class T> static inline T *unLoadAll(const char *cfilename) {
		return (T *)unLoadAll(cfilename, VDTypeInfo::getType<T>());
	}

	/**
	 *	@Return
	 */
	static void *VDAPIENTRY unLoadAll(const char *cfilename, const VDTypeInfo &info);
};

#endif
