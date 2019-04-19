/*
 * CircularList.hpp
 *
 *  Created on: Apr 7, 2019
 *      Author: bartlomiej
 */

#ifndef _CIRCULAR_LIST_HPP_
#define _CIRCULAR_LIST_HPP_

#include <exception>
#include <iterator>

namespace mtl{

template<typename T>
class CircularList {

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

	Node* head_;
	Node* tail_;
	int size_;
	void add( const_reference value, Node** nodeptr );
	Node* del( Node* node );

public:
	struct iterator : public std::iterator<std::forward_iterator_tag, Node> {
			Node* node_;
			iterator() : node_(nullptr){};
			explicit iterator( Node* node ) : node_(node){};
			iterator( const iterator& right_iterator ) : node_( right_iterator.node_ ) {};
			iterator& operator= ( const iterator& right_iterator ) { //todo: return const iterator
				node_ = right_iterator.node_;
				return *this;
			};
		    iterator& operator++ ()
		    {
		        if( node_ ){
		        	node_ = node_->next;
		        }
		        return *this;
		    }

		    iterator operator++ (int)
		    {
		    	iterator tmp(*this);
		    	if( node_ ){
		        	node_ = node_->next;
		        }
		        return tmp;
		    }

		    bool operator == (const iterator& rhs) const
		    {
		        return node_ == rhs.node_;
		    }

		    bool operator != (const iterator& rhs) const
		    {
		        return node_ != rhs.node_;
		    }

		    reference operator* () const
		    {
		        if( !node_ )
		        	throw std::logic_error( "Invalid iterator dereference");
		        return *(node_->value);

		    }

		    reference operator-> () const
		    {
		    	 if( !node_ )
					throw std::logic_error( "Invalid iterator dereference");
				return *(node_->value);
		    }

		};

public:
	CircularList() : head_(nullptr), tail_( nullptr ), size_(0) {};
	~CircularList();
	int size() const { return size_;}
	void push_back( const_reference value ) { add( value, &tail_ ); };
	void pop();
	void push_front( const_reference value ) { add( value, &head_ ); };
	const_reference front() const { if( !head_ ) throw std::logic_error( "empty CircularList"); return *(head_->value); };
	reference front() { if( !head_ ) throw std::logic_error( "empty CircularList"); return *(head_->value); };
	const_reference back() const { if( !tail_ ) throw std::logic_error( "empty CircularList"); return *(tail_->value); };
	reference back() { if( !tail_ ) throw std::logic_error( "empty CircularList"); return *(tail_->value); };
	iterator erase( iterator position);
	iterator erase( iterator first, iterator last);
	iterator position( int position );
	iterator begin() const {  return iterator( head_ ); };
	iterator end() const { return iterator( tail_ ); };

};

template<typename T>
void CircularList<T>::add( CircularList<T>::const_reference value, CircularList<T>::Node** nodeptr )
{
	CircularList<T>::Node* new_node = new CircularList<T>::Node( value );
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
typename CircularList<T>::Node* CircularList<T>::del(  CircularList<T>::Node* node )
{
	Node* it = node;
	Node* tmp = it->next;
	it->next = tmp->next;
	delete tmp;
	--size_;
	return it;
}

template<typename T>
typename CircularList<T>::iterator CircularList<T>::erase( CircularList<T>::iterator position )
{
	if( head_ == position.node_ ){
		pop();
		return begin();
	}
	Node* it = head_;
	if( tail_ == position.node_ ){
		for( ;it->next!=tail_; it = it->next){}
		tail_ = del(it);
		return begin();

	}
	do{
		if( it->next == position.node_ ){
			it = del(it);
			return iterator( it->next);
		}
		it = it->next;
	}while( it != tail_ );
	return iterator( tail_ );
}

template<typename T>
typename CircularList<T>::iterator CircularList<T>::erase( CircularList<T>::iterator first, CircularList<T>::iterator last )
{
	CircularList<T>::iterator it = first;
	while( it!=last ){
		it = erase( it );
	}
	return last;
}

template<typename T>
typename CircularList<T>::iterator CircularList<T>::position( int position )
{
	CircularList<T>::iterator it( head_ );
	for( int i = 0; i<position; ++i)
		++it;
	return it;
}

template<typename T>
void CircularList<T>::pop()
{
	if( !head_ )
		return;
	tail_->next = head_->next;
	delete head_;
	head_ = tail_->next;
	--size_;
}

template<typename T>
CircularList<T>::~CircularList()
{
	if( !head_ )
		return;
	CircularList<T>::Node* tmp = head_;
	tail_->next = nullptr;
	while( tmp ){
		head_ = tmp->next;
		delete tmp;
		tmp = head_;
	}
}

}//end namespace

#endif /* _CIRCULAR_LIST_HPP_ */
