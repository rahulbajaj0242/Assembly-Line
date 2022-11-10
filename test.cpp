#include <iostream>
#include <string.h>
#include "sstream"
using namespace std;

char m_delimiter = ',';

std::string trim(std::string &str){
    int start = str.find_first_not_of(' ');
    int end = str.find_last_not_of(' ');
    return str.substr(start, end-start+1);
  }

std::string extractToken(const std::string& str, size_t& next_pos, bool& more) {
  string token;
  string stringAtPos = str.substr(next_pos);
  stringstream s(stringAtPos);
  if(stringAtPos[0] == m_delimiter) {
    throw "Delimiter Found!";
  }
  if(getline(s, token, m_delimiter) && more) {
    token = trim(token);
    size_t currPos = str.find(token);
    next_pos = str.find(m_delimiter, currPos);
    more = true;
    if(next_pos == string::npos) {
      more= false;
    }
    else {
      next_pos++;
    }
    return token;
  }
  more = false;
  return "NULL";
}


int main() {
  
  string s = "Armchair,    654321,  10,  Upholstered Wing Chair";

  bool more = true;
  size_t next_pos = 0;

  while(more) {
    try
    {
      cout << extractToken(s, next_pos, more) << endl;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
  }

}