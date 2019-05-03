/*
 * wheels_system.hpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#ifndef WHEEL_SYSTEM_HPP_
#define WHEEL_SYSTEM_HPP_

#include <array>
#include <bitset>
#include <map>
#include "circular_list.hpp"

namespace lm {

class WheelSystem {
	static const int WHEELS_NUMBER = 12;

public:
	typedef std::bitset<5> Key;
	typedef std::array<int,WHEELS_NUMBER> WheelsPosition;
	typedef std::array<char,WHEELS_NUMBER> WheelsPositionCode;
	typedef mtl::CircularList<char> Wheel;

	class PositionTable {
	private:
		std::map<char, WheelsPosition > position_table_;

	public:
		void load();
		void init_wheels_position( const WheelsPositionCode& start_code, WheelsPosition& wheels_position );
	};

private:
	Wheel psi_1;
	Wheel::iterator psi_1_iterator;
	Wheel psi_2;
	Wheel::iterator psi_2_iterator;
	Wheel psi_3;
	Wheel::iterator psi_3_iterator;
	Wheel psi_4;
	Wheel::iterator psi_4_iterator;
	Wheel psi_5;
	Wheel::iterator psi_5_iterator;
	Wheel mu_37;
	Wheel::iterator mu_37_iterator;
	Wheel mu_61;
	Wheel::iterator mu_61_iterator;
	Wheel chi_1;
	Wheel::iterator chi_1_iterator;
	Wheel chi_2;
	Wheel::iterator chi_2_iterator;
	Wheel chi_3;
	Wheel::iterator chi_3_iterator;
	Wheel chi_4;
	Wheel::iterator chi_4_iterator;
	Wheel chi_5;
	Wheel::iterator chi_5_iterator;
	void init_wheels();
	void init_wheel( std::ifstream& ifs, Wheel& wheel );
	static PositionTable position_table;

public:
	WheelSystem();
	void get_wheels_position( const WheelsPositionCode& start_code, WheelsPosition& wheels_position )
	{
		position_table.init_wheels_position( start_code, wheels_position );
	}
	void set_wheels_position( const WheelsPositionCode& start_code );
	void generate_key( Key& key );
	void rotate();
	static void init_position_code( WheelsPositionCode& position_code );
};

}//end namespace

#endif /* WHEEL_SYSTEM_HPP_ */
