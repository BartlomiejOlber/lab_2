//============================================================================
// Name        : lab_2.cpp
// Author      : d
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include<list>

#include "lorenz_machine.hpp"
#include "ita2_converter.hpp"
#include "circular_list.hpp"
using namespace std;

struct MyClass {

	int value_;
	explicit MyClass( int value ) : value_(value){};
	~MyClass(){ std::cout<<"destruct my class object : "<< value_ << endl; };
};

std::ostream& operator<< ( std::ostream& strm, const MyClass& obj) { strm<< obj.value_; return strm;};

int main() {



	/**mtl::CircularList<const char*> str_list;
	str_list.push_front( "Liverpool" );
	str_list.push_front( "Football" );
	str_list.push_back( "Club" );
	cout<< str_list.front()<< std::endl << str_list.back() <<std::endl;
	cout<<" Size: "<< str_list.size() << std::endl;
	mtl::CircularList<const char*>::iterator it = str_list.begin();
	for( int i = 0; i<10; ++i){
		cout<< *it<<endl;
		it++;

	}
	cout<< "\n\n";
	str_list.erase( str_list.end(), ++str_list.begin() );
	it = str_list.begin();
	for( int i = 0; i<10; ++i){
		cout<<*it<<endl;
		it++;
	}
	**/
	lm::LorenzMachine lorenz_machine;
	lm::WheelSystem wheels;
	lm::ITA2Converter converter;
	lm::ITA2Converter::ITA2Message mess;
	string m(" 999mai\ncki999 syn kierownika");
	std::transform( m.begin(), m.end(), m.begin(), ::toupper);
	converter.encode( m, mess );
	/**MyClass my_class(1);
	mtl::List<MyClass> int_list;
	int_list.push_back( my_class );
	my_class.value_= 10;
	int_list.push_front( my_class );
	my_class.value_= 5;
	int_list.push_back( my_class );
	cout<< int_list.front()<< std::endl << int_list.back() <<std::endl;
	cout<<" Size: "<< int_list.size() << std::endl;
	**/

	return 0;
}
