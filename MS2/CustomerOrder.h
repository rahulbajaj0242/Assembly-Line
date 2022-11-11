#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include "string.h"
#include "Station.h"

namespace sdds {

  struct Item {
		std::string m_itemName;
		size_t m_serialNumber{0};
		bool m_isFilled{false};

		Item(const std::string& src) : m_itemName(src) {};
};

  class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};

		static size_t m_widthField;

	public:
		CustomerOrder(){};
		~CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& co);
		CustomerOrder& operator=(const CustomerOrder& co) = delete;
		CustomerOrder(const CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(const CustomerOrder&& co) noexcept;
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
  };

}

#endif