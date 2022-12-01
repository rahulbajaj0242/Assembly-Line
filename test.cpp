#include <iostream>
#include <string.h>
#include "sstream"
using namespace std;



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

  // string data = "Nighttable|Desk";

  // string first = data.substr(0, data.find('|'));
  // string second = data.substr(data.find('|')+1);

  // cout << "First: '" << first << endl;
  // cout << "Second: '" << second << endl;

  unsigned int a = 1; 
unsigned int b = 2;  
unsigned int c = 3;  
unsigned int d = 4;  
unsigned int e = 5;

a <<= 2;  
b >>= 0;  
c = a & b;  
d = a ^ b;  
e = c | d;

cout << b;

}


