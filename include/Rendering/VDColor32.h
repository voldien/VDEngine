/**
 *
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
#ifndef _VD_COLOR_32_H_
#define _VD_COLOR_32_H_ 1
#include "../VDDef.h"
#include <iostream>

/**
 *
 */
class VDDECLSPEC VDColor32{
public:
	inline VDColor32(void){}
	VDColor32(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
	VDColor32(unsigned int c);
	VDColor32(const VDColor32& color){*this = color;}

	/**
	 *
	 */
	inline unsigned char operator[](int i)const {return m[i];}
	inline unsigned char& operator[](int i){return m[i];}

	/**
	 *
	 */
	inline unsigned char r(void)const{return m[0];}
	inline unsigned char g(void)const{return m[1];}
	inline unsigned char b(void)const{return m[2];}
	inline unsigned char a(void)const{return m[3];}

	/**
	 *
	 */
	unsigned int getColor(void)const;
	unsigned int HexRGB(void)const;
	unsigned int HexRGBA(void)const;
	unsigned int HexBGR(void)const;
	unsigned int HexBGRA(void)const;
	void setColor(unsigned int hexa);

	/**
	 *
	 */
	void setR(unsigned char red){m[0] = red;}
	void setG(unsigned char green){m[1] = green;}
	void setB(unsigned char blue){m[2] = blue;}
	void setA(unsigned char alpha){m[3] = alpha;}

	/**
	 *
	 */
	VDColor32 grayScale(void)const;

	/**
	 *
	 */
	bool isEqualColor(const VDColor32& Color)const;			//  is RGBA Equal.
	bool isEqualColorOnly(const VDColor32& Color)const;		//	is RGB Equal.
	bool isBlack(void)const;								//	is RGB == 0
	bool isTransparent(void)const;							//	is A Channel == 0

	/**/
	friend bool operator==(const VDColor32& v1, const VDColor32& v2);
	friend bool operator!= (const VDColor32& v1, const VDColor32& v2);

	/**/
	friend std::istream &operator>>(std::istream &is, VDColor32& t);
	friend std::ostream &operator<<(std::ostream &os, const VDColor32& t);

	/**/
	friend VDColor32 operator+(const VDColor32& v1, const VDColor32& v2);
	friend VDColor32 operator-(const VDColor32& v1, const VDColor32& v2);
	friend VDColor32 operator/(const VDColor32& vec, float scalar);
	friend VDColor32 operator*(const VDColor32& vec, float scalar);
	friend VDColor32 operator*(float scalar,const VDColor32& vec);

	/**/
	VDColor32& operator=(const VDColor32& v2);
	VDColor32& operator+=(const VDColor32& v2);
	VDColor32& operator-=(const VDColor32& v2);
	VDColor32& operator/=(float scalar);
	VDColor32& operator/=(const VDColor32& rh);
	VDColor32& operator*=(float scalar);

private:	/*	Attributes.	*/

	union{
		unsigned int u;
		unsigned char m[4];
	};


public:	/* Copy Right XNA	*/
    static inline VDColor32 Black(void){return  VDColor32(4278190080U);}
    static inline VDColor32 Gray(void) {return  VDColor32(4286611584);}
    static inline VDColor32 Pink(void){return  VDColor32(4291543295);}
    static inline VDColor32 Red(void){return  VDColor32(4278190335);}
    static inline VDColor32 White(void){return  VDColor32(0xffffffff);}


};


inline VDColor32::VDColor32(unsigned char r,unsigned char g,unsigned char b,unsigned char a){
	this->setR( r );
	this->setG( g );
	this->setB( b );
	this->setA( a );

}
inline VDColor32::VDColor32(unsigned int hex){
	this->setA( (hex >> 24) & 0xff );
	this->setB( (hex >> 16) & 0xff );
	this->setG( (hex >> 8) & 0xff );
	this->setR( hex & 0xff );
}


inline unsigned int VDColor32::getColor(void)const{
	return this->u;
}


inline VDColor32 operator+(const VDColor32& v1, const VDColor32& v2){
	return VDColor32 (v1.m[0] + v2.m[0],
					v1.m[1] + v2.m[1],
					v1.m[2] + v2.m[2],
					v1.m[3] + v2.m[3]);
}
inline VDColor32 operator-(const VDColor32& v1, const VDColor32& v2){
	return VDColor32 (v1.m[0] - v2.m[0],
					v1.m[1] - v2.m[1],
					v1.m[2] - v2.m[2],
					v1.m[3] - v2.m[3]);
}
inline VDColor32 operator/(const VDColor32& vec, float scalar){
	return VDColor32 (vec.m[0] / scalar,
					vec.m[1] / scalar,
					vec.m[2] / scalar,
					vec.m[3] / scalar);
}
inline VDColor32 operator*(const VDColor32& vec, float scalar){
	return VDColor32 (vec.m[0] * scalar,
					vec.m[1] * scalar,
					vec.m[2] * scalar,
					vec.m[3] * scalar);
}
inline VDColor32 operator*(float scalar,const VDColor32& vec){
	return VDColor32 (vec.m[0] * scalar,
					vec.m[1] * scalar,
					vec.m[2] * scalar,
					vec.m[3] * scalar);
}

inline bool operator==(const VDColor32& v1, const VDColor32& v2){
	return (v1.m[0] == v2.m[0] &&
			 v1.m[1] == v2.m[1] &&
			 v1.m[2] == v2.m[2] &&
			 v1.m[3] == v2.m[3]);

}
inline bool operator!=(const VDColor32& v1, const VDColor32& v2){
	return !(v1.m[0] == v2.m[0] &&
			 v1.m[1] == v2.m[1] &&
			 v1.m[2] == v2.m[2] &&
			 v1.m[3] == v2.m[3]);
}


inline VDColor32& VDColor32::operator=(const VDColor32& v2){
	this->m[0] = v2[0];
	this->m[1] = v2[1];
	this->m[2] = v2[2];
	this->m[3] = v2[3];
	return *this;
}
inline VDColor32& VDColor32::operator+=(const VDColor32& v2){
	this->m[0] +=  v2.m[0];
	this->m[1] +=  v2.m[1];
	this->m[2] +=  v2.m[2];
	this->m[3] +=  v2.m[3];
	return *this;
}
inline VDColor32& VDColor32::operator-=(const VDColor32& v2){
	this->m[0] -=  v2.m[0];
	this->m[1] -=  v2.m[1];
	this->m[2] -=  v2.m[2];
	this->m[3] -=  v2.m[3];
	return *this;
}
inline VDColor32& VDColor32::operator/=(float scalar){
	this->m[0] /=  scalar;
	this->m[1] /=  scalar;
	this->m[2] /=  scalar;
	this->m[3] /=  scalar;
	return *this;
}
inline VDColor32& VDColor32::operator*=(float scalar){
	this->m[0] *=  scalar;
	this->m[1] *=  scalar;
	this->m[2] *=  scalar;
	this->m[3] *=  scalar;
	return *this;
}

inline VDColor32 VDColor32::grayScale(void)const{
	float product = (this->r() * 0.26f) + (this->g() * 0.44f) + (this->b() * 0.14f);
	unsigned char color = (unsigned char)(product * 255);
	return VDColor32(color, color, color, 255);
}

inline bool VDColor32::isEqualColor(const VDColor32& color)const{
	return (this->r() == color.r() && this->g() == color.g() && this->b() == color.b() && this->a() == color.a());
}
inline bool VDColor32::isEqualColorOnly(const VDColor32& color)const{
	return (this->r() == color.r() && this->g() == color.g() && this->b()  == color.b());
}
inline bool VDColor32::isBlack(void)const{
	return (this->r() == 0 && this->g() == 0 && this->b() == 0);
}
inline bool VDColor32::isTransparent(void)const{
	return (this->a() <= 254);
}

#endif
