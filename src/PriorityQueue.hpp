#include <vector>
#include <iostream>

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

template<class T>
class MinHeap {
	public:
		MinHeap(int max_size);
		void insert(T datum, int priority);
		void print();
		~MinHeap();
	private:
		Node<T> *data;
		int size;
		int max_size;
		int parent(int index);
		int child(int index);
		void heapify(int index);
};

template<class T>
MinHeap<T>::MinHeap(int max_size) {
	this->size = 0;
	this->max_size = max_size;
	this->data = new Node<T>[max_size];
}

template<class T>
MinHeap<T>::~MinHeap() {
	delete [] this->data;
}

template<class T>
int MinHeap<T>::parent(int index) {
	return (index - 1) / 2;
}

template<class T>
int MinHeap<T>::child(int index) {
	return 2 * index + 1;
}

template<class T>
void MinHeap<T>::heapify(int index) {
	if (index == 0) {
		return;
	}
	int parent_index = this->parent(index);
	if (this->data[index] <= this->data[parent_index]) {
		auto tmp = this->data[parent_index];
		this->data[parent_index] = this->data[index];
		this->data[index] = tmp;
		heapify(parent_index);
	}
}

template<class T>
void MinHeap<T>::insert(T datum, int priority) {
	Node<T> new_node = Node<T>(datum, priority);
	this->data[size] = new_node;
	size++;
	heapify(size - 1);
}

template<class T>
void MinHeap<T>::print() {
	for (int i = 0; i < this->size; i++) {
		std::cout << this->data[i].get_priority() << " ";
	}
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

