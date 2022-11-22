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
        more = false;
        return token;
      }
      else if(getline(s, token, m_delimiter)) {
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
        // if(m_widthField < token.length()) m_widthField= token.length();
        return token;
      }
      more = false;
    }
    return "NULL";
}


int main() {
  
  // string s = "Bed,         123456,   5,  Queen size bed with headboard";

  // bool more = true;
  // size_t next_pos = 0;

  // while(more) {
  //   try
  //   {
  //     cout << extractToken(s, next_pos, more) << endl;
  //   }
  //   catch(const std::exception& e)
  //   {
  //     std::cerr << e.what() << '\n';
  //   }
    
  // }

  // string list = " Office Chair|Desk|Bookcase|Bookcase|Filing Cabinet";
  // int cnt = count(list.begin(), list.end(), '|');
  // cout << cnt << endl;

  string data = "Nighttable|Desk";

  string first = data.substr(0, data.find('|'));
  string second = data.substr(data.find('|')+1);

  cout << "First: '" << first << endl;
  cout << "Second: '" << second << endl;

}



bool Workstation::attemptToMoveOrder()
	{
		bool Ordermoved = false;
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(Station::getItemName()) || Station::getQuantity() <= 0)
			{
				Ordermoved = true;
				if (m_pNextStation)
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				else
				{
					(m_orders.front().isOrderFilled()) ? g_completed.push_back(std::move(m_orders.front())) : g_incomplete.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
			}
		}
		return Ordermoved;
	}