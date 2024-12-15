#include "../include/Thirteen.h"
#include <gtest/gtest.h>

TEST(ConstructorTest, BasicConstructor) {
   Thirteen obj1 = Thirteen();

   ASSERT_EQ(obj1.size(), (size_t)0);
   ASSERT_EQ(obj1.toString(), "");
}

TEST(ConstructorTest, ListConstructor) {
   Thirteen obj1 = Thirteen({'1', '2', '3'});
   obj1.print();

   ASSERT_EQ(obj1.size(), (size_t)3);
   ASSERT_EQ(obj1.toString(), "123");
}

TEST(ConstructorTest, StringConstructor) {
   Thirteen obj1 = Thirteen("123A");

   ASSERT_EQ(obj1.size(), (size_t)4);
   ASSERT_EQ(obj1.toString(), "123A");
}

TEST(ConstructorTest, CopyConstructor) {
   Thirteen obj1 = Thirteen("123AC");
   Thirteen obj2 = Thirteen(obj1);

   ASSERT_EQ(obj2.size(), (size_t)5);
   ASSERT_EQ(obj2.toString(), "123AC");
}

TEST(UtilsTest, ToDecimal) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   ASSERT_EQ(obj1.toDecimal(), 1);
   ASSERT_EQ(obj2.toDecimal(), 15);
   ASSERT_EQ(obj3.toDecimal(), 23);
}

TEST(UtilsTest, CharToInt) {
   unsigned char c1 = 'A', c2 = '1', c3 = '5';

   ASSERT_EQ(charToInt(c1), 10);
   ASSERT_EQ(charToInt(c2), 1);
   ASSERT_EQ(charToInt(c3), 5);
}

TEST(UtilsTest, IntToChar) {
   unsigned int c1 = 10, c2 = 1, c3 = 5;

   ASSERT_EQ(intToChar(c1), 'A');
   ASSERT_EQ(intToChar(c2), '1');
   ASSERT_EQ(intToChar(c3), '5');
}

TEST(OperatorsTest, AssignOperator) {
   Thirteen obj1 = Thirteen("123AC");
   Thirteen obj2 = obj1;

   ASSERT_EQ(obj2.size(), (size_t)5);
   ASSERT_EQ(obj2.toString(), "123AC");
}

TEST(OperatorsTest, MoveOperator) {
   Thirteen obj1 = Thirteen("123AC");
   Thirteen obj2 = std::move(obj1);

   ASSERT_EQ(obj1.size(), (size_t)0);
   ASSERT_EQ(obj1.toString(), "");
   ASSERT_EQ(obj2.size(), (size_t)5);
   ASSERT_EQ(obj2.toString(), "123AC");
}

TEST(OperatorsTest, SumOperator) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   Thirteen result1 = obj1 + obj2;
   Thirteen result2 = obj1 + obj3;
   Thirteen result3 = obj2 + obj3;

   ASSERT_EQ(result1.toDecimal(), 16);
   ASSERT_EQ(result2.toDecimal(), 24);
   ASSERT_EQ(result3.toDecimal(), 38);
}

TEST(OperatorsTest, SubOperator) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   Thirteen result1 = obj2 - obj1;
   Thirteen result2 = obj3 - obj1;
   Thirteen result3 = obj3 - obj2;

   ASSERT_EQ(result1.toDecimal(), 14);
   ASSERT_EQ(result2.toDecimal(), 22);
   ASSERT_EQ(result3.toDecimal(), 8);
}

TEST(OperatorsTest, MultOperator) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   Thirteen result1 = obj2 * obj1;
   Thirteen result2 = obj3 * obj1;
   Thirteen result3 = obj3 * obj2;

   ASSERT_EQ(result1.toDecimal(), 15);
   ASSERT_EQ(result2.toDecimal(), 23);
   ASSERT_EQ(result3.toDecimal(), 345);
}

TEST(OperatorsTest, SumEqOperator) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   obj2 += obj1;
   obj3 += obj1;

   ASSERT_EQ(obj2.toDecimal(), 16);
   ASSERT_EQ(obj3.toDecimal(), 24);
}

TEST(OperatorsTest, SubEqOperator) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   obj2 -= obj1;
   obj3 -= obj2;

   ASSERT_EQ(obj2.toDecimal(), 14);
   ASSERT_EQ(obj3.toDecimal(), 9);
}

TEST(OperatorsTest, MultEqOperator) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   obj2 *= obj1;
   obj3 *= obj2;

   ASSERT_EQ(obj2.toDecimal(), 15);
   ASSERT_EQ(obj3.toDecimal(), 345);
}

TEST(OperatorsTest, GreaterTest) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   ASSERT_TRUE(obj2 > obj1);
   ASSERT_TRUE(obj3 > obj1);
   ASSERT_TRUE(obj3 > obj2);
}

TEST(OperatorsTest, GreaterEqTest) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   ASSERT_TRUE(obj2 >= obj1);
   ASSERT_TRUE(obj3 >= obj1);
   ASSERT_TRUE(obj3 >= obj3);
}

TEST(OperatorsTest, LessTest) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   ASSERT_TRUE(obj1 < obj2);
   ASSERT_TRUE(obj1 < obj3);
   ASSERT_TRUE(obj2 < obj3);
}

TEST(OperatorsTest, LessEqTest) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");
   Thirteen obj3 = Thirteen("1A");

   ASSERT_TRUE(obj1 <= obj2);
   ASSERT_TRUE(obj1 <= obj3);
   ASSERT_TRUE(obj3 <= obj3);
}

TEST(OperatorsTest, EqTest) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");

   ASSERT_FALSE(obj1 == obj2);
   ASSERT_TRUE(obj2 == obj2);
}

TEST(OperatorsTest, NotEqTest) {
   Thirteen obj1 = Thirteen("1");
   Thirteen obj2 = Thirteen("12");

   ASSERT_TRUE(obj1 != obj2);
   ASSERT_FALSE(obj2 != obj2);
}