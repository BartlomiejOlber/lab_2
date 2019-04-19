/*
 * lorenz_machine.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: bartlomiej
 */

#include "lorenz_machine.hpp"

namespace lm {

void LorenzMachine::encipher( const std::string& plaintext, std::string& ciphertext )
{
	ITA2Converter::ITA2Message codemessage;
	ita2_converter_.encode( plaintext, codemessage );
	std::bitset<5> key;
	for( auto i = codemessage.begin(); i != codemessage.end(); ++i){
		wheel_system_.generate_key(key);
		*i = (*i ^ key);
		wheel_system_.rotate();
	}
	ita2_converter_.decode( codemessage, ciphertext );
}

void LorenzMachine::decipher( const std::string& ciphertext, std::string& plaintext )
{
	ITA2Converter::ITA2Message codemessage;
	ita2_converter_.encode( ciphertext, codemessage );
	std::bitset<5> key;
	for( auto i = codemessage.begin(); i != codemessage.end(); ++i){
		wheel_system_.generate_key(key);
		*i = (*i ^ key);
		wheel_system_.rotate();
	}
	ita2_converter_.decode( codemessage, plaintext );
}

}//end namespace
