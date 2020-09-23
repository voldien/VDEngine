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
#ifndef _VD_ITERATOR_H_
#define _VD_ITERATOR_H_ 1
#include"../VDDef.h"


/**
 *	Simple Iterator class for
 *	generic classes.
 */
template<class T>
class VDDECLSPEC VDIterator{
public:

	/**
	 *	@Return
	 */
	VDIterator& operator++(void);

	/**
	 *	@Return
	 */
	VDIterator& operator++(int);


	/**
	 *	@Return
	 */
	VDIterator& operator--(void);


	/**
	 *	@Return
	 */
	VDIterator& operator+=(int n);

	/**
	 *	@Return
	 */
	VDIterator& operator-=(int n);


	/**
	 *	@Return
	 */
	VDIterator& operator+(int n);

	/**
	 *	@Return
	 */
	VDIterator& operator-(int n);


	/**
	 *	@Return
	 */
	VDIterator& operator[](int index)const;

	/**
	 *	@Return
	 */
	T& operator->(void)const{
		return (T)*this->iterator;
	}

	/**
	 *	@Return
	 */
	T& operator*(void)const{
		return *this->iterator;
	}

	/**
	 *	@Return
	 */
	T& operator*(void){
		return *this->iterator;
	}


	/**
	 *	@Return
	 */
	inline bool operator==(const VDIterator& iterator){
		return this->iterator == iterator.iterator;
	}

	/**
	 *	@Return
	 */
	inline bool operator!=(const VDIterator& iterator){
		return this->iterator != iterator.iterator;
	}

	/**
	 *	@Return
	 */
	VDIterator& operator=(const VDIterator& iterator){
		this->iterator = iterator.iterator;
		return *this;
	}

public:	/*	Protected attributes.	*/

	T* iterator;	/**/

};

#endif
