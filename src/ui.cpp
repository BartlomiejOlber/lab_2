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
		print_options();
		choice = get_choice();
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
	std::ofstream ofs;
	ofs.open( "../data/output.txt" , std::ofstream::out | std::ofstream::trunc);
	ofs << message;
	ofs.close();
}

void UserInterface::get_position_code( lm::WheelSystem::WheelsPositionCode& code )
{
	std::string str;
	std::cout<<"\n Enter machine's starting configuration (12 letters)\n";
	std::getline(std::cin, str);
	std::transform( str.begin(), str.end(), str.begin(), ::tolower);
	for( unsigned int i = 0; i<str.size() && i<12; ++i )
		code[i] = str[i];
}

void UserInterface::get_file_name( std::string& file_name )
{
	std::cout<<"\n Enter the file's name e.g. message.txt\n";
	std::getline(std::cin, file_name);
}

void UserInterface::get_message( std::string& message )
{
	char delim = 27;
	std::cout<<"\n Type your message then press [esc] and enter to commit\n";
	std::getline(std::cin, message,delim);
}

int UserInterface::get_choice()
{
	int input;
	std::cin >> input;
	while(std::cin.fail()) {
		std::cout << "Error, please enter an integer" << std::endl;
		std::cin.clear();
		std::cin.ignore(256,'\n');
		std::cin >> input;
	}
	std::cin.ignore();
	return input;
}

void UserInterface::print_message( const std::string& message )
{
	std::cout<<"\n Your en/decrypted message :\n";
	std::cout<<message;
	std::cout<< " \n\n [1]. Back"<<std::endl;
	std::cout<< "\n Selection: ";
	int choice = 0;
	while (choice!=1)
	{
		choice = get_choice();
	}
}

void UserInterface::print_options()
{
	std::cout<< "\n\n\t*Available options:*\n\n" << std::endl;
	std::cout<< "[1]. Encipher file message" << std::endl;
	std::cout<< "[2]. Decipher file message"<< std::endl;
	std::cout<< "[3]. Encipher keyboard message"<<std::endl;
	std::cout<< "[4]. Decipher keyboard message"<<std::endl;
	std::cout<< "[5]. Exit"<<std::endl;
	std::cout<< "\n Selection: ";
}

void UserInterface::encipher_file( lm::LorenzMachine& lorenz_machine )
{
	std::system( "clear" );
	std::string file_name, input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code;
	lm::WheelSystem::init_position_code( position_code );
	get_file_name( file_name );
	load_message( file_name, input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	lorenz_machine.encipher( input_message, output_message );
	save_message( output_message );
}

void UserInterface::decipher_file( lm::LorenzMachine& lorenz_machine )
{
	std::system( "clear" );
	std::string file_name, input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code;
	lm::WheelSystem::init_position_code( position_code );
	get_file_name( file_name );
	load_message( file_name, input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	lorenz_machine.decipher( input_message, output_message );
	save_message( output_message );
}

void UserInterface::encipher_keyboard( lm::LorenzMachine& lorenz_machine )
{
	std::system( "clear" );
	std::string input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code;
	lm::WheelSystem::init_position_code( position_code );
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	get_message( input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	lorenz_machine.encipher( input_message, output_message );
	print_message( output_message );
}

void UserInterface::decipher_keyboard( lm::LorenzMachine& lorenz_machine )
{
	std::system( "clear" );
	std::string input_message, output_message;
	lm::WheelSystem::WheelsPositionCode position_code;
	lm::WheelSystem::init_position_code( position_code );
	get_position_code( position_code );
	lorenz_machine.init_position( position_code );
	get_message( input_message );
	std::transform( input_message.begin(), input_message.end(), input_message.begin(), ::toupper);
	lorenz_machine.decipher( input_message, output_message );
	print_message( output_message );
}

}//end namespace

