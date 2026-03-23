#include "Menu.h"
#include "Utils.h"
#include <cstring>
#include <cctype>

namespace seneca {

static void skipLeadingWhitespace(const char*& str) {
   while (*str && std::isspace(static_cast<unsigned char>(*str)))
      str++;
}

void MenuItem::setEmpty() {
   delete[] m_content;
   m_content = nullptr;
   m_indentCount = 0;
   m_indentSize = 0;
   m_row = -1;
}

const char* MenuItem::content() const {
   return m_content;
}

bool MenuItem::hasContent() const {
   if (!m_content) return false;
   const char* p = m_content;
   skipLeadingWhitespace(p);
   return *p != '\0';
}

MenuItem::MenuItem(const char* content, unsigned int indentCount,
                     unsigned int indentSize, int row) :
   m_content(nullptr), m_indentCount(0), m_indentSize(0), m_row(-1) {
   if (!content) {
      setEmpty();
      return;
   }
   const char* p = content;
   skipLeadingWhitespace(p);
   if (*p == '\0') {
      setEmpty();
      return;
   }
   if (indentCount > 4 || indentSize > 4) {
      setEmpty();
      return;
   }
   if (row > static_cast<int>(MaximumNumberOfMenuItems)) {
      setEmpty();
      return;
   }
   m_content = new char[std::strlen(p) + 1];
   std::strcpy(m_content, p);
   m_indentCount = indentCount;
   m_indentSize = indentSize;
   m_row = row;
}

MenuItem::~MenuItem() {
   delete[] m_content;
   m_content = nullptr;
}

MenuItem::operator bool() const {
   return hasContent();
}

std::ostream& MenuItem::display(std::ostream& ostr) const {
   if (!hasContent()) {
      ostr << "??????????";
      return ostr;
   }
   for (unsigned int i = 0; i < m_indentCount * m_indentSize; i++)
      ostr << ' ';
   if (m_row >= 0) {
      ostr.width(2);
      ostr.setf(std::ios::right);
      ostr << m_row << "- ";
      ostr.unsetf(std::ios::right);
   }
   ostr << m_content;
   return ostr;
}

Menu::Menu(const char* title, const char* exitOption,
           unsigned int indentCount, unsigned int indentSize) :
   m_indentCount(indentCount),
   m_indentSize(indentSize),
   m_numItems(0),
   m_title(title, indentCount, indentSize, -1),
   m_exitOption(exitOption, indentCount, indentSize, 0),
   m_prompt("> ", indentCount, indentSize, -1) {
   for (unsigned int i = 0; i < MaximumNumberOfMenuItems; i++)
      m_items[i] = nullptr;
}

Menu::~Menu() {
   for (unsigned int i = 0; i < m_numItems; i++) {
      delete m_items[i];
      m_items[i] = nullptr;
   }
}

Menu& Menu::operator<<(const char* menuItemContent) {
   if (m_numItems < MaximumNumberOfMenuItems && menuItemContent) {
      m_items[m_numItems] =
         new MenuItem(menuItemContent, m_indentCount, m_indentSize,
                      static_cast<int>(m_numItems + 1));
      m_numItems++;
   }
   return *this;
}

size_t Menu::select() const {
   if (m_title)
      m_title.display() << std::endl;
   for (unsigned int i = 0; i < m_numItems; i++)
      m_items[i]->display() << std::endl;
   m_exitOption.display() << std::endl;
   m_prompt.display();
   return static_cast<size_t>(ut.getInt(0, static_cast<int>(m_numItems)));
}

size_t operator<<(std::ostream& ostr, const Menu& m) {
   if (&ostr == &std::cout)
      return m.select();
   return 0;
}

}

