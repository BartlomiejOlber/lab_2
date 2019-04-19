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
#include "circular_list.hpp"
#include <map>

namespace lm {

class WheelSystem {

public:
	typedef std::array<int,12> WheelsPosition;
	typedef std::array<char,12> WheelsPositionCode;
	typedef mtl::CircularList<char> Wheel;
	typedef std::array<WheelSystem::Wheel::iterator,12> CurrentSettings;

	class PositionTable {
	private:
		std::map<char, WheelsPosition > position_table_;

	public:
		void load();
		void get_wheels_position_(  const WheelsPositionCode& start_code, WheelsPosition& wheels_position );
	};

private:
	static Wheel psi_1;
	static Wheel psi_2;
	static Wheel psi_3;
	static Wheel psi_4;
	static Wheel psi_5;
	static Wheel mu_37;
	static Wheel mu_61;
	static Wheel chi_1;
	static Wheel chi_2;
	static Wheel chi_3;
	static Wheel chi_4;
	static Wheel chi_5;
	static bool is_init;
	static void init_wheels();
	static PositionTable position_table;
	CurrentSettings current_position_;

public:
	WheelSystem();
	void get_wheels_position(  const WheelsPositionCode& start_code, WheelsPosition& wheels_position )
	{
		position_table.get_wheels_position_( start_code, wheels_position );
	}
	void set_wheels_position( const WheelsPositionCode& start_code );
	void generate_key( std::bitset<5>& key );
	void rotate();
};

}//end namespace

#endif /* WHEEL_SYSTEM_HPP_ */
