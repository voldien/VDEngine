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
#ifndef _VD_POINT_H_
#define _VD_POINT_H_ 1
#include"../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDPoint{
public:
	VDPoint();
	VDPoint(const VDPoint& point);
	VDPoint(int x, int y);
	VDPoint(int v){this->setX(v); this->setY(v);}

	/**
	 *	@Return
	 */
	inline int x()const{return this->m[0];}

	/**
	 *	@Return
	 */
	inline int y()const{return this->m[1];}

	/**
	 *
	 */
	inline void setX(int x){this->m[0] = x;}

	/**
	 *
	 */
	inline void setY(int y){this->m[1] = y;}

	/**/
	inline int operator[](unsigned int i)const{return m[i];}
	inline int& operator[](unsigned int i){return m[i];}

	/**/
	friend std::istream &operator>>(std::istream &is, VDPoint& t);
	friend std::ostream &operator<<(std::ostream &os, const VDPoint& t);


	/**/
	friend VDPoint operator+(const VDPoint& lh, const VDPoint& rh);
	friend VDPoint operator-(const VDPoint& poi1, const VDPoint& poi2);
	friend VDPoint operator*(const VDPoint& poi1, const VDPoint& poi2);
	friend VDPoint operator*(const VDPoint& poi1, float scalar);
	friend VDPoint operator/(const VDPoint& poi1, const VDPoint& poi2);
	friend VDPoint operator/(const VDPoint& poi1, float scalar);

	/**/
	VDPoint& operator+=(const VDPoint& rec2);
	VDPoint& operator-=(const VDPoint& rec2);
	VDPoint& operator*=(const VDPoint& rec2);
	VDPoint& operator*=(float scalar);
	VDPoint& operator/=(const VDPoint& rect2);
	VDPoint& operator/=(float scalar);

	/**/
	VDPoint& operator=(const VDPoint& v2);


	/**/
	friend bool operator==(const VDPoint& r1, const VDPoint& r2);
	friend bool operator!=(const VDPoint& r1, const VDPoint& r2);

private:	/*	Attributes.	*/

	union{
		int m[2];
		int e[2];
	};
};

inline VDPoint::VDPoint(){}

inline VDPoint::VDPoint(const VDPoint& point){
	*this = point;
}

inline VDPoint::VDPoint(int x, int y){
	this->setX(x);
	this->setY(y);
}


inline VDPoint operator+(const VDPoint& lh, const VDPoint& rh){
	return VDPoint(lh.x() + rh.x(), lh.y() + rh.y());
}

inline VDPoint operator-(const VDPoint& lh, const VDPoint& rh){
	return VDPoint(lh.x() - rh.x(), lh.y() - rh.y());
}
/*
Point Point::operator*(float lh)const{
	return Point(this->x * lh, this->y * lh);
}
Point Point::operator*(const Point& lh)const{
	return Point(this->x * lh.x, this->y * lh.y);
}

Point Point::operator/(float lh)const{
	return Point(this->x + lh, this->y + lh);
}
Point Point::operator/(const Point& lh)const{
	return Point(this->x / lh.x, this->y / lh.y);
}
*/


inline VDPoint& VDPoint::operator+=(const VDPoint& rh){
	this->m[0] += rh.x();
	this->m[1] += rh.y();
	return *this;
}

inline VDPoint& VDPoint::operator-=(const VDPoint& rh){
	this->m[0] -= rh.x();
	this->m[1] -= rh.y();
	return *this;
}

inline VDPoint& VDPoint::operator*=(float rh){
	this->m[0] *= rh;
	this->m[1] *= rh;
	return *this;
}

inline VDPoint& VDPoint::operator*=(const VDPoint& rh){
	this->m[0] *= rh.x();
	this->m[1] *= rh.y();
	return *this;
}

inline VDPoint& VDPoint::operator/=(float rh){
	this->m[0] /= rh;
	this->m[1] /= rh;
	return *this;
}

inline VDPoint& VDPoint::operator/=(const VDPoint& rh){
	this->m[0] /= rh.x();
	this->m[1] /= rh.y();
	return *this;
}

inline VDPoint& VDPoint::operator=(const VDPoint& rh){
	this->m[0] = rh.x();
	this->m[1] = rh.y();
	return *this;
}


#endif
