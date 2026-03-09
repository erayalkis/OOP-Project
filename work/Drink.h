#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"
#include <iostream>
#include <fstream>

namespace seneca {

class Drink {
   Billable m_item;  // name and base price
   char m_size;      // S, M, L, X or 0 if not ordered

public:
   Drink();

   std::ostream& print(std::ostream& ostr = std::cout) const;
   bool order();
   bool ordered() const;
   std::ifstream& read(std::ifstream& file);
   double price() const;
};

std::ostream& operator<<(std::ostream& ostr, const Drink& D);
double& operator+=(double& money, const Drink& D);
double operator+(double money, const Drink& D);

}

#endif // !SENECA_DRINK_H
