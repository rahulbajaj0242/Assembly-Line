// Name: Rahul Bajaj
// Seneca Student ID: 107707218
// Seneca email: rbajaj12@myseneca.ca
// Date of completion: Nov 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include <string>
#include <deque>
#include <vector>
#include "CustomerOrder.h"
#include "Workstation.h"

namespace sdds {

  class LineManager {

    std::vector<Workstation*> m_activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;

  public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
  };


}


#endif