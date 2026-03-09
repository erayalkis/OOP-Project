#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H

#include <cstddef>

namespace seneca {

class Utils {
public:
   int getInt();
   int getInt(int min, int max);
   char* makeBillFileName(char* filename, size_t billNo) const;
};

extern Utils ut;
}

#endif // !SENECA_UTILS_H
