#include "Food.h"
#include "Menu.h"
#include <cctype>
#include <cstring>
#include <iomanip>
#include <limits>

namespace seneca {

   void Food::setCustomize(const char* text) {
      delete[] m_customize;
      m_customize = nullptr;

      if (!text || !text[0]) return;

      const size_t len = std::strlen(text);
      if (len == 0) return;

      m_customize = new char[len + 1];
      std::strcpy(m_customize, text);
   }

   Food::Food() : Billable(), m_ordered(false), m_child(false), m_customize(nullptr) {}

   Food::Food(const Food& other) : Billable(other), m_ordered(other.m_ordered), m_child(other.m_child) {
      m_customize = nullptr;
      if (other.m_customize) setCustomize(other.m_customize);
   }

   Food& Food::operator=(const Food& other) {
      if (this != &other) {
         Billable::operator=(other);
         m_ordered = other.m_ordered;
         m_child = other.m_child;
         setCustomize(other.m_customize);
      }
      return *this;
   }

   Food::~Food() {
      delete[] m_customize;
      m_customize = nullptr;
   }

   bool Food::ordered() const {
      return m_ordered;
   }

   bool Food::order() {
      Menu portionMenu("Food Size Selection", "Back", 3);
      portionMenu << "Adult" << "Child";

      const size_t sel = portionMenu.select();
      if (sel == 0) {
         m_ordered = false;
         m_child = false;
         delete[] m_customize;
         m_customize = nullptr;
         return false;
      }

      m_ordered = true;
      m_child = (sel == 2);

      std::cout << "Special instructions" << std::endl;
      std::cout << "> ";

      char buffer[256]{};
      std::cin.getline(buffer, 256);

      char* start = buffer;
      while (*start && std::isspace(static_cast<unsigned char>(*start))) ++start;

      char* end = start + std::strlen(start);
      while (end > start &&
             (std::isspace(static_cast<unsigned char>(end[-1])) || end[-1] == '\r'))
         --end;
      *end = '\0';

      if (start[0] == '\0') {
         delete[] m_customize;
         m_customize = nullptr;
      } else {
         setCustomize(start);
      }

      return true;
   }

   std::ifstream& Food::read(std::ifstream& file) {
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

      m_ordered = false;
      m_child = false;
      delete[] m_customize;
      m_customize = nullptr;

      return file;
   }

   double Food::price() const {
      if (ordered() && m_child) {
         return Billable::price() * 0.5;
      }
      return Billable::price();
   }

   std::ostream& Food::print(std::ostream& ostr) const {
      const char* n = name();
      const size_t len = std::strlen(n);

      for (int i = 0; i < 28; ++i) {
         if (i < 25 && static_cast<size_t>(i) < len) ostr << n[i];
         else ostr << '.';
      }

      if (!ordered()) {
         ostr << ".....";
      } else {
         ostr << (m_child ? "Child" : "Adult");
      }

      ostr << std::right << std::fixed << std::setprecision(2) << std::setw(7)
           << price();

      if (m_customize && &ostr == &std::cout) {
         ostr << " >> ";
         for (int i = 0; i < 30 && m_customize[i]; ++i) ostr << m_customize[i];
      }

      return ostr;
   }

}

