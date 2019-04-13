/*
 * ita2_converter.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#include "ita2_converter.hpp"

namespace lm {

ITA2Converter::ITA2Map ITA2Converter::digits;
ITA2Converter::ITA2Map ITA2Converter::letters;

ITA2Converter::ITA2Converter(){
	if( ITA2Converter::digits.empty() )
		ITA2Converter::init_maps();
}

void ITA2Converter::init_maps(){


}

}

