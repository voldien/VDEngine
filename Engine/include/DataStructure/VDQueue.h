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
#ifndef _VD_QUEUE_H_
#define _VD_QUEUE_H_ 1
#include"VDSystem.h"
#include"VDIterator.h"

/**
 *
 */
template<class T, int U = 0>
class VDDECLSPEC VDQueue{
public:

	class Iterator : public VDIterator<T>{
	public:
		Iterator& operator++(){
			pointer++;
			pointer = it->mdata + (pointer - it->mdata) % it->getReserved();
			return *this;
		}

		Iterator& operator++(int){
			this->pointer++;
			this->pointer = it->mdata + (pointer - it->mdata) % it->getReserved();
			return *this;
		}

		Iterator& operator--(){
			pointer--;
			pointer = it->mdata + (pointer - it->mdata) % it->getReserved();
			return *this;
		}

		T& operator->()const{
			return *this->pointer;
		}

		T& operator*()const{
			return *this->pointer;
		}

		bool operator==(const Iterator& it){
			return this->pointer == it.pointer;
		}

		bool operator!=(const Iterator& it){
			return this->pointer != it.pointer;
		}


		T* pointer;

		VDQueue<T>* it;
	};


	VDQueue(){
		this->mback = nullptr;
		this->mfront = nullptr;
		this->mdata = nullptr;
		this->reserved = 0;
	}

	VDQueue(unsigned int nrOfElements){
		this->mback = nullptr;
		this->mfront = nullptr;
		this->mdata = nullptr;
		this->reserved = 0;
		this->resize(nrOfElements);
	}

	VDQueue(const VDQueue& queue){
		*this = queue;
	}
	
	~VDQueue(){
		free(this->mdata);
	}

	/**
	 *	get front without changing the queue.
	 */
	T& front()const{
		return *this->mfront;
	}

	/**
	 *	get front without changing the queue.
	 */
	T& back()const{
		return *this->mback;
	}


	/**
	 *	@Return
	 */
	T& dequeue(){
		this->mfront = this->mdata + (this->mfront - this->mdata) % this->getReserved();	/*solution for x mod nrOfElements*/
		this->mfront++;
		return *(this->mfront -1);
	}

	/**
	 *	Add element at the end of the
	 *	queue.
	 */
	T& enqueue(const T& item){
		this->mback = this->mdata + ( (this->mback - this->mdata) % this->getReserved() );
		memcpy(this->mback, &item, sizeof(T));
		this->mback++;
		return *(this->mback - 1);
	}

	T& push_front(const T& item){

	}

	/**
	 *	Clear the queue.
	 */
	inline void clear(){
		this->mfront = this->mdata;
		this->mback = this->mdata;
	}

	/**
	 *	@Return true if queue is empty.
	 */
	inline bool isEmpty()const{
		return (this->mfront == this->mback);
	}

	/**
	 *	@Return true if queue is full.
	 */
	bool isFull()const{
		return (this->front() - this->back()) == -(sizeof(T)) ? true : false;
	}

	/**
	 *	Resize queue.
	 */
	void resize(unsigned int size){
		if(!this->mdata){
			this->mdata = this->mfront = this->mback = (T*)malloc(sizeof(T) * size);
			memset(this->mdata, 0, sizeof(T) * size);
		}
		else{
			this->mdata = (T*)realloc(this->mdata, this->getTypeSize() * size);
		}
		this->reserved = size;
	}

	/**
	 *	@Return get begin iterator.
	 */
	Iterator begin()const{
		Iterator it;
		it.pointer = this->mfront;
		it.it = (VDQueue<T>*)this;
		return it;
	}

	/**
	 *	@Return get end iterator.
	 */
	Iterator end()const{
		Iterator it;
		it.pointer = this->mback;
		it.it = (VDQueue<T>*)this;
		return it;
	}


	/**
	 *	@Return
	 */
	int getSize()const{
		return (mback - mfront);
	}

	/**
	 *	@Return number of elements reserved.
	 */
	inline unsigned int getReserved()const{
		return this->reserved;
	}

	/**
	 *	Get size of each element.
	 */
	int getTypeSize()const{
		return sizeof(T);
	}

	VDQueue& operator=(const VDQueue& que){
		this->mdata = (T*)malloc(que.getReserved());
		this->resize(que.getReserved());
		Iterator it = que.begin();
		Iterator tit = begin();
		while(it != que.end()){
			(*tit)++ = (*it)++;
		}
		this->reserved = que.getReserved();
		return *this;
	}

private:	/*	Private attributes.	*/

	unsigned int reserved;	/*	Number of reserved queue nodes allocated.	*/
	T* mdata;				/*	Queue pool.	*/
	T* mfront;				/*	Points to front of the queue.	*/
	T* mback;				/*	Points to the end of the queue.	*/
};


#endif
