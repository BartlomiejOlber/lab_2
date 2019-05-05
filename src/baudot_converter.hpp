/*
 * ita2_converter.hpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#ifndef BAUDOT_CONVERTER_HPP_
#define BAUDOT_CONVERTER_HPP_

#include <string>
#include <bitset>
#include <map>
#include <vector>

namespace lm {

class BaudotConverter {
public:
	typedef std::bitset<5> BaudotBits;
	typedef std::map<char, BaudotBits > BaudotCode;
	typedef std::pair<char, BaudotBits> BaudotPair;
	typedef std::vector<BaudotBits > BaudotMessage;
	typedef std::map<char, char> ITA2Map;
	typedef std::pair<char, char> ITA2Pair;

private:
	static BaudotCode baudot_code;
	static ITA2Map ita2_map;
	static void init_maps();

public:
	BaudotConverter();
	void encode_baudot( const std::string& ita2text, BaudotMessage& codetext  );
	void decode_baudot( const BaudotMessage& codetext, std::string& ita2text );
	void convert_ita2( const std::string& plaintext, std::string& ita2text  );
	void convert_plaintext( const std::string& ita2text, std::string& plaintext );
};

}//end namespace




#endif /* BAUDOT_CONVERTER_HPP_ */
