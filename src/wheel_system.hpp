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

namespace lm {

class WheelSystem {

public:
	typedef std::array<int,12> WheelsPosition;
	typedef std::array<char,12> WheelsPositionCode;

	class ReadingTable {
	private:
		std::map<char, WheelsPosition > reading_table;

	public:
		void get_wheels_position(  const WheelsPositionCode& start_code, WheelsPosition& wheels_position );
		void load();
	};

private:
	static std::bitset<43> psi_1;
	static std::bitset<47> psi_2;
	static std::bitset<51> psi_3;
	static std::bitset<53> psi_4;
	static std::bitset<59> psi_5;
	static std::bitset<37> mu_37;
	static std::bitset<61> mu_61;
	static std::bitset<41> chi_1;
	static std::bitset<31> chi_2;
	static std::bitset<29> chi_3;
	static std::bitset<26> chi_4;
	static std::bitset<23> chi_5;
	static bool is_init;
	static void init_wheels();
	static ReadingTable reading_table;


public:
	WheelSystem();

};

}//end namespace



#endif /* WHEEL_SYSTEM_HPP_ */
