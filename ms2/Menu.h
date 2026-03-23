#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include "constants.h"
#include <iostream>

namespace seneca {

class Menu;

class MenuItem {
   friend class Menu;
private:
   char* m_content;
   unsigned int m_indentCount;
   unsigned int m_indentSize;
   int m_row;

   void setEmpty();
   const char* content() const;
   bool hasContent() const;

public:
   MenuItem(const char* content = nullptr, unsigned int indentCount = 0,
            unsigned int indentSize = 0, int row = -1);
   MenuItem(const MenuItem&) = delete;
   MenuItem& operator=(const MenuItem&) = delete;
   ~MenuItem();

   operator bool() const;
   std::ostream& display(std::ostream& ostr = std::cout) const;
};

class Menu {
   unsigned int m_indentCount;
   unsigned int m_indentSize;
   unsigned int m_numItems;
   MenuItem m_title;
   MenuItem m_exitOption;
   MenuItem m_prompt;
   MenuItem* m_items[MaximumNumberOfMenuItems];

public:
   Menu(const char* title, const char* exitOption = "Exit",
        unsigned int indentCount = 0, unsigned int indentSize = 3);
   Menu(const Menu&) = delete;
   Menu& operator=(const Menu&) = delete;
   ~Menu();

   Menu& operator<<(const char* menuItemContent);
   size_t select() const;
};

size_t operator<<(std::ostream& ostr, const Menu& m);
}

#endif // !SENECA_MENU_H

