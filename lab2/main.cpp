#include <iostream>
#include "include/Thirteen.h"

int main() {
   Thirteen num = Thirteen();
   num.print();
   Thirteen num1 = Thirteen({'1', '2', '3'});
   num1.print();
   Thirteen num2 = Thirteen(3, '2');
   num2.print();
   Thirteen num3 = Thirteen("123A");
   num3.print();
   return 0;
}