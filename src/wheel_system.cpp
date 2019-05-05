/*
 * wheel_system.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#include <sstream>
#include <fstream>
#include "wheel_system.hpp"

namespace lm {

WheelSystem::PositionTable WheelSystem::position_table;

WheelSystem::WheelSystem()
{
	WheelSystem::init_wheels();
	WheelSystem::position_table.load();
}

void WheelSystem::init_wheels()
{
	std::ifstream ifs;
	ifs.open( "../data/wheels.txt", std::ifstream::in);
	init_wheel( ifs, psi_1 );
	init_wheel( ifs, psi_2 );
	init_wheel( ifs, psi_3 );
	init_wheel( ifs, psi_4 );
	init_wheel( ifs, psi_5 );
	init_wheel( ifs, mu_37 );
	init_wheel( ifs, mu_61 );
	init_wheel( ifs, chi_1 );
	init_wheel( ifs, chi_2 );
	init_wheel( ifs, chi_3 );
	init_wheel( ifs, chi_4 );
	init_wheel( ifs, chi_5 );
	ifs.close();
}

void WheelSystem::init_wheel( std::ifstream& ifs, Wheel& wheel )
{
	std::string line;
	std::string::iterator it;
	std::getline( ifs, line );
	for ( it=line.begin(); it!=line.end(); ++it )
	    wheel.push_back( (*it - '0') );
}

void WheelSystem::init_position_code( WheelsPositionCode& position_code )
{
	for( int i = 0; i<WHEELS_NUMBER; ++i ){
		position_code[i] = 'a';
	}
}

void WheelSystem::PositionTable::load()
{
	std::ifstream ifs;
	ifs.open( "../data/position_table.txt", std::ifstream::in);
	std::string line, tmp_str;
	int tmp;
	WheelsPosition wheels_position;
	char row_letter = 'a';
	while (std::getline( ifs, line )){
		std::stringstream iss(line);
		for ( auto it = wheels_position.begin(); it != wheels_position.end(); ++it ){
			std::getline(iss, tmp_str, ' ');
			tmp = std::stoi( tmp_str );
			*it = tmp;
		}
		position_table.position_table_.insert( std::pair<char,WheelsPosition>( row_letter , wheels_position ));
		++row_letter;
	}
	ifs.close();
}

void WheelSystem::PositionTable::init_wheels_position( const WheelsPositionCode& start_code, WheelsPosition& wheels_position )
{
	int i = 0;
	for ( auto it = start_code.begin(); it != start_code.end(); ++it, ++i){
		wheels_position.at( i ) = position_table.position_table_.at( *it ).at( i );
	}
}

void WheelSystem::set_wheels_position( const WheelsPositionCode& start_code )
{
	WheelsPosition wheels_position;
	get_wheels_position( start_code, wheels_position );
	Wheel::iterator it = psi_1.position( wheels_position[0] );
	psi_1_iterator = it;
	it = psi_2.position( wheels_position[1] );
	psi_2_iterator = it;
	it = psi_3.position( wheels_position[2] );
	psi_3_iterator = it;
	it = psi_4.position( wheels_position[3] );
	psi_4_iterator = it;
	it = psi_5.position( wheels_position[4] );
	psi_5_iterator = it;
	it = mu_37.position( wheels_position[5] );
	mu_37_iterator = it;
	it = mu_61.position( wheels_position[6] );
	mu_61_iterator = it;
	it = chi_1.position( wheels_position[7] );
	chi_1_iterator = it;
	it = chi_2.position( wheels_position[8] );
	chi_2_iterator = it;
	it = chi_3.position( wheels_position[9] );
	chi_3_iterator = it;
	it = chi_4.position( wheels_position[10] );
	chi_4_iterator = it;
	it = chi_5.position( wheels_position[11] );
	chi_5_iterator = it;
}

void WheelSystem::generate_key( Key& key )
{
	Key chi_key, psi_key;
	chi_key[0] = *(chi_1_iterator);
	chi_key[1] = *(chi_2_iterator);
	chi_key[2] = *(chi_3_iterator);
	chi_key[3] = *(chi_4_iterator);
	chi_key[4] = *(chi_5_iterator);
	psi_key[0] = *(psi_1_iterator);
	psi_key[1] = *(psi_2_iterator);
	psi_key[2] = *(psi_3_iterator);
	psi_key[3] = *(psi_4_iterator);
	psi_key[4] = *(psi_5_iterator);
	key = (chi_key ^ psi_key);
}

void WheelSystem::rotate()
{
	++chi_1_iterator;
	++chi_2_iterator;
	++chi_3_iterator;
	++chi_4_iterator;
	++chi_5_iterator;
	++mu_61_iterator;
	if(*mu_61_iterator)
		++mu_37_iterator;
	if(!(*mu_37_iterator)){
		++psi_1_iterator;
		++psi_2_iterator;
		++psi_3_iterator;
		++psi_4_iterator;
		++psi_5_iterator;
	}
}

}//end namespace


