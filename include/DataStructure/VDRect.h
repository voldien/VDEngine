/*
    Copyright (C) 2015  Valdemar Lindberg

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
#ifndef _VD_RECT_H_
#define _VD_RECT_H_ 1
#include"../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDRect{
public:
	VDRect(void);
	VDRect(float x, float y, float width, float height);
	VDRect(const VDRect& rect);

	/**
	 *
	 */
	inline void setX(float x){this->m[0] = x;}

	/**
	 *
	 */
	inline void setY(float y){this->m[1] = y;}

	/**
	 *
	 */
	inline void setWidth(float width){this->m[2] = width;}

	/**
	 *
	 */
	inline void setHeight(float height){this->m[3] = height;}

	/**
	 *
	 */
	inline float x(void)const{return m[0];}

	/**
	 *
	 */
	inline float y(void)const{return m[1];}

	/*
	 *
	 */
	inline float width(void)const{return m[2];}

	/*
	 *
	 */
	inline float height(void)const{return m[3];}


	inline float bottom(void)const{return this->y() + this->height();}
	inline float center(void)const;
	inline float left(void)const;
	inline float location(void)const;
	inline float right(void)const{return this->x() + this->width();}
	inline float top(void)const;


	/**
	 *
	 */
	inline float operator[](int i)const {return this->m[i];}
	inline float& operator[](int i){return this->m[i];}
	

	friend std::istream &operator>>(std::istream &is, VDRect& t);
	friend std::ostream &operator<<(std::ostream &os, const VDRect& t);
	
	/*
	 *	determine if rectangle is intersecting.
	 */
	int intersect(const VDRect& rect)const;

	/*
	 *
	 */
	int contains(const VDRect& rect)const;
	int contains(const VDPoint& rect)const;

	/*
	 *
	 */
	void inflate(float hor, float ver);

	/*
	 *
	 */
	void offset(float x, float y);

	//Rect union(const Rect& rect1, const Rect& rect2);


	friend VDRect operator+(const VDRect& rec1, const VDRect& rec2);
	friend VDRect operator-(const VDRect& rec1, const VDRect& rec2);
	friend VDRect operator*(const VDRect& rec1, const VDRect& rec2);
	friend VDRect operator/(const VDRect& rect1, const VDRect& rect2);


	VDRect& operator=(const VDRect& v2);

	friend bool operator==(const VDRect& r1, const VDRect& r2);
	friend bool operator!=(const VDRect& r1, const VDRect& r2);

//private:
	/*
	 *	m[0] x position
	 *	m[1] y position
	 *	m[2] width
	 *	m[3] height
	 */
	union{
		float m[4];
		float n[4];
	};
};

inline VDRect::VDRect(void){

}

inline VDRect::VDRect(float x, float y, float width, float height){
	setX(x);
	setY(y);
	setWidth(width);
	setHeight(height);

}

inline VDRect::VDRect(const VDRect& rect){
	*this = rect;
}


inline int VDRect::intersect(const VDRect& rect)const{
	return((rect.x() > this->x() || rect.x() < this->x() + this->width() ) &&
	   (rect.y() < this->y() || rect.y() > this->y() - this->height() ));
}

inline int VDRect::contains(const VDRect& rect)const{
	return (rect.x() > this->x() && rect.y() < this->y()
		&& rect.width() < this->width() && rect.height() < this->height());

}

inline void VDRect::inflate(float width, float height){
	m[2] += width;
	m[3] += height;
}

inline void VDRect::offset(float x, float y){
	m[0] += x;
	m[1] += y;
}



inline VDRect& VDRect::operator=(const VDRect& v2){
	this->m[0] = v2.m[0];
	this->m[1] = v2.m[1];
	this->m[2] = v2.m[2];
	this->m[3] = v2.m[3];
	return *this;
}

/*
bool Rect::operator==(Rect* rh)const{
	return (this == rh);
}
bool Rect::operator!=(Rect* rh)const{
	return (this != rh);
}*/

#endif
