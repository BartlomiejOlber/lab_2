/*
 * lorenz_machine.hpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#ifndef LORENZ_MACHINE_HPP_
#define LORENZ_MACHINE_HPP_

#include "baudot_converter.hpp"
#include "wheel_system.hpp"

namespace lm{

class LorenzMachine{

private:
	WheelSystem wheel_system_;
	BaudotConverter baudot_converter_;

public:
	void encipher( const std::string& plaintext, std::string& ciphertext );
	void decipher( const std::string& ciphertext, std::string& plaintext );
	void init_position( const WheelSystem::WheelsPositionCode& start_code ){
		wheel_system_.set_wheels_position( start_code ); }

private:
	void xor_message( BaudotConverter::BaudotMessage& codemessage );
};

}//end namespace

#endif /* LORENZ_MACHINE_HPP_ */
