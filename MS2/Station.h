// Name: Rahul Bajaj
// Seneca Student ID: 107707218
// Seneca email: rbajaj12@myseneca.ca
// Date of completion: Nov 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef STATION_H
#define STATION_H
#include "string.h"

namespace sdds {

  class Station {
    int m_id{};
    std::string m_name{};
    std::string m_description{};
    unsigned int m_nextNum{};
    unsigned int m_stock{};
    static size_t m_widthField;
    static int id_generator;

  public:
    Station(const std::string& str);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
  };

}

#endif