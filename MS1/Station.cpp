#include <iostream>
#include "Station.h"
#include "Utilities.h"
#include <iomanip>

#include "sstream"

using namespace std;

namespace sdds {

  size_t Station::m_widthField = 0;
  int Station::id_generator = 0;

  Station::Station(const std::string& str) {
    Utilities u;
    bool more = true;
    size_t next_pos = 0;

    if(str.length() != 0) {

      if(id_generator == 0) id_generator++;
      m_id = id_generator;
      id_generator++;

      m_name = u.extractToken(str, next_pos, more);

      string num = u.extractToken(str, next_pos, more);
      m_nextNum = stoi(num);

      string stock = u.extractToken(str, next_pos, more);
      m_stock = stoi(stock);

      m_widthField = m_widthField > u.getFieldWidth() ? m_widthField: u.getFieldWidth();

      m_description = u.extractToken(str, next_pos, more);
    }
  }

  const std::string& Station::getItemName() const {
    return m_name;
  }

  size_t Station::getNextSerialNumber() {
    int temp = m_nextNum;
    m_nextNum++;
    return temp;
  }

  size_t Station::getQuantity() const {
    return m_stock;
  }

  void Station::updateQuantity() {
    if(m_stock != 0) {
      m_stock--;
    }
  }

  void Station::display(std::ostream& os, bool full) const {
    if(!full) {
      os << setfill('0') << setw(3) << right<< m_id  << " | " << setfill(' ') << setw(m_widthField) << left << m_name << " | " << setw(6) << left <<  m_nextNum << " |";
    }
    else {
      os << setw(3) << left << m_id << " | " << setw(m_widthField) << left << m_name << " | " << setw(6) << left <<  m_nextNum << " | " << right << setw(4) << m_stock << " | " <<  left << m_description;
    }
    os << endl;
  }

}