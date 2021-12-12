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
#ifndef _VD_SMART_REFERENCE_H_
#define _VD_SMART_REFERENCE_H_ 1
#include "../VDDef.h"

/**
 *	Responsible for preventing
 *	data be freed when references
 *	to the block of data still exists.
 */
class VDDECLSPEC VDSmartReference {
  public:
	inline VDSmartReference() {
		this->incre = 1;
		this->pointer = nullptr;
	}

	inline VDSmartReference(const VDSmartReference &references) { *this = references; }

	/**
	 *	Increment number of references.
	 */
	inline void increment() { this->incre += 1; }

	/**
	 *	Deincrement number of references.
	 */
	inline void deincreemnt() { this->incre -= 1; }

	/**
	 *	Set reference pointer.
	 */
	inline void setPointer(void *pointer) { this->pointer = pointer; }

	/**
	 *	Get reference pointer.
	 */
	inline void *getPointer() const { return this->pointer; }

	/**
	 *	Get index count.
	 */
	inline int getIndexCount() const { return this->incre; }

	/**
	 *	Override the index.
	 */
	inline void setIndexCount(unsigned int index) { this->incre = index; }

	/**
	 *	Assign smart reference object.
	 */
	VDSmartReference &operator=(const VDSmartReference &reference) {
		this->setPointer(reference.getPointer());
		this->setIndexCount(this->getIndexCount());
		return *this;
	}

	/**
	 *	Check if equal.
	 */
	bool operator==(const VDSmartReference &reference) { return (this->getPointer() == reference.getPointer()); }

	/**
	 *	Check if not equal.
	 */
	bool operator!=(const VDSmartReference &reference) { return (this->getPointer() != reference.getPointer()); }

  private:		   /*	Attributes.	*/
	int incre;	   /*	Number of references to the pointer.	*/
	void *pointer; /*	*/
};

#endif
