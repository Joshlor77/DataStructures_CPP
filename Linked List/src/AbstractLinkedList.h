/*
 * Abstract class for LinkedList
 *
 */

#ifndef SRC_ABSTRACTLINKEDLIST_H_
#define SRC_ABSTRACTLINKEDLIST_H_

template <class DT>
class AbstractLinkedList {
protected:
	virtual DT& pop() = 0;
	virtual DT& remove(int index) = 0;
	virtual void push(DT data) = 0;
	virtual void insert(DT data, int index) = 0;
	virtual int find(DT data) = 0;
	virtual int size() = 0;
	virtual DT& get(int index) = 0;
	virtual ~AbstractLinkedList() {};
};



#endif /* SRC_ABSTRACTLINKEDLIST_H_ */
