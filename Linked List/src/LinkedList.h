/*
 * Singly LinkedList with pointer implementation
 *
 */

#include "AbstractLinkedList.h"
#include "LinkedListException.h"

using namespace std;

#ifndef SRC_LINKEDLIST_H_
#define SRC_LINKEDLIST_H_

template <class DT>
class LinkedList : AbstractLinkedList<DT> {
private:
	DT _info;
	LinkedList<DT>* _next;
public:
	LinkedList();
	LinkedList(DT data);
	LinkedList(const LinkedList<DT>& list);
	~LinkedList();
	DT& pop();
	DT& popfront();
	DT& popback();
	DT& remove(int index);
	void push (DT data);
	void pushfront(DT data);
	void pushback(DT data);
	void insert(DT data, int index);
	int find(DT data);
	int size();
	DT& get(int index);
	bool operator== (LinkedList<DT> a);
	bool operator!= (LinkedList<DT> a);
	void sort();
	LinkedList<DT>& operator= (LinkedList<DT> a);
};

/*
 * Constructors
 */

//Default Constructor
template <class DT>
LinkedList<DT>::LinkedList(){
	_next = nullptr;
}

//Non-Default Constructor
template <class DT>
LinkedList<DT>::LinkedList(DT data){
	_info = data;
	_next = new LinkedList<DT>();
}

//Copy Constructor
template <class DT>
LinkedList<DT>::LinkedList (const LinkedList<DT>& list){
	if (list._next == nullptr){
		_next = nullptr;
	} else {
		_info = list._info;
		_next = new LinkedList<DT>(*(list._next));
	}
}

template <class DT>
LinkedList<DT>::~LinkedList(){
	if (_next != nullptr){
		_next->~LinkedList();
	}
}

/*
 * Access Functions
 */

/*
 * Deletes the Linked List object that the Linked List object that this function is called on.
 *
 * This is done by storing _next, the LinkedList pointer inside of the LinkedList object this function is called on.
 * Also, a copy of the data stored by the LinkedList object is stored.
 * Then, the data in the LinkedList object is replaced with the data in the LinkedList object _next points to,
 * and the _next for the _next field in the data the LinkedList object being pointed to is used to replace
 * the _next field of the LinkedList object this function is called on.
 * Finally, the LinkedList object which is pointed to by the copied pointer is deleted, then the store copy data is returned
 *
 */

template <class DT>
DT& LinkedList<DT>::pop(){
	try {
		return popfront();
	} catch (LinkedListIsEmptyException& e){
		throw e;
	}
}

template <class DT>
DT& LinkedList<DT>::popfront(){
	if (_next == nullptr){
		throw LinkedListIsEmptyException();
	}

	DT& toReturn = _info;
	LinkedList<DT>* toDelete = _next;

	_info = toDelete->_info;
	_next = toDelete->_next;

	toDelete->_next = nullptr;
	delete toDelete;

	return toReturn;
}

/*
 * The function gets sent through the Linked List until reaching a Linked List that points to an empty Linked List.
 * When the function reaches a Linked List object that points to an empty Linked List, popfront() is called and returned.
 */
template <class DT>
DT& LinkedList<DT>::popback(){
	if (_next == nullptr) {
		throw LinkedListIsEmptyException();
	}

	if (_next->_next != nullptr){
		return _next->popback();
	}

	//If _next->_next == nullptr
	return popfront();

}

/*
 * Allows for removing data in any Linked List in the chain
 *
 * This is done by repeatedly calling this function through the list with index - 1, until index = 0.
 * When index = 0, popfront() is called and returned.
 */
template <class DT>
DT& LinkedList<DT>::remove(int index){
	if (_next == nullptr){
		throw LinkedListIsEmptyException();
	}
	if (index < 0 || index >= size()){
		throw LinkedListOutofBoundsException();
	}
	if (index != 0){
		return _next->remove(index - 1);
	}
	//If index == 0
	return popfront();
}

template <class DT>
void LinkedList<DT>::push(DT data){
	pushfront(data);
}

template <class DT>
void LinkedList<DT>::pushfront(DT data){

	LinkedList<DT>* newList = new LinkedList<DT>();

	newList->_info = _info;
	newList->_next = _next;
	_info = data;
	_next = newList;
}

template <class DT>
void LinkedList<DT>::pushback(DT data){
	if (_next == nullptr){
		pushfront(data);
	} else {
		_next->pushback(data);
	}

}

template <class DT>
void LinkedList<DT>::insert(DT data, int index){
	if (index < 0 || index > size()){
		throw LinkedListOutofBoundsException();
	}
	if (index != 0){
		_next->insert(data, index - 1);
		return;
	}
	//If index == 0
	pushfront(data);
}


/*
 * Searches through the list for a piece of data and returns the index of the data if it is found, otherwise returns -1.
 */
template <class DT>
int LinkedList<DT>::find(DT data){
	if (_next == nullptr){
		return -1;
	}
	if (_info != data){
		return _next->find(data) + 1;
	}
	//if _info == data
	return 0;
}

template <class DT>
int LinkedList<DT>::size(){
	if (_next != nullptr){
		return _next->size() + 1;
	}

	return 0;
}

template <class DT>
DT& LinkedList<DT>::get(int index){

	if (index < 0 || index >= size()){
		throw LinkedListOutofBoundsException();
	}

	if (index != 0){
		return _next->get(index - 1);
	}
	//If index == 0
	return _info;
}

// Two Linked Lists are said to be equal if they contain the same elements in the same order
template <class DT>
bool LinkedList<DT>::operator== (LinkedList<DT> a) {

	//If either LinkedList is empty
	if (_next == nullptr || a._next == nullptr){

		//If only one LinkedList is empty
		if ((_next == nullptr) != (a._next == nullptr)){
			return false;
		}
		//If both LinkedLists are empty
		return true;
	}

	//If both lists contain the same data, compare the next list for both lists
	if (_info == a._info){
		return *(_next) == *(a._next);
	}
	//If _info != a._info
	return false;
}

// Two Linked Lists are said to be unequal if they do not contain the same elements in the same order
template <class DT>
bool LinkedList<DT>::operator!= (LinkedList<DT> a) {

	//If either LinkedList is empty
	if (_next == nullptr || a._next == nullptr) {

		//If both LinkedLists are empty
		if ((_next == nullptr) == (a._next == nullptr)){
			return false;
		}
		//If only one LinkedList is empty
		return true;
	}
	//If both lists contain the same data, compare the next list for both lists
	if (_info == a._info){
		return *(_next) != *(a._next);
	}
	//If _info != a._info
	return true;
}

template <class DT>
LinkedList<DT>& LinkedList<DT>::operator= (LinkedList<DT> a) {

	using std::swap;

	swap(_info, a._info);
	swap(_next, a._next);

	return *this;
}

#endif /* SRC_LINKEDLIST_H_ */
