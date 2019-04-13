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

namespace lm{

class LorenzMachine{

private:

	WheelSystem wheel_system;

public:
	void encipher( const std::string& plaintext, std::string& ciphertext  );
	void decipher( const std::string& ciphertext, std::string& plaintext );
};

}//end namespace



#endif /* LORENZ_MACHINE_HPP_ */
