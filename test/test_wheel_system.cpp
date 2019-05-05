/*
 * test_wheel_system.cpp
 *
 *  Created on: May 5, 2019
 *      Author: bartlomiej
 */


#include "catch.hpp"
#include "../src/wheel_system.hpp"

namespace test {

using namespace lm;

SCENARIO( "wheel system usage" ) {

    GIVEN( "a wheel system object; a starting wheels position code" ) {
    	WheelSystem wheel_system;
    	WheelSystem::WheelsPositionCode position_code;
    	WheelSystem::WheelsPositionCode initialized_code = {'a','a','a','a','a','a','a','a','a','a','a','a'} ;
        WHEN( "initializing the position_code" ) {

        	WheelSystem::init_position_code( position_code );
        	THEN( "the position code is initialized with 12 'a' letters" ) {
                REQUIRE( position_code == initialized_code );
            }
        }
        WHEN( "getting starting wheels position from the Position Table" ) {
        	WheelSystem::WheelsPosition wheels_position;
        	wheel_system.get_wheels_position( initialized_code, wheels_position );
        	THEN( "in result we get the starting wheels position according to position_table.txt(first row for 12 'a's)" ) {
                REQUIRE( wheels_position[0] == 15 );
        		REQUIRE( wheels_position[1] == 47 );
        		REQUIRE( wheels_position[2] == 14 );
        		REQUIRE( wheels_position[3] == 1 );
        		REQUIRE( wheels_position[4] == 57 );
        		REQUIRE( wheels_position[5] == 37 );
        		REQUIRE( wheels_position[6] == 1 );
        		REQUIRE( wheels_position[7] == 9 );
        		REQUIRE( wheels_position[8] == 10 );
        		REQUIRE( wheels_position[9] == 2 );
        		REQUIRE( wheels_position[10] == 12 );
        		REQUIRE( wheels_position[11] == 5 );
            }

		}
    }
}

}// end namespace test

