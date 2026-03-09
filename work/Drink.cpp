#include "Drink.h"
#include "Menu.h"
#include "Utils.h"
#include <iomanip>
using namespace std;
namespace seneca {

   Drink::Drink() : m_size(0) {}

   ostream& Drink::print(ostream& ostr) const {
      const char* n = m_item.name();
      for (int i = 0; i < 28; i++) {
         if (i < 25 && n[i])
            ostr << n[i];
         else
            ostr << '.';
      }
      switch (m_size) {
         case 'S': ostr << "SML.."; break;
         case 'M': ostr << "MID.."; break;
         case 'L': ostr << "LRG.."; break;
         case 'X': ostr << "XLR.."; break;
         default:  ostr << "....."; break;
      }
      ostr << right << fixed << setprecision(2) << setw(7) << price();
      return ostr;
   }

   bool Drink::order() {
      Menu sizeMenu("Drink Size Selection", "Back", 3);
      sizeMenu << "Small" << "Medium" << "Larg" << "Extra Large";
      int sel = (int)sizeMenu.select();
      if (sel == 0) {
         m_size = 0;
         return false;
      }
      switch (sel) {
         case 1: m_size = 'S'; break;
         case 2: m_size = 'M'; break;
         case 3: m_size = 'L'; break;
         case 4: m_size = 'X'; break;
      }
      return true;
   }

   bool Drink::ordered() const {
      return m_size != 0;
   }

   ifstream& Drink::read(ifstream& file) {
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
            m_size = 0;
         }
      }
      return file;
   }

   double Drink::price() const {
      double base = m_item.price();
      if (!ordered()) return base;
      switch (m_size) {
         case 'S': return base * 0.5;
         case 'M': return base * 0.75;
         case 'L': return base;
         case 'X': return base * 1.5;
         default:  return base;
      }
   }

   ostream& operator<<(ostream& ostr, const Drink& D) {
      return D.print(ostr);
   }

   double& operator+=(double& money, const Drink& D) {
      money += D.price();
      return money;
   }

   double operator+(double money, const Drink& D) {
      return money + D.price();
   }
}
