/*
 * list.hpp
 *
 *  Created on: Apr 7, 2019
 *      Author: bartlomiej
 */

#ifndef LIST_HPP_
#define LIST_HPP_

#include <exception>
#include <iterator>

namespace mtl{

template<typename T>
class List {

public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;

private:
	struct Node {
		T* value;
		Node* next;
		Node(const_reference val ) : value( new T(val)), next(nullptr){};
		~Node(){ delete value; };
	};

	class iterator : public std::iterator<std::forward_iterator_tag, Node> {
		Node* node_;
	public:
		iterator() : node_(nullptr){};
		explicit iterator( Node* node ) : node_(node) {};
		iterator( const iterator& right_iterator ) : node_( right_iterator.node_ ) {};
		iterator& operator= ( const iterator& right_iterator ) { //todo: return const iterator
			node_ = right_iterator.node_;
			return *this;
		};
	};

	Node* head_;
	Node* tail_;
	int size_;
	void add( const_reference value, Node** nodeptr );


public:
	List() : head_(nullptr), tail_( nullptr ), size_(0) {};
	~List();
	int size() const { return size_;}
	void push_back( const_reference value ) { add( value, &tail_ ); };
	void pop_back();
	void push_front( const_reference value ) { add( value, &head_ ); };
	void pop_front();
	const_reference front() const { if( !head_ ) throw std::logic_error( "empty list"); return *(head_->value); };
	reference front() { if( !head_ ) throw std::logic_error( "empty list"); return *(head_->value); };
	const_reference back() const { if( !tail_ ) throw std::logic_error( "empty list"); return *(tail_->value); };
	reference back() { if( !tail_ ) throw std::logic_error( "empty list"); return *(tail_->value); };
};

template<typename T>
void List<T>::add( List<T>::const_reference value, List<T>::Node** nodeptr )
{
	List<T>::Node* new_node = new List<T>::Node( value );
	if( *nodeptr ) {
		new_node->next = head_;
		tail_->next = new_node;
		*nodeptr = new_node;
	} else {
		head_ = new_node;
		tail_ = new_node;
		tail_->next = head_;
	}
	++size_;
}


template<typename T>
List<T>::~List()
{
	if( !head_ )
		return;
	List<T>::Node* tmp = head_;
	tail_->next = nullptr;
	while( tmp ){
		head_ = tmp->next;
		delete tmp;
		tmp = head_;
	}
}

}//end namespace

#endif /* LIST_HPP_ */
