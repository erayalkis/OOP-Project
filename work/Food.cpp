#include "Food.h"
#include "Menu.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>
using namespace std;
namespace seneca {

   Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {}

   Food::Food(const Food& other)
      : m_item(other.m_item), m_ordered(other.m_ordered), m_child(other.m_child), m_customize(nullptr) {
      ut.alocpy(m_customize, other.m_customize);
   }

   Food& Food::operator=(const Food& other) {
      if (this != &other) {
         m_item = other.m_item;
         m_ordered = other.m_ordered;
         m_child = other.m_child;
         ut.alocpy(m_customize, other.m_customize);
      }
      return *this;
   }

   Food::~Food() {
      delete[] m_customize;
      m_customize = nullptr;
   }

   ostream& Food::print(ostream& ostr) const {
      const char* n = m_item.name();
      for (int i = 0; i < 28; i++) {
         if (i < 25 && n[i])
            ostr << n[i];
         else
            ostr << '.';
      }
      if (m_ordered)
         ostr << (m_child ? "Child" : "Adult");
      else
         ostr << ".....";
      ostr << right << fixed << setprecision(2) << setw(7) << price();
      if (m_customize && &ostr == &cout) {
         ostr << " >> ";
         for (int i = 0; i < 30 && m_customize[i]; i++)
            ostr << m_customize[i];
      }
      return ostr;
   }

   bool Food::order() {
      Menu portionMenu("Food Size Selection", "Back", 3);
      portionMenu << "Adult" << "Child";
      int sel = (int)portionMenu.select();
      if (sel == 0) {
         m_ordered = false;
         m_child = false;
         delete[] m_customize;
         m_customize = nullptr;
         return false;
      }
      m_ordered = true;
      m_child = (sel == 2);
      delete[] m_customize;
      m_customize = nullptr;
      cout << "Special instructions" << endl << "> ";
      char buf[256];
      cin.getline(buf, 256);
      int i = 0;
      while (buf[i] && ut.isspace(buf[i])) i++;
      if (buf[i]) {
         int len = ut.strlen(buf);
         while (len > i && ut.isspace(buf[len - 1])) len--;
         buf[len] = '\0';
         ut.alocpy(m_customize, buf + i);
      }
      return true;
   }

   bool Food::ordered() const {
      return m_ordered;
   }

   ifstream& Food::read(ifstream& file) {
      char buf[256];
      double p = 0;
      if (file.getline(buf, 256, ',')) {
         const char* start = buf;
         while (*start == ' ') start++;
         char* end = buf + ut.strlen(buf);
         while (end > start && (end[-1] == ' ' || end[-1] == '\r')) *--end = '\0';
         if (*start) {
            m_item.setName(start);
            file >> p;
            file.ignore();
            m_item.setPrice(p);
            m_ordered = false;
            m_child = false;
            delete[] m_customize;
            m_customize = nullptr;
         }
      }
      return file;
   }

   double Food::price() const {
      double base = m_item.price();
      if (m_ordered && m_child)
         return base * 0.5;
      return base;
   }

   ostream& operator<<(ostream& ostr, const Food& F) {
      return F.print(ostr);
   }

   double& operator+=(double& money, const Food& F) {
      money += F.price();
      return money;
   }

   double operator+(double money, const Food& F) {
      return money + F.price();
   }
}
