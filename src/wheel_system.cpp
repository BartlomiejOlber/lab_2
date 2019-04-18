/*
 * wheel_system.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include "wheel_system.hpp"

namespace lm {

bool WheelSystem::is_init = false;
WheelSystem::PositionTable WheelSystem::position_table;
mtl::CircularList<char> WheelSystem::psi_1;
mtl::CircularList<char> WheelSystem::psi_2;
mtl::CircularList<char> WheelSystem::psi_3;
mtl::CircularList<char> WheelSystem::psi_4;
mtl::CircularList<char> WheelSystem::psi_5;
mtl::CircularList<char> WheelSystem::mu_37;
mtl::CircularList<char> WheelSystem::mu_61;
mtl::CircularList<char> WheelSystem::chi_1;
mtl::CircularList<char> WheelSystem::chi_2;
mtl::CircularList<char> WheelSystem::chi_3;
mtl::CircularList<char> WheelSystem::chi_4;
mtl::CircularList<char> WheelSystem::chi_5;


WheelSystem::WheelSystem()
{

	if( !WheelSystem::is_init ){
		WheelSystem::init_wheels();
		WheelSystem::position_table.load();
		WheelSystem::is_init = true;
	}

}

void WheelSystem::init_wheels()
{
	std::ifstream ifs;
	ifs.open( "../data/wheels.txt", std::ifstream::in);
	std::string line;
	std::string::iterator it;
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
	    psi_1.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		psi_2.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		psi_3.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		psi_4.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		psi_5.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		mu_37.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		mu_61.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		chi_1.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		chi_2.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		chi_3.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		chi_4.push_back( *it );
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
		chi_5.push_back( *it );
	is_init = true;
	ifs.close();
}

void WheelSystem::PositionTable::load()
{
	std::ifstream ifs;
	ifs.open( "../data/position_table.txt", std::ifstream::in);
	std::string line;
	std::string::iterator it;
	std::getline( ifs, line );
}

void WheelSystem::PositionTable::get_wheels_position(  const WheelsPositionCode& start_code, WheelsPosition& wheels_position )
{

}

}//end namespace


