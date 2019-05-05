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
	BaudotConverter::BaudotMessage codemessage;
	std::string ita2message;
	baudot_converter_.convert_ita2( plaintext, ita2message );
	baudot_converter_.encode_baudot( ita2message, codemessage );
	xor_message( codemessage );
	baudot_converter_.decode_baudot( codemessage, ciphertext );
}

void LorenzMachine::decipher( const std::string& ciphertext, std::string& plaintext )
{
	BaudotConverter::BaudotMessage codemessage;
	std::string ita2message;
	baudot_converter_.encode_baudot( ciphertext, codemessage );
	xor_message( codemessage );
	baudot_converter_.decode_baudot( codemessage, ita2message );
	baudot_converter_.convert_plaintext( ita2message, plaintext );
}

void LorenzMachine::xor_message( BaudotConverter::BaudotMessage& codemessage )
{
	BaudotConverter::BaudotBits key;
	for( auto i = codemessage.begin(); i != codemessage.end(); ++i){
		wheel_system_.generate_key(key);
		*i = (*i ^ key);
		wheel_system_.rotate();
	}
}

}//end namespace
