#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"
#include <algorithm>
#include <iomanip>


using namespace std;

namespace sdds {

  size_t CustomerOrder::m_widthField = 0;

  CustomerOrder::~CustomerOrder() {
    for(size_t i=0; i<m_cntItem; i++) {
        delete m_lstItem[i];
      }
    delete [] m_lstItem;
    m_lstItem = nullptr;
  }

  CustomerOrder::CustomerOrder(const std::string& str) {
    Utilities u;
    bool more = true;
    size_t next_pos = 0;

    m_name = u.extractToken(str, next_pos, more);
    m_product = u.extractToken(str, next_pos, more);
    cout << "NP: " << next_pos << endl;
    string list = str.substr(next_pos);
    auto cnt = count(list.begin(), list.end(), u.getDelimiter());
    m_lstItem = new Item*[cnt+1];
    m_cntItem = cnt+1;
    size_t i=0;
    while(i < m_cntItem) {
      cout << more << endl;
      Item* temp = new Item(u.extractToken(str, next_pos, more));
      cout << "N: " << next_pos << endl;
      m_lstItem[i] = temp;
      i++;
    }
    for_each(m_lstItem, m_lstItem+m_cntItem, [&]( Item* item){
      cout << item->m_itemName << endl;
    });
    m_widthField = m_widthField > u.getFieldWidth() ? m_widthField: u.getFieldWidth();
  }

  CustomerOrder::CustomerOrder(const CustomerOrder& co) {
    throw "No Copy operations allowed!";
  }

  CustomerOrder:: CustomerOrder(const CustomerOrder&& co) noexcept {
    *this = std::move(co);
  }

  CustomerOrder& CustomerOrder::operator=(const CustomerOrder&& co) noexcept {
    if(this != &co) {
      m_name = co.m_name;
      m_product = co.m_product;
      m_cntItem = co.m_cntItem;
      for(size_t i=0; i<m_cntItem; i++) {
        delete m_lstItem[i];
      }
      delete [] m_lstItem;
      m_lstItem = co.m_lstItem;
    }
    return *this;
  }

  bool CustomerOrder::isOrderFilled() const {
    return (all_of(m_lstItem, m_lstItem+m_cntItem, [=](const Item* i){
      return i->m_isFilled;
    }));
  }

  bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    return (all_of(m_lstItem, m_lstItem+m_cntItem, [=](const Item* i){
      if(i->m_itemName == itemName) {
        return i->m_isFilled;
      }
      return true;
    }));
  }

  void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    if(any_of(m_lstItem, m_lstItem+m_cntItem, [=](const Item* item){
      return (station.getItemName() == item->m_itemName);
    })) {
      for_each(m_lstItem, m_lstItem+m_cntItem, [&]( Item* item){
        if(station.getItemName() == item->m_itemName) {
          if(station.getQuantity() >= 1) {
            station.updateQuantity();
            item->m_isFilled = true;
            item->m_serialNumber = station.getNextSerialNumber();

            os << "Filled " << m_name << ", " << m_product << " [" << item->m_itemName << "]" << endl;
          }
          else {
            os << "Unable to fill " << m_name << ", " << m_product << " [" << item->m_itemName << "]" << endl;
          }
        }
      });
    } 
  }

  void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << endl;
    for_each(m_lstItem, m_lstItem+m_cntItem, [&]( Item* item){
      os << "[" << item->m_serialNumber << "] " << item->m_itemName << " - " << item->m_isFilled << endl;
    });
  }


}