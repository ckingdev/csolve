template<class T>
class Node {
	public:
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
