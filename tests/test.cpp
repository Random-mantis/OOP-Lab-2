#include <gtest/gtest.h>
#include "decimal.h"

TEST(DecimalTest, DefaultConstructor) {
    Decimal d;
    EXPECT_EQ(d.toString(), "0");
}

TEST(DecimalTest, IntConstructor) {
    Decimal d(12345);
    EXPECT_EQ(d.toString(), "12345");
}

TEST(DecimalTest, StringConstructor) {
    Decimal d("98765");
    EXPECT_EQ(d.toString(), "98765");
}

TEST(DecimalTest, InitializerListConstructor) {
    Decimal d({1,2,3,4,5});
    EXPECT_EQ(d.toString(), "12345");
}

TEST(DecimalTest, EqualityCheck) {
    Decimal a("123");
    Decimal b("123");
    EXPECT_TRUE(a.check_eq(b));
    EXPECT_FALSE(a.check_not_eq(b));
}

TEST(DecimalTest, LessCheck) {
    Decimal a("123");
    Decimal b("456");
    EXPECT_TRUE(a.check_less(b));
    EXPECT_TRUE(a.check_less_or_eq(b));
    EXPECT_FALSE(a.check_more(b));
}

TEST(DecimalTest, GreaterCheck) {
    Decimal a("456");
    Decimal b("123");
    EXPECT_TRUE(a.check_more(b));
    EXPECT_TRUE(a.check_more_or_eq(b));
    EXPECT_FALSE(a.check_less(b));
}

TEST(DecimalTest, SumOperation) {
    Decimal a("123");
    Decimal b("77");
    Decimal c = a.sum(b);
    EXPECT_EQ(c.toString(), "200");
}

TEST(DecimalTest, SubtractionOperation) {
    Decimal a("200");
    Decimal b("77");
    Decimal c = a.addition_minus(b);
    EXPECT_EQ(c.toString(), "123");
}

TEST(DecimalTest, SubtractionThrows) {
    Decimal a("50");
    Decimal b("77");
    EXPECT_THROW(a.addition_minus(b), std::underflow_error);
}