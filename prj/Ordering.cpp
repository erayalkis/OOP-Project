#include "Ordering.h"
#include "Utils.h"
#include "Menu.h"
#include "Billable.h"
#include "Food.h"
#include "Drink.h"

#include <iomanip>
#include <limits>

namespace seneca {

   size_t Ordering::countRecords(const char* file) const {
      std::ifstream in(file);
      if (!in) return 0;
      size_t count = 0;
      char ch{};
      while (in.get(ch)) {
         if (ch == '\n') ++count;
      }
      return count;
   }

   void Ordering::printBillTitle(std::ostream& ostr) const {
      ostr << "Bill # " << std::setw(3) << std::setfill('0') << m_billNo
           << std::setfill(' ') << " =============================" << std::endl;
   }

   void Ordering::printTotals(std::ostream& ostr, double total) const {
      const double tax = total * Tax;
      ostr << "                     Total: " << std::setw(12) << std::fixed
           << std::setprecision(2) << total << std::endl;
      ostr << "                     Tax: " << std::setw(14) << std::fixed
           << std::setprecision(2) << tax << std::endl;
      ostr << "                     Total+Tax: " << std::setw(8) << std::fixed
           << std::setprecision(2) << (total + tax) << std::endl;
      ostr << "========================================" << std::endl;
   }

   Ordering::Ordering(const char* drinkFile, const char* foodFile) {
      if (!drinkFile || !foodFile) return;

      m_foodCount = countRecords(foodFile);
      m_drinkCount = countRecords(drinkFile);

      std::ifstream drinks(drinkFile);
      std::ifstream foods(foodFile);

      if (!drinks || !foods || m_foodCount == 0 || m_drinkCount == 0) {
         return;
      }

      m_foods = new Food[m_foodCount];
      m_drinks = new Drink[m_drinkCount];

      size_t i = 0;
      for (; i < m_drinkCount && drinks; ++i) {
         m_drinks[i].read(drinks);
      }
      const bool drinksOk = (i == m_drinkCount);

      i = 0;
      for (; i < m_foodCount && foods; ++i) {
         m_foods[i].read(foods);
      }
      const bool foodsOk = (i == m_foodCount);

      if (!drinksOk || !foodsOk) {
         delete[] m_drinks;
         delete[] m_foods;
         m_drinks = nullptr;
         m_foods = nullptr;
         m_foodCount = 0;
         m_drinkCount = 0;
         m_noOfBillItems = 0;
         return;
      }

      for (size_t k = 0; k < MaximumNumberOfBillItems; ++k) {
         m_billItems[k] = nullptr;
      }
   }

   Ordering::~Ordering() {
      for (size_t i = 0; i < m_noOfBillItems; ++i) {
         delete m_billItems[i];
         m_billItems[i] = nullptr;
      }
      delete[] m_foods;
      delete[] m_drinks;
      m_foods = nullptr;
      m_drinks = nullptr;
   }

   Ordering::operator bool() const {
      return m_foods != nullptr && m_drinks != nullptr;
   }

   size_t Ordering::noOfBillItems() const {
      return m_noOfBillItems;
   }

   bool Ordering::hasUnsavedBill() const {
      return m_noOfBillItems > 0;
   }

   void Ordering::listFoods() const {
      if (!*this) return;

      std::cout << "List Of Avaiable Meals" << std::endl;
      std::cout << "========================================" << std::endl;
      for (size_t i = 0; i < m_foodCount; ++i) {
         m_foods[i].print(std::cout) << std::endl;
      }
      std::cout << "========================================" << std::endl;
   }

   void Ordering::listDrinks() const {
      if (!*this) return;

      std::cout << "List Of Avaiable Drinks" << std::endl;
      std::cout << "========================================" << std::endl;
      for (size_t i = 0; i < m_drinkCount; ++i) {
         m_drinks[i].print(std::cout) << std::endl;
      }
      std::cout << "========================================" << std::endl;
   }

   void Ordering::orderFood() {
      if (!*this) return;

      Menu menu("Food Menu", "Back to Order", 2);
      for (size_t i = 0; i < m_foodCount; ++i) {
         menu << m_foods[i].name();
      }

      const size_t selection = menu.select();
      if (selection == 0) return;

      if (m_noOfBillItems >= MaximumNumberOfBillItems) return;

      Food* ordered = new Food(m_foods[selection - 1]);
      if (ordered->order()) {
         m_billItems[m_noOfBillItems++] = ordered;
      } else {
         delete ordered;
      }
   }

   void Ordering::orderDrink() {
      if (!*this) return;

      Menu menu("Drink Menu", "Back to Order", 2);
      for (size_t i = 0; i < m_drinkCount; ++i) {
         menu << m_drinks[i].name();
      }

      const size_t selection = menu.select();
      if (selection == 0) return;

      if (m_noOfBillItems >= MaximumNumberOfBillItems) return;

      Drink* ordered = new Drink(m_drinks[selection - 1]);
      if (ordered->order()) {
         m_billItems[m_noOfBillItems++] = ordered;
      } else {
         delete ordered;
      }
   }

   void Ordering::printBill(std::ostream& ostr) const {
      if (!*this) return;

      double total = 0.0;
      printBillTitle(ostr);

      for (size_t i = 0; i < m_noOfBillItems; ++i) {
         m_billItems[i]->print(ostr) << std::endl;
         total += m_billItems[i]->price();
      }

      printTotals(ostr, total);
   }

   void Ordering::resetBill() {
      if (!*this) return;

      char billFileName[64]{};
      ut.makeBillFileName(billFileName, m_billNo);

      std::ofstream ofs(billFileName);
      if (ofs) {
         printBill(ofs);
      }

      std::cout << "Saved bill number " << m_billNo << std::endl;
      ++m_billNo;

      for (size_t i = 0; i < m_noOfBillItems; ++i) {
         delete m_billItems[i];
         m_billItems[i] = nullptr;
      }
      m_noOfBillItems = 0;

      std::cout << "Starting bill number " << m_billNo << std::endl;
   }

}

