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
#include "wheel_system.hpp"
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

	lm::LorenzMachine lorenz_machine;
	lm::WheelSystem wheels;
	lm::ITA2Converter converter;
	lm::ITA2Converter::ITA2Message mess;
	string m("cr7 mm9 sg8 jh14 ja24");
	std::transform( m.begin(), m.end(), m.begin(), ::toupper);
	string co, ci;
	lm::WheelSystem::WheelsPositionCode code = {'a', 'a','c','g','e','f','g','a','a','a','a','a'};
	lorenz_machine.init_position( code );
	lorenz_machine.encipher( m, co );
	cout<<m<<" ZAKODOWANA "<<co<<endl;
	lorenz_machine.init_position( code );
	lorenz_machine.decipher( co, ci );
	cout<<co<<" ODKODOWANA "<<ci<<endl;

	return 0;
}
