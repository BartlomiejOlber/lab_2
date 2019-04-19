/*
 * ita2_converter.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include "ita2_converter.hpp"

namespace lm {

ITA2Converter::ITA2Map ITA2Converter::digits;
ITA2Converter::ITA2Map ITA2Converter::letters;

ITA2Converter::ITA2Converter()
{
	if( ITA2Converter::digits.empty() )
		ITA2Converter::init_maps();
}

void ITA2Converter::init_maps()
{
	std::ifstream ifs;
	ifs.open( "../data/digits.txt", std::ifstream::in);
	std::string line, tmp_str;
	char character;
	while (std::getline( ifs, line )){
		std::stringstream iss(line);
		std::getline(iss, tmp_str, ' ');
		std::bitset<5> tmp_bitset(tmp_str);
		std::getline(iss, tmp_str, ' ');
		character = tmp_str[0];
		letters.insert( std::pair<char, std::bitset<5> > ( character , tmp_bitset ));
		std::getline(iss, tmp_str, ' ');
		character = tmp_str[0];
		digits.insert( std::pair<char, std::bitset<5> >( character , tmp_bitset ));
	}
	std::bitset<5> tmp_bitset("01000");
	character = '\n';
	digits.insert( std::pair<char, std::bitset<5> >( character , tmp_bitset ));
	letters.insert( std::pair<char, std::bitset<5> >( character , tmp_bitset ));
	ITA2Converter::ITA2Map::iterator it, it2;
	for( it = digits.begin(), it2 = letters.begin(); it!=digits.end(), it2!=letters.end(); ++it, ++it2){
		std::cout<< it->second.to_string()<< " "<< it->first<< " "<<std::endl;
	}
	for( it = digits.begin(), it2 = letters.begin(); it!=digits.end(), it2!=letters.end(); ++it, ++it2){
			std::cout<< it2->second.to_string()<< " "<<  " "<<it2->first<<std::endl;
		}
	ifs.close();
}

}

