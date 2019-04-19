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
	std::bitset<5> tmp_bitset_("00100");
	character = ' ';
	digits.insert( std::pair<char, std::bitset<5> >( character , tmp_bitset_ ));
	letters.insert( std::pair<char, std::bitset<5> >( character , tmp_bitset_ ));
	ifs.close();
}

void ITA2Converter::encode( const std::string& plaintext, ITA2Message& codetext )
{
	bool letters_ctrl = true;
	ITA2Map::iterator it;
	for( auto it_str = plaintext.begin(); it_str!=plaintext.end(); ++it_str ){
		if( letters_ctrl ){
			it = letters.find( *it_str );
			if ( it != letters.end() ){
				codetext.push_back( it->second );
			}else{
				letters_ctrl = false;
				codetext.push_back( std::bitset<5>("11011"));
				it = digits.find( *it_str );
				codetext.push_back( it->second );
			}
		}else{
			it = digits.find( *it_str );
			if ( it != digits.end() ){
				codetext.push_back( it->second );
			}else{
				letters_ctrl = true;
				codetext.push_back( std::bitset<5>("11011"));
				it = letters.find( *it_str );
				codetext.push_back( it->second );
			}
		}
	}
	/**std::cout<< plaintext<<std::endl;
	for( auto it = codetext.begin(); it!=codetext.end(); ++it ){
		std::cout<< it->to_string()<< " ";
	}**/

}

void ITA2Converter::decode( const ITA2Message& codetext, std::string& plaintext )
{
	bool letters_ctrl = true;
	ITA2Map::iterator it_map;
	for( auto it = codetext.begin(); it!=codetext.end(); ++it ){
		if( *it == std::bitset<5>("11011") )
			letters_ctrl = !letters_ctrl;
		if( letters_ctrl ){
			for( it_map = letters.begin(); it_map!= letters.end(); ++it_map){
				if( *it == it_map->second ){
					plaintext += it_map->first;
				}
			}
		}else{
			for( it_map = digits.begin(); it_map!= digits.end(); ++it_map){
				if( *it == it_map->second ){
					plaintext += it_map->first;
				}
			}
		}
	}
}

}//end namespace

