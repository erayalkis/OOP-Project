#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include <iostream>
#include <fstream>
#include "constants.h"

namespace seneca {

class Food;
class Drink;
class Billable;

class Ordering {
   Food* m_foods{nullptr};
   Drink* m_drinks{nullptr};
   Billable* m_billItems[MaximumNumberOfBillItems]{};

   size_t m_foodCount{0};
   size_t m_drinkCount{0};
   size_t m_noOfBillItems{0};
   unsigned int m_billNo{1};

   size_t countRecords(const char* file) const;
   void printTotals(std::ostream& ostr, double total) const;
   void printBillTitle(std::ostream& ostr) const;

public:
   Ordering(const char* drinkFile, const char* foodFile);
   ~Ordering();

   Ordering(const Ordering&) = delete;
   Ordering& operator=(const Ordering&) = delete;

   operator bool() const;

   size_t noOfBillItems() const;
   bool hasUnsavedBill() const;

   void listFoods() const;
   void listDrinks() const;

   void orderFood();
   void orderDrink();

   void printBill(std::ostream& ostr) const;
   void resetBill();
};

}

#endif // !SENECA_ORDERING_H

