#include "Utils.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

namespace seneca {

int Utils::getInt() {
   int value = 0;
   while (true) {
      std::string line;
      std::getline(std::cin, line);

      if (line.find_first_not_of(" \t\v\r\f\n") == std::string::npos) {
         std::cout << "You must enter a value: ";
         continue;
      }

      std::istringstream iss(line);
      iss >> value;
      if (iss.fail()) {
         std::cout << "Invalid integer: ";
         continue;
      }

      char remaining;
      if (iss >> remaining) {
         std::cout << "Only an integer please: ";
         continue;
      }

      return value;
   }
}

int Utils::getInt(int min, int max) {
   while (true) {
      const int value = getInt();
      if (value >= min && value <= max) return value;

      std::cout << "Invalid value: [" << min << "<= value <=" << max
                << "], try again: ";
   }
}

char* Utils::makeBillFileName(char* filename, size_t billNo) const {
   char billFileName[21] = "bill_";
   size_t temp = billNo;
   int cnt = 5;
   int length;

   do {
      cnt++;
      temp /= 10;
   } while (temp > 0);

   length = cnt;

   while (billNo > 0) {
      billFileName[--cnt] = (billNo % 10) + '0';
      billNo /= 10;
   }

   if (billFileName[cnt - 1] == '\0') {
      billFileName[--cnt] = '0';
   }

   for (int i = 0; ".txt"[i]; i++) {
      billFileName[length++] = ".txt"[i];
   }

   billFileName[length] = '\0';
   strcpy(filename, billFileName);
   return filename;
}

Utils ut;

}

