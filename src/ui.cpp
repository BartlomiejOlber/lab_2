/*
 * ui.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: bartlomiej
 */
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "ui.hpp"
#include "lorenz_machine.hpp"

namespace ui{

void UserInterface::loop()
{
	lm::LorenzMachine lorenz_machine;
	int choice = 0;
		do{
			std::system( "clear" );
			choice = get_number();
			switch(choice)
			{
				case 1:
					encipher_file( lorenz_machine );
					break;
				case 2:
					decipher_file( lorenz_machine );
					break;
				case 3:
					encipher_keyboard( lorenz_machine );
					break;
				case 4:
					decipher_keyboard( lorenz_machine );
					break;
			}
		}while(choice != 5);
}

void UserInterface::load_message( const std::string& file_name, std::string& message)
{
	std::ifstream ifs;
	ifs.open( file_name, std::ifstream::in);
	std::stringstream sstr;
	sstr << ifs.rdbuf();
	message = sstr.str();
	ifs.close();
}

void UserInterface::save_message( const std::string& message )
{
	remove( "output.txt" );
	std::ofstream outfile ("output.txt");
	outfile << message;
	outfile.close();
}

void UserInterface::get_position_code( lm::WheelSystem::WheelsPositionCode& code )
{
	std::string str;
	std::cin >> str;
	for( int i = 0; i<12; ++i )
		code[i] = str[i];
}

std::string UserInterface::get_file_name()
{
	std::string str;
	std::cin >> str;
	return str;
}

void UserInterface::get_message( std::string& message )
{
	char delim = 27;
	std::getline(std::cin, message, delim);
}

int UserInterface::get_number()
{
	int input;
	std::cin >> input;
	while(std::cin.fail()) {
		std::cout << "Error, please enter an integer" << std::endl;
		std::cin.clear();
		std::cin.ignore(256,'\n');
		std::cin >> input;
	}
	return input;
}

void UserInterface::print_message( const std::string& message )
{
	std::cout<<message;
}

void UserInterface::encipher_file( lm::LorenzMachine& lorenz_machine )
{
	std::string file_name, input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code = {'a', 'a','a','a','a','a','a','a','a','a','a','a'};
	file_name = get_file_name();
	load_message( file_name, input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	lorenz_machine.encipher( input_message, output_message );
	save_message( output_message );
}

void UserInterface::decipher_file( lm::LorenzMachine& lorenz_machine )
{
	std::string file_name, input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code = {'a', 'a','a','a','a','a','a','a','a','a','a','a'};
	file_name = get_file_name();
	load_message( file_name, input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	lorenz_machine.decipher( input_message, output_message );
	save_message( output_message );
}

void UserInterface::encipher_keyboard( lm::LorenzMachine& lorenz_machine )
{
	std::string file_name, input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code = {'a', 'a','a','a','a','a','a','a','a','a','a','a'};
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	get_message( input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	lorenz_machine.encipher( input_message, output_message );
	print_message( output_message );
}

void UserInterface::decipher_keyboard( lm::LorenzMachine& lorenz_machine )
{
	std::string file_name, input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code = {'a', 'a','a','a','a','a','a','a','a','a','a','a'};
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	get_message( input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	lorenz_machine.decipher( input_message, output_message );
	print_message( output_message );
}

}//end namespace

