#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca {

class Billable {
   char* m_name;
   double m_price;

public:
   void setPrice(double value);
   void setName(const char* name);
   Billable();
   Billable(const Billable& other);
   Billable& operator=(const Billable& other);
   ~Billable();

   double price() const;
   const char* name() const;
};

}

#endif // !SENECA_BILLABLE_H
