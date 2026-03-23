#include "Billable.h"
#include <cstring>

namespace seneca {

   void Billable::price(double value) {
      m_price = value;
   }

   void Billable::name(const char* src) {
      if (m_name) {
         delete[] m_name;
         m_name = nullptr;
      }
      if (src && src[0]) {
         const size_t len = std::strlen(src);
         m_name = new char[len + 1];
         std::strcpy(m_name, src);
      }
   }

   Billable::Billable() : m_name(nullptr), m_price(0.0) {}

   Billable::Billable(const Billable& other) : m_name(nullptr), m_price(other.m_price) {
      name(other.m_name);
   }

   Billable& Billable::operator=(const Billable& other) {
      if (this != &other) {
         name(other.m_name);
         m_price = other.m_price;
      }
      return *this;
   }

   Billable::~Billable() {
      delete[] m_name;
      m_name = nullptr;
   }

   double Billable::price() const {
      return m_price;
   }

   const char* Billable::name() const {
      return m_name ? m_name : "";
   }

   double& operator+=(double& money, const Billable& B) {
      money += B.price();
      return money;
   }

   double operator+(double money, const Billable& B) {
      return money + B.price();
   }

   std::ostream& operator<<(std::ostream& ostr, const Billable& B) {
      return ostr << B.name();
   }

}

