#include "../include/Thirteen.h"

bool validate(const std::initializer_list<unsigned char>& t) {
   for (unsigned char c : t) {
      if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'C'))) {
         return false;
      }
   }
   return true;
}

bool validate(const std::string& t) {
   for (unsigned char c : t) {
      if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'C'))) {
         return false;
      }
   }
   return true;
}

bool validate(const unsigned char& t) {
   if (!((t >= '0' && t <= '9') || (t >= 'A' && t <= 'C'))) {
      return false;
   }

   return true;
}

unsigned int charToInt(const unsigned char& item) {
   switch (item) {
      case 'A':
         return 10;
      case 'B':
         return 11;
      case 'C':
         return 12;
      default:
         return (unsigned int)(item - '0');
   }
}

unsigned char intToChar(const unsigned int& item) {
   switch (item) {
      case 10:
         return 'A';
      case 11:
         return 'B';
      case 12:
         return 'C';
      default:
         return (unsigned char)('0' + item);
   }
}