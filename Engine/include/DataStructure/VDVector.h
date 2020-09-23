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
#ifndef _VD_VECTOR_H_
#define _VD_VECTOR_H_ 1
#include"../VDSystem.h"
#include"VDIterator.h"

/**
 *	Vector.
 */
template<class T>
class VDDECLSPEC VDVector{
public:

	/**
	 *
	 */
	class Iterator : public VDIterator<T>{
		public:

		/*
		 *
		 */
		Iterator& operator++(void){
			this->iterator++;
			return *this;
		}

		Iterator& operator++(int){
			this->iterator++;
			return *this;
		}


		/*
		 *
		 */
		Iterator& operator--(void){
			this->iterator--;
			return *this;
		}


		/*
		 *
		 */
		Iterator& operator+(int n){
			this->iterator += n;
			return *this;
		}

		/*
		 *
		 */
		Iterator& operator-(int n){
			this->iterator += n;
			return *this;
		}

		/**/
		T* operator->(void){
			return this->iterator;
		}

	};

	VDVector(void){
		this->data = NULL;
		this->capacity = 0;
		this->nrOfElements = 0;
	}

	VDVector(const VDVector& vector){
		this->data = NULL;
		this->capacity = 0;
		this->nrOfElements = 0;
		*this = vector;
	}

	VDVector(int numElements){
		this->data = NULL;
		this->capacity = 0;
		this->nrOfElements = 0;
		this->resize(numElements);
	}

	~VDVector(void){
		delete[] this->data;
	}

	/**
	 *	@Return
	 */
	inline bool isValid(void)const{
		return this->data != NULL;
	}

	/**
	 *	@Return
	 */
	inline bool isValid(const T* object)const{
		if(isValid()){
			return (object - (T*)*this->data) < this->nrOfElements;
		}
		else{
			return false;
		}
	}

	/**
	 *
	 */
	void remove(int index){
		if(this->nrOfElements <= 1){
			this->nrOfElements--;
			return;
		}
		memcpy(this->data[index], this->data[nrOfElements - 1], sizeof(T));
		this->nrOfElements--;
	}

	/**
	 *	@Return
	 */
	T& push(const T& p){
		T* tmp;
		if(this->nrOfElements < this->capacity)
			memcpy((void*)&this->data[this->nrOfElements++],&p,sizeof(T));
		else{
			resize(this->nrOfElements +1);
			tmp = &push(p);
			return *tmp;
		}	
		tmp = &this->data[nrOfElements];
		return *tmp;
	}

	/**
	 *	@Return
	 */
	inline T& push_back(const T& p){
		return push(p);
	}

	/**/
	inline T& push_front(const T& p){
		insert(this->begin(), p);
		return this->data[0];
	}

	/**
	 *
	 */
	inline void pop(void){
		this->nrOfElements--;
	}

	/**
	 *
	 */
	void erase(const T& t){
		Iterator it;
		this->erase(it);
	}

	/*
	 *
	 */
	void erase(const Iterator& iterator){
		memset(iterator.iterator, 0, sizeof(T));
	}


	/**
	 *
	 */
	void merge(const VDVector<T>& vector){
		unsigned int x = 0;
		for(; x < vector.size(); x++){
			this->push(vector[x]);
		}
	}

	/**
	 *
	 */
	void insert(const Iterator& it, const T v){
		if(this->nrOfElements < this->capacity){
			Iterator des = this->end() + 1;
			memmove(des.iterator, it.iterator, sizeof(T) * (des.iterator - it.iterator));
			memcpy(des.iterator, &v, sizeof(T));
			this->nrOfElements++;
		}
		else{
			this->resize(this->nrOfElements + 1);
			this->insert(it, v);
		}
	}

	void insert(const Iterator& iterator){

	}

	void swapElement(const Iterator& swp1, const Iterator& swp2){
		Iterator tmp = *swp1;
		*swp1 = swp2;
		*swp2 = tmp;
	}

	/**
	 *
	 */
	void resize(unsigned int size){
		this->data = (T*)realloc(this->data, sizeof(T) * size);
		this->capacity = size;
	}

	/**
	 *
	 */
	void reserve(unsigned int size){
		this->resize(this->size() + size);
	}

	/**
	 *
	 */
	inline void clear(void){
		this->nrOfElements = 0;
	}

	/**
	 *
	 */
	inline T& operator[](int i){return data[i];}
	inline T operator[](int i)const{return data[i];}	/*	TODO check if its neccessary.	*/

	/**
	 *
	 */
	VDVector& operator=(const VDVector& vector){
		this->resize(vector.getCapacity());
		
		memcpy(this->data, vector.getData(), vector.getDataTypeSize() * vector.size());

		return *this;
	}

	/**
	 *	@Return
	 */
	inline Iterator begin(void)const{
		Iterator it;
		it.iterator = this->data;
		return it;
	}

	/**
	 *
	 *	@Return
	 */
	inline Iterator end(void)const{
		Iterator it;
		it.iterator = &this->data[this->nrOfElements];
		return it;
	}


	inline int getDataTypeSize(void)const{
		return sizeof(T);
	}

	inline int size(void)const{
		return this->nrOfElements;
	}

	inline int getCapacity(void)const{
		return this->capacity;
	}

	inline T* getData(void)const{
		return this->data;
	}

private:	/*	Attributes.	*/

	T* data;					/*	*/
	unsigned int capacity;		/*	*/
	unsigned int nrOfElements;	/*	*/
};

#endif
