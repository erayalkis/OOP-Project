#include "Drink.h"
#include "Menu.h"
#include <iomanip>
#include <cctype>
#include <cstring>
#include <limits>

namespace seneca {

   Drink::Drink() : Billable(), m_size('\0') {}

   bool Drink::ordered() const {
      return m_size != '\0';
   }

   bool Drink::order() {
      Menu menu("Drink Size Selection", "Back", 3);
      menu << "Small" << "Medium" << "Larg" << "Extra Large";

      const size_t sel = menu.select();
      if (sel == 0) {
         m_size = '\0';
         return false;
      }

      switch (sel) {
         case 1: m_size = 'S'; break;
         case 2: m_size = 'M'; break;
         case 3: m_size = 'L'; break;
         case 4: m_size = 'X'; break;
         default: m_size = '\0'; return false;
      }
      return true;
   }

   std::ifstream& Drink::read(std::ifstream& file) {
      char buffer[256]{};
      if (!file.getline(buffer, 256, ',')) return file;

      char* start = buffer;
      while (*start && std::isspace(static_cast<unsigned char>(*start))) ++start;

      char* end = start + std::strlen(start);
      while (end > start &&
             (std::isspace(static_cast<unsigned char>(end[-1])) || end[-1] == '\r'))
         --end;
      *end = '\0';

      double p{};
      if (!(file >> p)) return file;
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      Billable::name(start);
      Billable::price(p);
      m_size = '\0';
      return file;
   }

   double Drink::price() const {
      if (!ordered()) return Billable::price();

      switch (m_size) {
         case 'S': return Billable::price() * 0.5;
         case 'M': return Billable::price() * 0.75;
         case 'L': return Billable::price();
         case 'X': return Billable::price() * 1.5;
         default: return Billable::price();
      }
   }

   std::ostream& Drink::print(std::ostream& ostr) const {
      const char* n = name();
      const size_t len = std::strlen(n);

      for (int i = 0; i < 28; ++i) {
         if (i < 25 && static_cast<size_t>(i) < len) ostr << n[i];
         else ostr << '.';
      }

      if (!ordered()) ostr << ".....";
      else {
         switch (m_size) {
            case 'S': ostr << "SML.."; break;
            case 'M': ostr << "MID.."; break;
            case 'L': ostr << "LRG.."; break;
            case 'X': ostr << "XLR.."; break;
            default:  ostr << "....."; break;
         }
      }

      ostr << std::right << std::fixed << std::setprecision(2) << std::setw(7)
           << price();
      return ostr;
   }

}

