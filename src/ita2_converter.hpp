/*
 * ita2_converter.hpp
 *
 *  Created on: Apr 13, 2019
 *      Author: bartlomiej
 */

#ifndef ITA2_CONVERTER_HPP_
#define ITA2_CONVERTER_HPP_

#include <string>
#include <bitset>
#include <map>
#include <vector>

namespace lm {

class ITA2Converter {
public:
	typedef std::bitset<5> ITA2letter;
	typedef std::map<char, ITA2letter > ITA2Map;
	typedef std::pair<char, ITA2letter> ITA2Pair;
	typedef std::vector<ITA2letter > ITA2Message;

private:
	static ITA2Map letters;
	static ITA2Map digits;
	static void init_maps();

public:
	ITA2Converter();
	void encode( const std::string& plaintext, ITA2Message& codetext  );
	void decode( const ITA2Message& codetext, std::string& plaintext );
};

}//end namespace




#endif /* ITA2_CONVERTER_HPP_ */
