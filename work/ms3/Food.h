#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"
#include <iostream>
#include <fstream>

namespace seneca {

class Food {
   Billable m_item;
   bool m_ordered;
   bool m_child;
   char* m_customize;

public:
   Food();
   Food(const Food& other);
   Food& operator=(const Food& other);
   ~Food();

   std::ostream& print(std::ostream& ostr = std::cout) const;
   bool order();
   bool ordered() const;
   std::ifstream& read(std::ifstream& file);
   double price() const;
};

std::ostream& operator<<(std::ostream& ostr, const Food& F);
double& operator+=(double& money, const Food& F);
double operator+(double money, const Food& F);

}

#endif // !SENECA_FOOD_H
