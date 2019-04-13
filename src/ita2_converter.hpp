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
	typedef std::map<char, std::bitset<5> > ITA2Map;
	typedef std::vector<std::bitset<5> > ITA2Message;

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
