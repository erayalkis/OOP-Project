#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace seneca {

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
      return !ut.isspace(m_content);
   }

   MenuItem::MenuItem(const char* content, unsigned int indentCount,
                     unsigned int indentSize, int row) :
      m_content(nullptr), m_indentCount(0), m_indentSize(0), m_row(-1) {
      if (!content) {
         setEmpty();
         return;
      }
      const char* p = content;
      while (*p && ut.isspace(*p)) p++;
      if (*p == '\0') {
         setEmpty();
         return;
      }
      if (indentCount > 4 || indentSize > 4) {
         setEmpty();
         return;
      }
      if (row > (int)MaximumNumberOfMenuItems) {
         setEmpty();
         return;
      }
      ut.alocpy(m_content, p);
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

   ostream& MenuItem::display(ostream& ostr) const {
      if (!hasContent()) {
         ostr << "??????????";
         return ostr;
      }
      for (unsigned int i = 0; i < m_indentCount * m_indentSize; i++)
         ostr << ' ';
      if (m_row >= 0) {
         ostr.width(2);
         ostr.setf(ios::right);
         ostr << m_row << "- ";
         ostr.unsetf(ios::right);
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
         m_items[m_numItems] = new MenuItem(menuItemContent, m_indentCount,
                                           m_indentSize, (int)(m_numItems + 1));
         m_numItems++;
      }
      return *this;
   }

   size_t Menu::select() const {
      if (m_title)
         m_title.display() << endl;
      for (unsigned int i = 0; i < m_numItems; i++)
         m_items[i]->display() << endl;
      m_exitOption.display() << endl;
      m_prompt.display();
      return (size_t)ut.getInt(0, (int)m_numItems);
   }

   size_t operator<<(ostream& ostr, const Menu& m) {
      if (&ostr == &cout)
         return m.select();
      return 0;
   }
}
