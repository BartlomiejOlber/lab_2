/*
 * test_circular_list.cpp
 *
 *  Created on: May 5, 2019
 *      Author: bartlomiej
 */


#include "catch.hpp"
#include "../src/circular_list.hpp"

namespace test {

using namespace mtl;

SCENARIO( "my template circular list usage" ) {

    GIVEN( "a circular list of integers object is created" ) {

    	CircularList<int> list;
    	int first = 1;
    	int second = 2;
    	int third = 3;
        WHEN( "three elemets are addeed to the list" ) {
        	list.push_back( first );
        	list.push_back( second );
        	list.push_back( third );
        	THEN( "the list size = 3" ) {
                REQUIRE( list.size() == 3 );
            }
        	THEN( "the dereferenced iterator pointing on the beginning of the list equals the first element" ) {
                REQUIRE( *(list.begin()) == first );
            }
        	THEN( "the dereferenced iterator pointing on the end of the list equals the third element" ) {
                REQUIRE( *(list.end()) == third );
            }
        }
        WHEN( "incrementing thr iterator pointing on the end of the list" ) {
        	list.push_back( first );
        	list.push_back( second );
        	list.push_back( third );
        	CircularList<int>::iterator it = list.end();
        	++it;
        	THEN( "the iterator points on the begin of the list" ) {
                REQUIRE( it == list.begin() );
            }
        }
    }
}

}// end namespace test

