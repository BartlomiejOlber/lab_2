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
const ITA2Converter::ITA2letter SHIFT_LETTERS("11011");
const ITA2Converter::ITA2letter UNKNOWN_SIGN("00000");
const ITA2Converter::ITA2letter SHIFT_DIGITS("11111");

ITA2Converter::ITA2Converter()
{
	if( ITA2Converter::digits.empty() )
		ITA2Converter::init_maps();
}

void ITA2Converter::init_maps()
{
	std::ifstream ifs;
	ifs.open( "../data/baudot_code.txt", std::ifstream::in);
	std::string line, tmp_str;
	char character;
	while (std::getline( ifs, line )){
		std::stringstream iss(line);
		std::getline(iss, tmp_str, ' ');
		std::bitset<5> tmp_bitset(tmp_str);
		std::getline(iss, tmp_str, ' ');
		character = std::stoi( tmp_str );
		letters.insert( ITA2Pair( character , tmp_bitset ));
		std::getline(iss, tmp_str, ' ');
		character = std::stoi( tmp_str );
		digits.insert( ITA2Pair( character , tmp_bitset ));
	}
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
				it = digits.find( *it_str );
				if( it != digits.end() ){
					letters_ctrl = false;
					codetext.push_back( SHIFT_DIGITS );
					codetext.push_back( it->second );
				}else{
					codetext.push_back( UNKNOWN_SIGN );
				}
			}
		}else{
			it = digits.find( *it_str );
			if ( it != digits.end() ){
				codetext.push_back( it->second );
			}else{
				it = letters.find( *it_str );
				if( it != letters.end() ){
					letters_ctrl = true;
					codetext.push_back( SHIFT_LETTERS );
					codetext.push_back( it->second );
				}else{
					codetext.push_back( UNKNOWN_SIGN );
				}
			}
		}
	}
}

void ITA2Converter::decode( const ITA2Message& codetext, std::string& plaintext )
{
	bool letters_ctrl = true;
	ITA2Map::iterator it_map;
	for( auto it = codetext.begin(); it!=codetext.end(); ++it ){
		if( *it == SHIFT_LETTERS ){
			letters_ctrl = true;
			//plaintext += shift_letters_char;
			continue;
		}
		if( *it == SHIFT_DIGITS ){
			letters_ctrl = false;
			//plaintext += shift_digits_char;
			continue;
		}
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

