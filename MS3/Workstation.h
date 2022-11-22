#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <string>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

  std::deque<CustomerOrder> g_pending;
  std::deque<CustomerOrder> g_completed;
  std::deque<CustomerOrder> g_incomplete;

  class Workstation: public Station {
    std::deque<CustomerOrder> m_order;
    Workstation* m_pNextStation{};

  public:
    Workstation(const std::string& str): Station(str){};
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station =nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
    Workstation(const Workstation& ws) = delete;
    Workstation(Workstation&& ws) = delete;
    Workstation& operator=(const Workstation& ws) = delete;
    Workstation& operator=(Workstation&& ws) = delete;
  };

}

#endif