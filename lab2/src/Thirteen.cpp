#include "../include/Thirteen.h"

Thirteen::Thirteen() : digits(nullptr), length(0) {}

Thirteen::Thirteen(const size_t& n) : digits(new unsigned char[n]), length(n) {}

Thirteen::Thirteen(const size_t& n, unsigned char t)
    : digits(new unsigned char[n]), length(n) {
   if (!validate(t)) {
      throw std::invalid_argument("Invalid number format");
   }

   for (int i = 0; i < n; i++) {
      digits[i] = charToInt(t);
   }
}

Thirteen::Thirteen(const std::initializer_list<unsigned char>& t) {
   if (!validate(t)) {
      throw std::invalid_argument("Invalid number format");
   }

   length = t.size();
   digits = new unsigned char[t.size()];
   size_t i = 0;

   for (unsigned char c : t) {
      digits[length - i - 1] = charToInt(c);
      i++;
   }
}

Thirteen::Thirteen(const std::string& t) {
   if (!validate(t)) {
      throw std::invalid_argument("Invalid number format");
   }

   length = t.size();
   digits = new unsigned char[t.size()];
   for (size_t i = 0; i < length; i++) {
      digits[length - i - 1] = charToInt(t[i]);
   }
}

Thirteen::Thirteen(const Thirteen& other) { deepCopy(other); }

Thirteen::Thirteen(Thirteen&& other) noexcept
    : length(other.length), digits(other.digits) {
   other.length = 0;
   other.digits = nullptr;
}

void Thirteen::clear() {
   delete[] digits;
   length = 0;
   digits = nullptr;
}

Thirteen::~Thirteen() { clear(); }

void Thirteen::print() const {
   std::cout << "[ ";
   for (size_t i = 0; i < length; i++) {
      std::cout << intToChar(digits[length - i - 1]);
   }
   std::cout << " ]" << std::endl;
}

std::string Thirteen::toString() const {
   std::string result = "";
   for (size_t i = 0; i < length; i++) {
      result += intToChar(digits[length - i - 1]);
   }
   return result;
}

unsigned long long Thirteen::toDecimal() const {
   unsigned long long result = 0;
   unsigned long long power = 1;
   for (size_t i = 0; i < length; i++) {
      result += (unsigned long long)digits[i] * power;
      power *= 13;
   }
   return result;
}

size_t Thirteen::size() const { return length; }

void Thirteen::removeLeadingZeros() {
   while (digits[length - 1] == 0 && length > 1) {
      --length;
   }
}

void Thirteen::deepCopy(const Thirteen& other) {
   length = other.length;
   digits = new unsigned char[length];
   std::copy(other.digits, other.digits + other.length, digits);
}

Thirteen& Thirteen::operator=(const Thirteen& other) {
   if (this != &other) {
      clear();
      deepCopy(other);
   }
   return *this;
}

Thirteen& Thirteen::operator=(Thirteen&& other) noexcept {
   if (this != &other) {
      delete[] digits;
      length = other.length;
      digits = other.digits;
      other.length = 0;
      other.digits = nullptr;
   }
   return *this;
}

Thirteen Thirteen::operator+(const Thirteen& other) const {
   size_t maxSize = length > other.length ? length : other.length;
   Thirteen result = Thirteen(maxSize + 1, '0');
   unsigned int newDigit;
   for (size_t i = 0; i < maxSize; i++) {
      unsigned char leftDigit = digits[i], rightDigit = other.digits[i];
      if (length <= i) {
         leftDigit = 0;
      }
      if (other.size() <= i) {
         rightDigit = 0;
      }
      newDigit = leftDigit + rightDigit;
      result.digits[i + 1] += newDigit / 13;
      result.digits[i] = newDigit % 13;
   }

   result.removeLeadingZeros();
   return result;
}

Thirteen Thirteen::operator-(const Thirteen& other) const {
   if (*this < other) {
      throw std::range_error("Negative values not supported");
   }
   Thirteen result = Thirteen(*this);
   result.print();

   for (size_t i = 0; i < length; i++) {
      unsigned char &leftDigit = result.digits[i],
                    &rightDigit = other.digits[i];
      if (length <= i) {
         leftDigit = 0;
      }
      if (other.size() <= i) {
         rightDigit = 0;
      }
      if (result.digits[i] < other.digits[i]) {
         result.digits[i + 1] -= 1;
         result.digits[i] += 13;
      }
      result.digits[i] -= other.digits[i];
   }

   result.removeLeadingZeros();
   return result;
}

Thirteen Thirteen::operator*(const Thirteen& other) const {
   size_t maxSize = length + other.length;
   Thirteen result = Thirteen(maxSize, '0');

   for (size_t i = 0; i < length; i++) {
      unsigned char carry_digit = 0;
      for (size_t j = 0; j < other.length; ++j) {
         unsigned char product =
             result.digits[i + j] + carry_digit + digits[i] * other.digits[j];
         result.digits[i + j] = product % 13;
         carry_digit = product / 13;
      }
      if (carry_digit > 0) {
         result.digits[i + other.length] = carry_digit;
      }
   }

   result.removeLeadingZeros();
   return result;
}

bool Thirteen::operator==(const Thirteen& other) const {
   if (length != other.length) return false;

   for (size_t i = 0; i < length; ++i) {
      if (digits[i] != other.digits[i]) return false;
   }
   return true;
}

bool Thirteen::operator!=(const Thirteen& other) const {
   return !(*this == other);
}

bool Thirteen::operator<(const Thirteen& other) const {
   if (length != other.length) return length < other.length;

   for (size_t i = length; i > 0; --i) {
      if (digits[i - 1] != other.digits[i - 1])
         return digits[i - 1] < other.digits[i - 1];
   }
   return false;
}

bool Thirteen::operator>(const Thirteen& other) const { return other < *this; }

bool Thirteen::operator<=(const Thirteen& other) const {
   return !(other < *this);
}

bool Thirteen::operator>=(const Thirteen& other) const {
   return !(*this < other);
}

Thirteen& Thirteen::operator+=(const Thirteen& other) {
   *this = *this + other;
   return *this;
}

Thirteen& Thirteen::operator-=(const Thirteen& other) {
   *this = *this - other;
   return *this;
}

Thirteen& Thirteen::operator*=(const Thirteen& other) {
   *this = *this * other;
   return *this;
}