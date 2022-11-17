#include <iostream>
#include "Utilities.h"
#include <string.h>
#include "sstream"

using namespace std;

namespace sdds {

  char Utilities::m_delimiter = ' ';

  std::string Utilities::trim(std::string &str){
    int start = str.find_first_not_of(' ');
    int end = str.find_last_not_of(' ');
    return str.substr(start, end-start+1);
  }

  void Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
  }

  size_t Utilities::getFieldWidth() const {
    return m_widthField;
  }

  std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    if(more) {
      string token;
      string stringAtPos = str.substr(next_pos);
      stringstream s(stringAtPos);
      if(stringAtPos[0] == m_delimiter) {
        more = false;
        throw "Delimiter Found!";
      }

      auto delFound = stringAtPos.find(m_delimiter);

      if(delFound == string::npos) {
        getline(s, token, '\n');
        token = trim(token);
        if(m_widthField < token.size()) m_widthField= token.size();
        more = false;
        return token;
      }
      else if(getline(s, token, m_delimiter)) {
        // size_t currPos = next_pos + token.length() + 1;
        next_pos = next_pos+token.length() + 1;
        token = trim(token);
        more = true;
        // if(next_pos == string::npos) {
        //   more= false;
        // }
        // else {
        //   next_pos++;
        // }
        if(m_widthField < token.size()) m_widthField= token.size();
        return token;
      }
      more = false;
    }
    return "NULL";
  }

  // std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	// {
	// 	std::string token{};
	// 	std::size_t position = str.find(getDelimiter(), next_pos);

	// 	if (position == next_pos)
	// 	{
	// 		more = false;
	// 		throw std::string("Not found!");
	// 	}
	// 	else if (position != std::string::npos)
	// 	{
	// 		token = str.substr(next_pos, position - next_pos);
	// 		next_pos = token.find_first_not_of(" ");
	// 		token.erase(token.begin(), token.begin() + next_pos);
	// 		size_t end = token.find_last_not_of(" ");
	// 		token.erase(end + 1);
	// 		m_widthField = std::max(m_widthField, token.length());
	// 		next_pos = position + 1;
	// 		more = true;
	// 	}
	// 	else if (position == std::string::npos)
	// 	{
	// 		token = str.substr(next_pos, position - next_pos);
	// 		next_pos = token.find_first_not_of(" ");
	// 		token.erase(token.begin(), token.begin() + next_pos);
	// 		size_t end = token.find_last_not_of(" ");
	// 		token.erase(end + 1);
	// 		m_widthField = std::max(m_widthField, token.length());
	// 		next_pos = position + 1;
	// 		more = false;
	// 	}

	// 	return token;

	// }

  void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter = newDelimiter;
  }

  char Utilities::getDelimiter() {
    return m_delimiter;
  }

}