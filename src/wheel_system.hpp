/*
 * wheels_system.hpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#ifndef WHEEL_SYSTEM_HPP_
#define WHEEL_SYSTEM_HPP_

#include <array>
#include "circular_list.hpp"
#include <map>

namespace lm {

class WheelSystem {

public:
	typedef std::array<int,12> WheelsPosition;
	typedef std::array<char,12> WheelsPositionCode;

	class PositionTable {
	private:
		std::map<char, WheelsPosition > reading_table;

	public:
		void get_wheels_position(  const WheelsPositionCode& start_code, WheelsPosition& wheels_position );
		void load();
	};

private:
	static mtl::CircularList<char> psi_1;
	static mtl::CircularList<char> psi_2;
	static mtl::CircularList<char> psi_3;
	static mtl::CircularList<char> psi_4;
	static mtl::CircularList<char> psi_5;
	static mtl::CircularList<char> mu_37;
	static mtl::CircularList<char> mu_61;
	static mtl::CircularList<char> chi_1;
	static mtl::CircularList<char> chi_2;
	static mtl::CircularList<char> chi_3;
	static mtl::CircularList<char> chi_4;
	static mtl::CircularList<char> chi_5;
	static bool is_init;
	static void init_wheels();
	static PositionTable position_table;


public:
	WheelSystem();

};

}//end namespace



#endif /* WHEEL_SYSTEM_HPP_ */
