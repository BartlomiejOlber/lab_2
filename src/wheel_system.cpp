/*
 * wheel_system.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#include "wheel_system.hpp"

namespace lm {

bool WheelSystem::is_init = false;
WheelSystem::ReadingTable WheelSystem::reading_table;

WheelSystem::WheelSystem()
{

	if( !WheelSystem::is_init ){
		WheelSystem::init_wheels();
		WheelSystem::reading_table.load();
		WheelSystem::is_init = true;
	}

}

void WheelSystem::init_wheels()
{


}

void WheelSystem::ReadingTable::load()
{

}



}//end namespace


