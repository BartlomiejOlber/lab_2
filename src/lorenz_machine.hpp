/*
 * lorenz_machine.hpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#ifndef LORENZ_MACHINE_HPP_
#define LORENZ_MACHINE_HPP_

#include <string>
#include "wheel_system.hpp"
#include "ita2_converter.hpp"

namespace lm{

class LorenzMachine{

private:
	WheelSystem wheel_system_;
	ITA2Converter ita2_converter_;

public:
	void encipher( const std::string& plaintext, std::string& ciphertext );
	void decipher( const std::string& ciphertext, std::string& plaintext );
	void init_position( const WheelSystem::WheelsPositionCode& start_code ){
		wheel_system_.set_wheels_position( start_code ); }

};

}//end namespace



#endif /* LORENZ_MACHINE_HPP_ */
