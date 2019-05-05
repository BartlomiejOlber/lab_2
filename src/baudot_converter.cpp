/*
 * ita2_converter.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#include "baudot_converter.hpp"

#include <sstream>
#include <fstream>

namespace lm {

BaudotConverter::ITA2Map BaudotConverter::ita2_map;
BaudotConverter::BaudotCode BaudotConverter::baudot_code;
const char SHIFT_LETTERS_CHAR = 56;
const char SHIFT_FIGURES_CHAR = 53;

BaudotConverter::BaudotConverter()
{
	if( BaudotConverter::ita2_map.empty() )
		BaudotConverter::init_maps();
}

void BaudotConverter::init_maps()
{
	std::ifstream ifs;
	ifs.open( "../data/baudot_code.txt", std::ifstream::in);
	std::string line, tmp_str;
	char character, character2;
	while (std::getline( ifs, line )){
		std::stringstream iss(line);
		std::getline(iss, tmp_str, ' ');
		std::bitset<5> tmp_bitset(tmp_str);
		std::getline(iss, tmp_str, ' ');
		character = std::stoi( tmp_str );
		baudot_code.insert( BaudotPair( character , tmp_bitset ));
	}
	ifs.close();
	ifs.open("../data/ita2.txt", std::ifstream::in);
	while (std::getline( ifs, line )){
		std::stringstream iss(line);
		std::getline(iss, tmp_str, ' ');
		character = std::stoi( tmp_str );
		std::getline(iss, tmp_str, ' ');
		character2 = std::stoi( tmp_str );
		ita2_map.insert( ITA2Pair( character , character2 ));
	}
	ifs.close();
}

void BaudotConverter::encode_baudot( const std::string& ita2text, BaudotMessage& codetext )
{
	BaudotCode::iterator it_map;
	for( auto it = ita2text.begin(); it!=ita2text.end(); ++it ){
		it_map = baudot_code.find( *it );
		codetext.push_back( it_map->second );
	}
}

void BaudotConverter::decode_baudot( const BaudotMessage& codetext, std::string& ita2text )
{
	for( auto it = codetext.begin(); it!= codetext.end(); ++it ){
		for( auto it_map = baudot_code.begin(); it_map != baudot_code.end(); it_map++){
			if( *it == it_map->second ){
				ita2text += it_map->first;
				continue;
			}
		}
	}
}

void BaudotConverter::convert_ita2( const std::string& plaintext, std::string& ita2text )
{
	bool letters_ctrl = true;
	ITA2Map::iterator it;
	for( auto it_str = plaintext.begin(); it_str!=plaintext.end(); ++it_str ){
		if( letters_ctrl ){
			it = ita2_map.find( *it_str );
			if ( it != ita2_map.end() ){
				ita2text += it->first;
			}else{
				letters_ctrl = false;
				ita2text += SHIFT_FIGURES_CHAR;
				for( it = ita2_map.begin(); it!= ita2_map.end(); ++it){
					if( *it_str == it->second ){
						ita2text += it->first;
						continue;
					}
				}
			}
		}else{
			it = ita2_map.find( *it_str );
			if ( it != ita2_map.end() ){
				letters_ctrl = true;
				ita2text += SHIFT_LETTERS_CHAR;
				ita2text += it->first;
			}else{
				for( it = ita2_map.begin(); it!= ita2_map.end(); ++it){
					if( *it_str == it->second ){
						ita2text += it->first;
						continue;
					}
				}
			}
		}
	}
}

void BaudotConverter::convert_plaintext( const std::string& ita2text, std::string& plaintext)
{
	bool letters_ctrl = true;
	ITA2Map::iterator it;
	for( auto it_str = ita2text.begin(); it_str!=ita2text.end(); ++it_str ){
		if( *it_str == SHIFT_FIGURES_CHAR ){
			letters_ctrl = false;
			continue;
		}
		if( *it_str == SHIFT_LETTERS_CHAR ){
			letters_ctrl = true;
			continue;
		}
		if( letters_ctrl ){
			it = ita2_map.find( *it_str );
			plaintext += it->first;
		}else{
			it = ita2_map.find( *it_str );
			plaintext += it->second;
		}
	}
}

}//end namespace

