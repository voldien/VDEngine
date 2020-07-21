/**
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
 along with this getProgram().  If not, see <http://www.gnu.org/licenses/>.

 */
#ifndef _VD_POLL_ALLACTOR_H_
#define _VD_POLL_ALLACTOR_H_ 1
#include"../VDSystem.h"

/* add support for C++ allocates in order to remove pure function bug, if it's that it's the culprit*/

/*TODO extract the pool information into a subclass such that the memory consumption can be monitored.*/

/**
 *
 */
template<class T>
class VDPoolAllactor {
public:

	/**
	 *
	 */
	typedef struct poolallactoritem {
		T data;
		poolallactoritem* next;

	} PoolAllactorItem;

public:
	VDPoolAllactor(void) {
		this->item = NULL;
		this->numOfElements = 0;
		this->mReserved = 0;
	}

	VDPoolAllactor(const VDPoolAllactor& pollallactor) {
		*this = pollallactor;
	}

	VDPoolAllactor(unsigned num) {
		this->item = NULL;
		this->numOfElements = 0;
		this->mReserved = 0;
		this->resize(num);
	}

	~VDPoolAllactor(void) {
		if (this->item) {
			delete this->item;
		}
	}

	/**
	 *	Get a pointer to next object in pool allocator.
	 *
	 *	@Return None NULL pointer if successful.
	 */
	T* VDAPIENTRY obtain(void) {
		T* alloc;

		/*	if last resize*/
		if (this->isFull()) {
			this->resize(numOfElements + (1 << 3));
			return this->obtain();
		}

		if (this->numOfElements == 0)
			alloc = &this->item->data;
		else
			alloc = &this->item->next->data; /*changed.*/

		this->item->next = this->item->next->next; /*	TODO still some bugs in pool allactor.	*/
		this->numOfElements++;
		return (T*) alloc;
	}

	/**
	 *
	 */
	void VDAPIENTRY Return(T* element) {
		PoolAllactorItem* alloc = (PoolAllactorItem*) element;
		alloc->next = item->next;
		item->next = alloc;
		this->numOfElements--;
	}

	/**
	 *	Check if the data is in the same address space.
	 *
	 *	@Return true if valid item.
	 */
	bool VDAPIENTRY isValidItem(const T& data) const {
		const T* tmp = &data;
		if ((void*) tmp < (void*) item)
			return false;
		if ((void*) tmp > (item + reserved()))
			return false;

		return true;
	}

	/*
	 bool isValidItem(const T* data){

	 }
	 */

	bool find(const T&) {

	}

	/**
	 *
	 */
	void clean(void) {
		free(this->item);
		this->mReserved = 0;
		this->numOfElements = 0;
	}

	/**
	 *	Return true if allcator is full.
	 */
	bool isFull(void) const {
		return (reserved() - 1) <= this->numOfElements;
	}

	/*	TODO function for obtain.*/
	bool needs(void) const {
		return true;
	}

	/**
	 *
	 *	@Return
	 */
	inline int size(void) const {
		return this->numOfElements;
	}

	/**/
	inline int reserved(void) const {
		return this->mReserved;
	}

	/**
	 *
	 */
	/*	TODO Fix, still some bugs!	*/
	void resize(unsigned int size) {
		PoolAllactorItem* tmp;
		int i;
		int delta = size - this->reserved();
		if (delta == 0) {
			return;
		}

		i = this->item != NULL ? this->reserved() + 1 : 0;
		this->item = (PoolAllactorItem*) realloc(this->item,
		        sizeof(PoolAllactorItem) * size);
		memset(&this->item[this->numOfElements], 0,
		        sizeof(PoolAllactorItem) * (size - this->numOfElements));

		tmp = this->item;
		for (i = 1; i < delta; i++) {
			tmp->next = (PoolAllactorItem*) item + i; // * sizeof(PoolAllactorItem) );
			tmp = tmp->next;
		}
		tmp->next = NULL;

		/*
		 else{
		 PoolAllactorItem* eof = (PoolAllactorItem*)item;
		 while(!eof){
		 eof = eof->next;
		 }
		 item = realloc(item,sizeof(PoolAllactorItem)  * size);
		 if(!item){

		 }

		 memset(eof + sizeof(PoolAllactorItem), 0, delta * sizeof(PoolAllactorItem) );

		 tmp = (PoolAllactorItem*)eof;
		 for(i = reserved(); i < delta; i++){
		 tmp->next = (PoolAllactorItem*)this->item + (i * ( (sizeof(T) + sizeof(PoolAllactor*) ) / sizeof(tmp->next) ) );
		 tmp = tmp->next;
		 }
		 }
		 */
		this->mReserved = size;
	}

	/**
	 *
	 *	@Return
	 */
	inline T* getLast(void) {
		return this->item[this->mReserved - 1];
	}

	/**
	 *
	 *	@Return
	 */
	inline T& operator[](int index) {
		return this->item[index].data;
	}

	/**
	 *
	 *	@Return
	 */
	inline T operator[](int index) const {
		return item[index].data;
	}

	/**
	 *
	 *	@Return
	 */
	VDPoolAllactor& operator=(const VDPoolAllactor& allocator) {
		resize(allocator.reserved());

		return *this;
	}

private:	/*	attributes.	*/

	PoolAllactorItem* item;
	int numOfElements;
	int mReserved;

};

#endif
