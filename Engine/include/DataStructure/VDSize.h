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
#ifndef _VD_SIZE_H_
#define _VD_SIZE_H_ 1
#include "VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDSize {
  public:
	VDSize();
	VDSize(int width, int height);
	VDSize(const VDSize &size);

	/**
	 *
	 *	@Return
	 */
	inline int width() const { return this->m[0]; }

	/**
	 *
	 *	@Return
	 */
	inline int height() const { return this->m[1]; }

	/***/
	inline void setWidth(int width) { m[0] = width; }
	/***/
	inline void setHeight(int height) { m[1] = height; }

	/***/
	inline int operator[](unsigned int i) const { return m[i]; }
	/***/
	inline int &operator[](unsigned int i) { return m[i]; }

	/***/
	friend std::istream &operator>>(std::istream &is, const VDSize &t);
	/***/
	friend std::ostream &operator<<(std::ostream &os, const VDSize &t);

	/***/
	friend VDSize operator+(const VDSize &rec1, const VDSize &rec2);
	friend VDSize operator-(const VDSize &rec1, const VDSize &rec2);
	friend VDSize operator*(const VDSize &rec1, const VDSize &rec2);
	friend VDSize operator*(const VDSize &rec1, float scalar);
	friend VDSize operator/(const VDSize &rec1, const VDSize &rect2);
	friend VDSize operator/(const VDSize &rec1, float scalar);

	/**/
	VDSize operator+=(const VDSize &rec2);
	VDSize operator-=(const VDSize &rec2);
	VDSize operator*=(const VDSize &rec2);
	VDSize operator*=(float scalar);
	VDSize operator/=(const VDSize &rect2);
	VDSize operator/=(float scalar);

	VDSize &operator=(const VDSize &v2);

	friend bool operator==(const VDSize &r1, const VDSize &r2);
	friend bool operator!=(const VDSize &r1, const VDSize &r2);

  private: /*	Attributes.	*/
	/**
	 *
	 */
	union {
		int m[2];
		int e[2];
	};
};

inline VDSize::VDSize() {}

inline VDSize::VDSize(int width, int height) {
	this->setWidth(width);
	this->setHeight(height);
}

inline VDSize::VDSize(const VDSize &size) { *this = size; }

inline VDSize &VDSize::operator=(const VDSize &v2) {
	this->setWidth(v2.width());
	this->setHeight(v2.height());
	return *this;
}

inline bool operator==(const VDSize &r1, const VDSize &r2) { return false; }

inline bool operator!=(const VDSize &r1, const VDSize &r2) {
	return (r1.width() == r2.width()) && (r1.height() == r2.height());
}

#endif
