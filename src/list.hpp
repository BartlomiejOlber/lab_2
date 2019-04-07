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

	Node* head_;
	Node* tail_;
	int size_;
	void add( const_reference value, Node** nodeptr );

public:
	class iterator : public std::iterator<std::forward_iterator_tag, Node> {
			Node* node_;
			int pos_;
			int max_pos_;
		public:
			iterator() : node_(nullptr), pos_(0), max_pos_( size_ ){};
			explicit iterator( Node* node ) : node_(node), pos_(0), max_pos_( size_ ) {};
			iterator( const iterator& right_iterator ) : node_( right_iterator.node_ ),  pos_(0), max_pos_( size_ ) {};
			iterator& operator= ( const iterator& right_iterator ) { //todo: return const iterator
				node_ = right_iterator.node_;
				return *this;
			};
		    iterator& operator++ ()
		    {
		        if( node_ ){
		        	node_ = node_->next;
		        	pos_++;
		        }
		        return *this;
		    }

		    iterator operator++ (int)
		    {
		    	iterator tmp(*this);
		    	if( node_ ){
		        	node_ = node_->next;
		        	pos_++;
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
	List() : head_(nullptr), tail_( nullptr ), size_(0) {};
	~List();
	int size() const { return size_;}
	void push_back( const_reference value ) { add( value, &tail_ ); };
	void pop();
	void push_front( const_reference value ) { add( value, &head_ ); };
	const_reference front() const { if( !head_ ) throw std::logic_error( "empty list"); return *(head_->value); };
	reference front() { if( !head_ ) throw std::logic_error( "empty list"); return *(head_->value); };
	const_reference back() const { if( !tail_ ) throw std::logic_error( "empty list"); return *(tail_->value); };
	reference back() { if( !tail_ ) throw std::logic_error( "empty list"); return *(tail_->value); };
	iterator erase( iterator position);
	iterator erase( iterator first, iterator last);
	iterator begin() {  return iterator( head_ ); };
	iterator end()
	};
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

/**template<typename T>
List<T>::iterator List<T>::erase( iterator position )
{
	iterator it = begin();
	do{
		if(){
			it ==
		}
		++it;
	}while( it != end() );


}
**/
template<typename T>
void List<T>::pop()
{
	if( !head_ )
		return;
	tail_->next = head_->next;
	delete head_;
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
