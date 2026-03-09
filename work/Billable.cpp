#include "Billable.h"
#include "Utils.h"
using namespace std;
namespace seneca {

   void Billable::setPrice(double value) {
      m_price = value;
   }

   void Billable::setName(const char* n) {
      if (n && n[0]) {
         ut.alocpy(m_name, n);
      } else {
         delete[] m_name;
         m_name = nullptr;
      }
   }

   Billable::Billable() : m_name(nullptr), m_price(0.0) {}

   Billable::Billable(const Billable& other) : m_name(nullptr), m_price(other.m_price) {
      ut.alocpy(m_name, other.m_name);
   }

   Billable& Billable::operator=(const Billable& other) {
      if (this != &other) {
         ut.alocpy(m_name, other.m_name);
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
}
