#include <iostream>
#include "workstation.h"
#include "Utilities.h"
#include <iomanip>

#include "sstream"

using namespace std;

namespace sdds {

  void Workstation::fill(std::ostream& os) {
    if(!m_order.empty()) {
      m_order.front().fillItem(*this, os);
    }
  }

  bool Workstation::attemptToMoveOrder() {
    if(m_order.front().isOrderFilled() || this->getQuantity() < 1) {
      if(m_pNextStation == nullptr) {
        if(m_order.front().isOrderFilled()) {
          g_completed.push_back(m_order.front());
        }
        else {
          g_incomplete.push_back(m_order.front());
        }
        m_order.pop_front();
      }
      else {
        *m_pNextStation += std::move(m_order.front());
        m_order.pop_front();
      }
      return true;
    }
    return false;
  }

  void Workstation::setNextStation(Workstation* station) {
    m_pNextStation = station;
  }

  Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
  } 

  void Workstation::display(std::ostream& os) const {
    os<< this->getItemName() << " --> ";
    if(m_pNextStation) {
      os << m_pNextStation->getItemName() << endl;;
    }
    else {
      os << "End of Line" << endl;
    }
  }

  Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
    m_order.push_back(newOrder);
  }


}