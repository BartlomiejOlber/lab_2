/*
 * test_baudot_converter.cpp
 *
 *  Created on: May 5, 2019
 *      Author: bartlomiej
 */


#include "catch.hpp"
#include "../src/baudot_converter.hpp"

namespace test {

using namespace lm;

SCENARIO( "Baudot converter usage" ) {

    GIVEN( "text with uppercase letters and digits; converter object" ) {
    	std::string test_string("ABC123DEF456");
    	std::string predicted_ita2_string("ABC5RST8DEF5UVW");
    	std::string ita2_string;
    	std::string plaintext_string;
    	BaudotConverter converter;
        WHEN( "converting the to a text that includes only ITA2 characters" ) {

        	converter.convert_ita2( test_string, ita2_string );
        	THEN( "the text is correctly converted" ) {
                REQUIRE( ita2_string == predicted_ita2_string );
            }
        }
        WHEN( "converting back ITA2 string to plaintext string" ) {

        	converter.convert_plaintext( predicted_ita2_string, plaintext_string );
        	THEN( "converted text is the same as the given text at the beginning" ) {
                REQUIRE( plaintext_string == test_string );
            }

		}
    }
}

}// end namespace test

