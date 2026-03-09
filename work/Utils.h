#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H

#include <cstddef>

namespace seneca {
   class Utils {
   public:
      char* alocpy(const char* src) const;
      char* alocpy(char*& des, const char* src) const;
      char* strcpy(char* des, const char* src) const;
      int strlen(const char* str) const;
      bool isspace(char ch) const;
      bool isspace(const char* cstring) const;
      int getInt();
      int getInt(int min, int max);
      char* makeBillFileName(char* filename, size_t billNo) const;
   };
   extern Utils ut;
}

#endif // !SENECA_UTILS_H
