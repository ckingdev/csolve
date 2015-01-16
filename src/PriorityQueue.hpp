#include <vector>
#include <iostream>
#include <cmath>

template<class T>
class Node {
	public:
		Node();
		Node(T datum, int priority);
		const T &get_datum();
		int get_priority();
		void set_priority(int new_p);
		bool operator <=(Node<T> &other);
		bool operator >=(Node<T> &other);
	private:
		T datum;
		int priority;
};

template<class T, int d>
class MinHeap {
	public:
		MinHeap(int max_size);
		void insert(T datum, int priority);
		T pop();
		void print();
		bool is_empty();
		~MinHeap();
	private:
		Node<T> *data;
		int size;
		int max_size;
		int parent(int index);
		int first_child(int index);
		void heap_up(int index);
		void heap_down(int index);
};

template<class T, int d>
MinHeap<T, d>::MinHeap(int max_size) {
	this->size = 0;
	this->max_size = max_size;
	this->data = new Node<T>[max_size];
}

template<class T, int d>
MinHeap<T, d>::~MinHeap() {
	delete [] this->data;
}

template<class T, int d>
int MinHeap<T, d>::parent(int index) {
	double tmp = index;
	tmp -= 1;
	tmp /= d;
	return int(tmp);
}

template<class T, int d>
int MinHeap<T, d>::first_child(int index) {
	return index * d + 1;
}

template<class T, int d>
void MinHeap<T, d>::heap_up(int index) {
	if (index == 0) {
		return;
	}
	int parent_index = this->parent(index);
	if (this->data[index] <= this->data[parent_index]) {
		auto tmp = this->data[parent_index];
		this->data[parent_index] = this->data[index];
		this->data[index] = tmp;
		heap_up(parent_index);
	}
}

template<class T, int d>
void MinHeap<T, d>::insert(T datum, int priority) {
	assert(this->size < this->max_size);
	Node<T> new_node = Node<T>(datum, priority);
	this->data[this->size] = new_node;
	size++;
	heap_up(size - 1);
}

template<class T, int d>
void MinHeap<T, d>::print() {
	for (int i = 0; i < this->size; i++) {
		std::cout << this->data[i].get_priority() << " ";
	}
	std::cout << std::endl;
}

template<class T, int d>
void MinHeap<T, d>::heap_down(int index) {
	int fc = this->first_child(index);
	if (fc >= this->size) { // No children
		return;
	}
	int min_index = fc;
	int min_pri = this->data[fc].get_priority();
	for (int i = 1; i < d; i++) {
		if (fc+i >= this->size) {
			break;
		}
		int iter_pri = this->data[fc+i].get_priority();
		if (iter_pri < min_pri) {
			min_pri = iter_pri;
			min_index = fc + i;
		}
	}
	if (this->data[index].get_priority() > min_pri) {
		auto swap = this->data[index];
		this->data[index] = this->data[min_index];
		this->data[min_index] = swap;
		heap_down(min_index);
	}
}

template<class T, int d>
T MinHeap<T, d>::pop() {
	assert(this->size > 0);
	T root_datum = this->data[0].get_datum();
	this->size--;
	this->data[0] = this->data[this->size];
	heap_down(0);
	return root_datum;
}

template<class T, int d>
bool MinHeap<T, d>::is_empty() {
	if (size > 0) {
		return false;
	}
	return true;
}

template<class T>
Node<T>::Node() {}

template<class T>
Node<T>::Node(T datum, int priority) {
	this->datum = datum;
	this->priority = priority;
}

template<class T>
const T &Node<T>::get_datum() {
	return this->datum;
}

template<class T>
int Node<T>::get_priority() {
	return this->priority;
}

template<class T>
void Node<T>::set_priority(int new_p) {
	this->priority = new_p;
}

template<class T>
bool Node<T>::operator <=(Node<T> &other) {
	if (this->priority <= other.get_priority()) {
		return true;
	}
	return false;
}

template<class T>
bool Node<T>::operator >=(Node<T> &other) {
	if (this->priority >= other.get_priority()) {
		return true;
	}
	return false;
}