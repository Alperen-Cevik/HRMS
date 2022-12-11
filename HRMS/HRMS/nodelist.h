#pragma once
#include <cstddef> // for NULL

template <typename T>
struct node_t {
	T data; // TODO: consider making this a ptr to avoid copying
	node_t* prev = NULL, * next = NULL;
};

template <typename T>
class NodeList
{
	using node = node_t<T>; 

public:
	NodeList() : _first(NULL), _last(NULL), _size(0) {
		// ctor.
	}

	~NodeList() {
		clear();
	}

	T& get(const size_t index) {
		if (index >= _size)
			throw "out of range";

		return node_at(index)->data;
	}

	node* node_at(size_t index) {
		if (index >= _size)
			throw "out of range";

		node* node = 0;

		if (index == 0)
			node = _first;
		else if (index + 1 == _size)
			node = _last;
		else {
			node = _first->next;
			while (--index)
				node = node->next;
		}

		return node;
	}

	void push(const T& elem) {
		node* node = new node_t<T>;
		node->data = elem;

		if (_first == NULL) {
			_first = node;
			_last = node;
		}
		else {
			node->prev = _last;
			_last->next = node;
			_last = node;
		}

		_size++;
	}

	void remove(const size_t index) {
		if (index >= _size)
			throw "out of range";

		node* node = node_at(index);
		
		if (_size-- == 1) {
			_first = NULL;
			_last = NULL;
			
			delete node;
			
			return;
		}

		if (node == _first) {
			_first = _first->next;
			_first->prev = NULL;
		}
		else if (node == _last) {
			_last = _last->prev;
			_last->next = NULL;
		}
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}

		delete node;
	}

	void clear() {
		_size = 0;
		// TODO: destroy elems
	}

	const size_t size() {
		return _size;
	}

	bool empty() {
		return !_size;
	}

	node* first() {
		return _first;
	};

	node* last() {
		return _last;
	}

	T& operator [](const size_t index) {
		return get(index);
	}

private:
	node* _first = NULL;
	node* _last = NULL;

	size_t _size = 0;
};
