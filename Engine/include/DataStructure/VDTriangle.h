/**
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
#ifndef _VD_TRIANGLE_H_
#define _VD_TRIANGLE_H_ 1
#include"VDSystem.h"
#include"VDShape.h"


/**
 *
 */
class VDDECLSPEC VDTriangle : public VDShape{
public:
	VDTriangle();
	VDTriangle(const VDTriangle& triangle);
	VDTriangle(const VDTriangle& p1, const VDTriangle& p2, const VDTriangle& p3);

	/**
	 *	Get normal from right hand.
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getNormal()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getEdge0()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getEdge1()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getEdge3()const;


	/**/
	inline void setPos0(const VDVector3& pos){
		p0 = pos;
	}

	/**/
	inline void setPos1(const VDVector3& pos){
		p1 = pos;
	}

	/**/
	inline void setPos2(const VDVector3& pos){
		p2 = pos;
	}

private:	/*	Attributes.	*/

	VDVector3 p0;	/**/
	VDVector3 p1;	/**/
	VDVector3 p2;	/**/
};


inline VDTriangle::VDTriangle(){
	p0 = VDVector3::zero();
	p1 = VDVector3::zero();
	p2 = VDVector3::zero();
}

inline VDTriangle::VDTriangle(const VDTriangle& triangle){
	this->setPos0(triangle.p0);
	this->setPos1(triangle.p1);
	this->setPos2(triangle.p2);
}

inline VDTriangle::VDTriangle(const VDTriangle& p1, const VDTriangle& p2, const VDTriangle& p3){
	this->p0 = p1;
	this->p1 = p2;
	this->p2 = p3;
}

inline VDVector3 VDTriangle::getEdge0()const{
	return ( p0 - p1 );
}

inline VDVector3 VDTriangle::getEdge1()const{
	return ( p0 - p2 );
}

inline VDVector3 VDTriangle::getEdge3()const{
	return ( p2 - p1 );
}

inline VDVector3 VDTriangle::getNormal()const{
	return cross(p0 - p1, p0 - p2) / dot(p0 - p1, p0 -p2);
}

#endif
