/*
 * test_lorenz_machine.cpp
 *
 *  Created on: May 5, 2019
 *      Author: bartlomiej
 */

#include "catch.hpp"
#include "../src/lorenz_machine.hpp"

namespace test {

using namespace lm;

SCENARIO( "lorenz machine usage" ) {

    GIVEN( "a lorenz machine object set in given starting position, a message with uppercase letters and digits" ) {
    	WheelSystem::WheelsPositionCode starting_position_code = {'a','a','a','a','a','a','a','a','a','a','a','a'} ;
    	LorenzMachine lorenz_machine;
    	lorenz_machine.init_position( starting_position_code );
    	std::string test_string("123ABC456CDE");
    	std::string ciphered_string;
    	std::string result_string;

        WHEN( "enciphering, setting the machine in the same starting position and deciphering the enciphered message" ) {

        	lorenz_machine.encipher( test_string, ciphered_string );
        	lorenz_machine.init_position( starting_position_code );
        	lorenz_machine.decipher( ciphered_string, result_string );
        	THEN( "the string we get from the operation is equal to the given string at the beginning" ) {
                REQUIRE( result_string == test_string );
            }
        }
    }
}

}// end namespace test


