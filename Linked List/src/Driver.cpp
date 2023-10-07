/*
 * Driver class to test LinkedList
 *
 */

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

template <class DT>
ostream& operator<< (ostream& os, LinkedList<DT> list){

	os << "{";

	int listSize = list.size();

	for (int i = 0; i < listSize - 1; i++){
		os << list.get(i) << ", ";
	}

	os << list.get(listSize - 1) << "}";

	return os;
}

int main () {

	int total = 6;

	LinkedList<LinkedList<int>> list = LinkedList<LinkedList<int>>();

	for (int i = 0; i < total; i++){
		list.pushback(LinkedList<int>(i));
	}

	for (int i = 0; i < list.size(); i++){
		for (int j = list.get(i).get(0) + 1; j < total; j++){
			list.get(i).pushback(j);
		}
	}

	cout << "LinkedList: " << list << endl;

	LinkedList<int> list2;
	list2.pushback(0);
	int* list2_0 = &(list2.get(0));
	cout << list2 << endl;
	*list2_0 = 2;
	cout << list2 << endl;

	return 0;
}

