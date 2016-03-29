#pragma once

/*
ArrayList is a simple implementation of a list using an array in c++.
All functions behave the same as the Java equivalent.

Oracles official API was used as a reference for what functionality had to be implemented:
https://docs.oracle.com/javase/7/docs/api/java/util/ArrayList.html

Some new features have been added such as sorting and operators.
An iterator has not yet been implemented.

As long as valid arguments are passed (index in range); excpected funtionallity is guaranteed.
*/

#include <string>
#include <vector>

template <typename T> class ArrayList{

private:

	static const size_t initialCapacity = 10;

	T** data = nullptr;

	size_t size_;
	size_t index;

	void dealloc(){
		if(data != nullptr){
			for(size_t i = 0; i < index; i++){
				delete data[i];
			}

			delete[] data;

			data = nullptr;
		}
		index = 0;
	}

	void alloc(const size_t& size){
		size_t newSize = size > 0 ? size : initialCapacity;

		T** ndata = new T*[newSize];

		for(size_t i = 0; i < newSize && i < index; i++){
			ndata[i] = data[i];
		}

		delete[] data;

		size_ = newSize;
		data = ndata;
	}

public:

	static const size_t npos = SIZE_MAX;

	ArrayList(const size_t& initialCapacity = ArrayList::initialCapacity){
		clear(initialCapacity);
	}

	ArrayList(const ArrayList<T>& list){
		dealloc();

		*this = list;
	}

	ArrayList(const std::vector<T>& vector){
		dealloc();

		*this = vector;
	}

	~ArrayList(){
		dealloc();
	}

	bool operator ==(const ArrayList<T>& list) const{
		if(index != list.index){
			return false;
		}

		for(size_t i = 0; i < index; i++){
			if(get(i) != list.get(i)){
				return false;
			}
		}

		return true;
	}

	bool operator !=(const ArrayList<T>& list) const{
		return !(*this == list);
	}

	T& operator [](const size_t& index) const{
		return get(index);
	}

	ArrayList<T>& operator =(const ArrayList<T>& list){
		dealloc();
		index = list.index;
		size_ = list.size_;
		data = new T*[size_];

		for(size_t i = 0; i < index; i++){
			data[i] = new T(*list.data[i]);
		}

		return *this;
	}

	ArrayList<T>& operator =(const std::vector<T>& vector){
		dealloc();
		size_ = index = vector.size();
		data = new T*[size_];

		for(size_t i = 0; i < index; i++){
			data[i] = new T(vector[i]);
		}

		return *this;
	}

	ArrayList<T>& operator +=(const ArrayList<T>& elements){
		addAll(elements);

		return *this;
	}

	ArrayList<T>& operator +=(const T& element){
		add(element);

		return *this;
	}

	ArrayList<T> operator +(const ArrayList<T>& elements) const{
		ArrayList<T> list = *this;

		list.addAll(elements);

		return list;
	}

	ArrayList<T> operator +(const T& element)  const{
		ArrayList<T> list = *this;

		list.add(element);

		return list;
	}

	ArrayList<T>& operator -=(const ArrayList<T>& elements){
		removeElements(elements);

		return *this;
	}

	ArrayList<T>& operator -=(const T& element){
		removeElement(element);

		return *this;
	}

	ArrayList<T> operator -(const ArrayList<T>& elements) const{
		ArrayList<T> list = *this;

		list.removeElements(elements);

		return list;
	}

	ArrayList<T> operator -(const T& element) const{
		ArrayList<T> list = *this;

		list.removeElement(element);

		return list;
	}

	// Get the current capacity. Will increase when needed.
	size_t capacity() const{
		return size_;
	}

	// Trims the capacity of this ArrayList instance to be the list's current size.
	ArrayList<T>& trimToSize(){
		alloc(index);

		return *this;
	}

	// Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
	ArrayList<T>& ensureCapacity(const size_t& minCapacity){
		if(size_ < minCapacity){
			alloc(minCapacity);
		}

		return *this;
	}

	// Returns a copy of this list.
	ArrayList<T> clone() const{
		ArrayList<T> list;

		for(size_t i = 0; i < index; i++){
			list.add(*data[i]);
		}

		return list;
	}

	// Returns the number of elements in this list.
	size_t size() const{
		return index;
	}

	// Returns true if this list contains no elements.
	bool isEmpty() const{
		return index == 0;
	}

	// Returns the element at the specified position in this list.
	T& get(const size_t& index) const{
		return *data[index];
	}

	// Swaps the elements at the specified positions in this list.
	ArrayList<T>& swap(const size_t& index0, const size_t& index1){
		if(index0 < index && index1 < index){
			T* tmp = data[index0];

			data[index0] = data[index1];
			data[index1] = tmp;
		}

		return *this;
	}

	// Inserts the specified element at the specified position in this list.
	ArrayList<T>& add(const T& element, const size_t& index = SIZE_MAX){
		T* tmp0 = new T(element);

		for(size_t i = index; i < ArrayList::index; i++){
			T* tmp1 = data[i];

			data[i] = tmp0;
			tmp0 = tmp1;
		}

		if(ArrayList::index >= size_){
			alloc(size_ * 2);
		}

		data[ArrayList::index++] = tmp0;

		return *this;
	}

	// Inserts all of the elements in the specified collection into this list, starting at the specified position.
	ArrayList<T>& addAll(const ArrayList<T>& elements, const size_t& index = SIZE_MAX){
		size_t curIndex = index;

		for(size_t i = 0; i < elements.index; i++){
			add(elements[i], curIndex == SIZE_MAX ? curIndex : curIndex++);
		}

		return *this;
	}

	// Replaces the element at the specified position in this list with the specified element.
	ArrayList<T>& set(const size_t& index, const T& element){
		if(index < ArrayList::index){
			delete data[index];

			data[index] = new T(element);
		}

		return *this;
	}

	// Returns the index of the first occurrence of the specified element in this list, or npos if this list does not contain the element.
	size_t indexOf(const T& element) const{
		for(size_t i = 0; i < index; i++){
			if(*(data[i]) == element){
				return i;
			}
		}

		return npos;
	}

	// Returns true if this list contains the specified element.
	bool contains(const T& element){
		return indexOf(element) != npos;
	}

	// Removes the element at the specified position in this list.
	ArrayList<T>& remove(const size_t& index){
		if(index < ArrayList::index){
			delete data[index];

			for(size_t i = index + 1; i < ArrayList::index; i++){
				data[i - 1] = data[i];
			}

			ArrayList::index--;
		}

		return *this;
	}

	// Removes all occurrences of the specified element from this list, if it is present.
	ArrayList<T>& removeElement(const T& t){
		size_t index;

		while((index = indexOf(t)) != npos){
			remove(index);
		}

		return *this;
	}

	// Removes from this list all of its elements that are contained in the specified collection.
	ArrayList<T>& removeElements(const ArrayList<T>& elements){
		for(size_t i = 0; i < elements.index; i++){
			removeElement(elements[i]);
		}

		return *this;
	}

	// Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
	ArrayList<T>& removeRange(const size_t& fromIndex, const size_t& toIndex){
		size_t diff = toIndex - fromIndex;

		for(size_t i = 0; i < diff; i++){
			remove(fromIndex);
		}

		return *this;
	}

	// Removes all of the elements from this list.
	ArrayList<T>& clear(size_t initialCapacity = ArrayList::initialCapacity){
		dealloc();
		alloc(initialCapacity);

		return *this;
	}

	// Reverse the order of all elements from this list.
	ArrayList<T>& reverse(){
		if(index != 0 && index != 1){
			for(size_t i = 0; i <= (index - 1) / 2; i++){
				swap(i, index - 1 - i);
			}
		}

		return *this;
	}

	// Sort the order of all elements from this list.
	ArrayList<T>& sort(){
		bool swapped = false;

		do{
			swapped = false;
			for(size_t i = 0; i < index - 1; i++){
				T* t0 = data[i];
				T* t1 = data[i + 1];

				if(*t0 > *t1){
					data[i] = t1;
					data[i + 1] = t0;
					swapped = true;
				}
			}
		} while(swapped);

		return *this;
	}

	// Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
	ArrayList<T> subList(const size_t& fromIndex, const size_t& toIndex = SIZE_MAX) const{
		ArrayList<T> list;

		for(size_t i = fromIndex; i < toIndex && i < index; i++){
			list.add(*data[i]);
		}

		return list;
	}

	// Returns a vector containing all of the elements in this list in proper sequence (from first to last element).
	std::vector<T> toVector() const{
		std::vector<T> vector;

		for(size_t i = 0; i < index; i++){
			vector.push_back(get(i));
		}

		return vector;
	}

	// Returns a string representation of the list.
	std::string toString() const{
		std::string s = "{";

		for(size_t i = 0; i < size(); i++){
			if(i != 0){
				s += ", ";
			}
			s += std::to_string((T) *data[i]);
		}

		s += "}";

		return s;
	}

	// Print the prefix along with a string representation of the list.
	const ArrayList<T>& print(const std::string& prefix = "") const{
		printf((prefix + toString() + "\n").data());

		return *this;
	}

};

namespace std{

	std::string to_string(const std::string& string){
		return string;
	}

	template <typename T>
	std::string to_string(const ArrayList<T>& list){
		return list.toString();
	}

	template <typename T>
	std::string to_string(const T* t){
		return "*" + std::to_string(*t);
	}

}
