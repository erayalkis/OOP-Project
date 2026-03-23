#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca {

class Billable {
protected:
   char* m_name{};
   double m_price{};

   void price(double value);
   void name(const char* name);

public:
   Billable();
   Billable(const Billable& other);
   Billable& operator=(const Billable& other);
   virtual ~Billable();

   virtual double price() const;
   const char* name() const;

   virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
   virtual bool order() = 0;
   virtual bool ordered() const = 0;
   virtual std::ifstream& read(std::ifstream& file) = 0;
};

double& operator+=(double& money, const Billable& B);
double operator+(double money, const Billable& B);

std::ostream& operator<<(std::ostream& ostr, const Billable& B);

}

#endif // !SENECA_BILLABLE_H

