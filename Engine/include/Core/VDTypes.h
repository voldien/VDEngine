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
#ifndef _VD_TYPE_INFO_H_
#define _VD_TYPE_INFO_H_ 1
#include <type_traits>
#include <typeindex>
#include <typeinfo>

#include "../VDDef.h"

/**
 *	Simple class
 */
class VDDECLSPEC VDTypeInfo {
  public:
	VDTypeInfo();
	VDTypeInfo(const VDTypeInfo &type);
	VDTypeInfo(const std::type_info &type);
	VDTypeInfo(const std::type_info &type, long unsigned int size);

  protected: /*	Attributes.	*/
	std::type_info *type;
	unsigned int typeSize;

  public:
	/**
	 *	@Return
	 */
	bool isInherited(const VDTypeInfo &type) const;

	/**
	 *	@Return
	 */
	template <class T> inline bool is() { return typeid(T) == *this->type; }

	/**
	 *
	 */
	bool operator==(const VDTypeInfo *rh);
	bool operator!=(const VDTypeInfo *rh);
	bool operator==(const std::type_info &_type) const;
	bool operator!=(const std::type_info &_type) const;
	bool operator==(unsigned int rh);
	bool operator!=(unsigned int rh);

	/**
	 *	@Return
	 */
	inline unsigned int getTypeSize() const { return this->typeSize; }

	/**
	 *
	 */
	inline void setTypeSize(unsigned int size) { this->typeSize = size; }

	/**
	 *	@Return
	 */
	inline std::type_info *getType() const { return this->type; }

	/**
	 *
	 */
	inline void setType(std::type_info *type) { this->type = type; }

	/**
	 *	@Return
	 */
	bool isPointer() const;

	/**
	 *	@Return
	 */
	bool isFunction() const;

	/**
	 *	Get type name.
	 */
	const char *getName() const;

	/**
	 *	@Return
	 */
	VDTypeInfo &operator=(const VDTypeInfo &type);

  public: /*	Public method.	*/
	template <class T> static inline VDTypeInfo getType() { return VDTypeInfo(typeid(T), sizeof(T)); }
};

#endif
