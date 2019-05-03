/*
 * ui.hpp
 *
 *  Created on: Apr 28, 2019
 *      Author: bartlomiej
 */

#ifndef UI_HPP_
#define UI_HPP_

#include <string>
#include "lorenz_machine.hpp"


namespace ui{

class UserInterface{

	void load_message( const std::string& file_name, std::string& message);
	void save_message( const std::string& message );
	void get_position_code( lm::WheelSystem::WheelsPositionCode& code );
	void get_file_name( std::string& file_name );
	void get_message( std::string& message );
	int get_choice();
	void print_message( const std::string& message );
	void print_options();
	void encipher_file( lm::LorenzMachine& lorenz_machine );
	void decipher_file( lm::LorenzMachine& lorenz_machine );
	void encipher_keyboard( lm::LorenzMachine& lorenz_machine );
	void decipher_keyboard( lm::LorenzMachine& lorenz_machine );

public:
	void loop();
};

}//end namespace



#endif /* UI_HPP_ */
