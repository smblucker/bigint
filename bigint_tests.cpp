#include "bigint.h"
#include <sstream>
using namespace csis3700;

#define BOOST_TEST_MODULE BigIntTests
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(get_digit_count_should_work_with_constructors)
{
    bigint b(3287);
    BOOST_CHECK_EQUAL(b.get_digit_count(), 4);
    
    bigint b1(0);
    BOOST_CHECK_EQUAL(b1.get_digit_count(), 1);
    BOOST_CHECK_EQUAL(b1.get_digit(0), 0);
    
    uint8_t a[] = {4,5,6,7,8,9};
    
    bigint b2(a, 6, false);
    BOOST_CHECK_EQUAL(b2.get_digit_count(), 6);
    
    uint8_t a1[] = {0};
    
    bigint b3(a1, 1, false);
    BOOST_CHECK_EQUAL(b3.get_digit_count(), 1);
}

BOOST_AUTO_TEST_CASE(get_digit_should_work_with_long_long_constructor)
{
    bigint b(3287);
    BOOST_CHECK_EQUAL(b.get_digit(0), 7);
    BOOST_CHECK_EQUAL(b.get_digit(1), 8);
    BOOST_CHECK_EQUAL(b.get_digit(2), 2);
    BOOST_CHECK_EQUAL(b.get_digit(3), 3);
    
    bigint b1(0);
    BOOST_CHECK_EQUAL(b1.get_digit(0), 0);
}

BOOST_AUTO_TEST_CASE(get_digit_should_work_with_input_constructor)
{
    uint8_t a[] = {4,5,6,7,8,9};
    
    bigint b(a, 6, false);
    
    BOOST_CHECK_EQUAL(b.get_digit(0), 4);
    BOOST_CHECK_EQUAL(b.get_digit(1), 5);
    BOOST_CHECK_EQUAL(b.get_digit(2), 6);
    BOOST_CHECK_EQUAL(b.get_digit(3), 7);
    BOOST_CHECK_EQUAL(b.get_digit(4), 8);
    BOOST_CHECK_EQUAL(b.get_digit(5), 9);
    
    a[0] = 7;
    BOOST_CHECK_EQUAL(b.get_digit(0), 4);
    
    uint8_t a1[] = {0};
    
    bigint b1(a1, 1, false);
    
    BOOST_CHECK_EQUAL(b1.get_digit(0), 0);
}

BOOST_AUTO_TEST_CASE(is_negative_should_work)
{
    bigint b(3287);
    BOOST_CHECK_EQUAL(b.is_negative(), false);
    
    bigint b1(-3287);
    BOOST_CHECK_EQUAL(b1.is_negative(), true);
    
    bigint b2(0);
    BOOST_CHECK_EQUAL(b2.is_negative(), false);
    
    uint8_t a[] = {4,5,6,7};
    
    bigint b3(a, 4, false);
    BOOST_CHECK_EQUAL(b3.is_negative(), false);
    
    uint8_t a1[] = {4,5,6,7};
    
    bigint b4(a1, 4, true);
    BOOST_CHECK_EQUAL(b4.is_negative(), true);
    
    uint8_t a2[] = {0};
    
    bigint b5(a2, 1, false);
    BOOST_CHECK_EQUAL(b5.is_negative(), false);
}

BOOST_AUTO_TEST_CASE(negate_should_work)
{
    bigint a(1567);
    
    bigint b = a.negate();
    
    BOOST_CHECK_EQUAL(b.is_negative(), true);
    BOOST_CHECK_EQUAL(a.is_negative(), false);
    BOOST_CHECK_EQUAL(b.get_digit(0), 7);
    BOOST_CHECK_EQUAL(b.get_digit(1), 6);
    BOOST_CHECK_EQUAL(b.get_digit(2), 5);
    BOOST_CHECK_EQUAL(b.get_digit(3), 1);
    
    bigint a1(-1567);
    
    bigint b1 = a1.negate();
    
    BOOST_CHECK_EQUAL(b1.is_negative(), false);
    BOOST_CHECK_EQUAL(a1.is_negative(), true);
    BOOST_CHECK_EQUAL(b1.get_digit(0), 7);
    BOOST_CHECK_EQUAL(b1.get_digit(1), 6);
    BOOST_CHECK_EQUAL(b1.get_digit(2), 5);
    BOOST_CHECK_EQUAL(b1.get_digit(3), 1);
    
    uint8_t a2[] = {4,5,6,7};
    
    bigint b2(a2, 4, false);
    
    bigint b3 = b2.negate();
    
    BOOST_CHECK_EQUAL(b3.is_negative(), true);
    BOOST_CHECK_EQUAL(b2.is_negative(), false);
    
    uint8_t a3[] = {4,5,6,7};
    
    bigint b4(a3, 4, true);
    
    bigint b5 = b4.negate();
    
    BOOST_CHECK_EQUAL(b5.is_negative(), false);
    BOOST_CHECK_EQUAL(b4.is_negative(), true);
}
    
BOOST_AUTO_TEST_CASE(equivalence_overload_should_work)
{
    bigint b1(1234);
    bigint b2(1234);
    
    BOOST_CHECK_EQUAL(b1==b2, true);
    
    bigint b3(1234);
    bigint b4(2234);
    
    BOOST_CHECK_EQUAL(b3==b4, false);
    
    bigint b5(1234);
    bigint b6(1334);
    
    BOOST_CHECK_EQUAL(b5==b6, false);
    
    bigint b7(1234);
    bigint b8(1244);
    
    BOOST_CHECK_EQUAL(b7==b8, false);
    
    bigint b9(1234);
    bigint b10(1235);
    
    BOOST_CHECK_EQUAL(b9==b10, false);
    
    bigint b11(1234);
    bigint b12(12345);
    
    BOOST_CHECK_EQUAL(b11==b12, false);
    
    bigint b13(12345);
    bigint b14(1234);
    
    BOOST_CHECK_EQUAL(b13==b14, false);
    
    bigint b15(1234);
    bigint b16(-1234);
    
    BOOST_CHECK_EQUAL(b15==b16, false);
    
    uint8_t a[] = {4,5,6,7};
    uint8_t a1[] = {4,5,6,7};
    
    bigint b17(a, 4, false);
    bigint b18(a1, 4, false);
    
    BOOST_CHECK_EQUAL(b17==b18, true);
    
    uint8_t a2[] = {4,5,6,7,8};
    uint8_t a3[] = {4,5,6,7};
    
    bigint b19(a2, 5, false);
    bigint b20(a3, 4, false);
    
    BOOST_CHECK_EQUAL(b19==b20, false);
    
    uint8_t a4[] = {4,5,6,7};
    uint8_t a5[] = {4,5,6,7};
    
    bigint b21(a4, 4, true);
    bigint b22(a5, 4, false);
    
    BOOST_CHECK_EQUAL(b21==b22, false);
    
    uint8_t a6[] = {4,5,6,7};
    uint8_t a7[] = {5,5,6,7};
    
    bigint b23(a6, 4, false);
    bigint b24(a7, 4, false);
    
    BOOST_CHECK_EQUAL(b23==b24, false);
    
}

BOOST_AUTO_TEST_CASE(less_than_overload_should_work)
{
    bigint b1(1235);
    bigint b2(1234);
    
    BOOST_CHECK_EQUAL(b1<b2, false);
    
    bigint b3(1234);
    bigint b4(1235);
    
    BOOST_CHECK_EQUAL(b3<b4, true);
    
    bigint b5(1235);
    bigint b6(234);
    
    BOOST_CHECK_EQUAL(b5<b6, false);
    
    bigint b7(235);
    bigint b8(1234);
    
    BOOST_CHECK_EQUAL(b7<b8, true);
    
    bigint b9(-1235);
    bigint b10(1234);
    
    BOOST_CHECK_EQUAL(b7<b8, true);
    
    bigint b11(1235);
    bigint b12(-1234);
    
    BOOST_CHECK_EQUAL(b11<b12, false);
    
    bigint b13(1244);
    bigint b14(1234);
    
    BOOST_CHECK_EQUAL(b13<b14, false);
    
    bigint b15(1400);
    bigint b16(1234);
    
    BOOST_CHECK_EQUAL(b15<b16, false);
    
    bigint b17(1000);
    bigint b18(1234);
    
    BOOST_CHECK_EQUAL(b17<b18, true);
    
    bigint b19(-1000);
    bigint b20(-1234);
    
    BOOST_CHECK_EQUAL(b19<b20, false);
    
    bigint b21(-1234);
    bigint b22(-1000);
    
    BOOST_CHECK_EQUAL(b21<b22, true);
    
    bigint b23(2454);
    bigint b24(1356);
    
    BOOST_CHECK_EQUAL(b23<b24, false);
}

BOOST_AUTO_TEST_CASE(plus_equals_overload_should_work)
{
    bigint b1(32);
    bigint b2(49);
    
    b1+=b2;
    
    BOOST_CHECK(b1==81);
    
    bigint b3(32);
    bigint b4(41);
    
    b3+=b4;
    
    BOOST_CHECK(b3==73);
    
    bigint b5(132);
    bigint b6(41);
    
    b5+=b6;
    
    BOOST_CHECK(b5==173);
    
    bigint b7(41);
    bigint b8(132);
    
    b7+=b8;
    
    BOOST_CHECK(b7==173);
    
    bigint b9(132);
    bigint b10(180);
    
    b9+=b10;
    
    BOOST_CHECK(b9==312);
    
    bigint b11(132);
    bigint b12(940);
    
    b11+=b12;
    
    BOOST_CHECK(b11==1072);
    
    bigint b13(999);
    bigint b14(1);
    
    b13+=b14;
    
    BOOST_CHECK(b13==1000);
}

BOOST_AUTO_TEST_CASE(plus_overload_should_work)
{
    bigint b1(32);
    bigint b2(49);
    
    BOOST_CHECK(b1 + b2==81);
    
    bigint b3(32);
    bigint b4(41);
    
    BOOST_CHECK(b3 + b4==73);
    
    bigint b5(132);
    bigint b6(41);
    
    BOOST_CHECK(b5 + b6==173);
    
    bigint b7(41);
    bigint b8(132);
    
    BOOST_CHECK(b7 + b8==173);
    
    bigint b9(132);
    bigint b10(180);
    
    BOOST_CHECK(b9 + b10==312);
    
    bigint b11(132);
    bigint b12(940);
    
    BOOST_CHECK(b11 + b12==1072);
    
    bigint b13(999);
    bigint b14(1);
    
    BOOST_CHECK(b13 + b14==1000);
}

BOOST_AUTO_TEST_CASE(minus_equals_overload_should_work)
{
    bigint b1(137);
    bigint b2(82);
    
    b1-=b2;
    
    BOOST_CHECK(b1==55);
    
    bigint b3(137);
    bigint b4(23);
    
    b3-=b4;
    
    BOOST_CHECK(b3==114);
}

BOOST_AUTO_TEST_CASE(minus_overload_should_work)
{
    bigint b1(137);
    bigint b2(82);
    
    BOOST_CHECK(b1 - b2==55);
    
    bigint b3(137);
    bigint b4(23);
    
    BOOST_CHECK(b3 - b4==114);
}

BOOST_AUTO_TEST_CASE(times_equals_overload_should_work)
{
    bigint b1(85);
    bigint b2(5);
    
    b1*=b2;
    
    BOOST_CHECK(b1==425);
    
    bigint b3(137);
    bigint b4(2);
    
    b3*=b4;
    
    BOOST_CHECK(b3==274);
    
    bigint b5(15);
    bigint b6(15);
    
    b5*=b6;
    
    BOOST_CHECK(b5==225);
    
    bigint b7(100);
    bigint b8(15);
    
    b7*=b8;
    
    BOOST_CHECK(b7==1500);
    
    bigint b9(1234);
    bigint b10(4321);
    
    b9*=b10;
    
    BOOST_CHECK(b9==5332114);
}

BOOST_AUTO_TEST_CASE(times_overload_should_work)
{
    bigint b1(85);
    bigint b2(5);
    
    BOOST_CHECK(b1 * b2==425);
    
    bigint b3(137);
    bigint b4(2);
    
    BOOST_CHECK(b3 * b4==274);
    
    bigint b5(15);
    bigint b6(15);
    
    BOOST_CHECK(b5 * b6==225);
    
    bigint b7(100);
    bigint b8(15);
    
    BOOST_CHECK(b7 * b8==1500);
    
    bigint b9(1234);
    bigint b10(4321);
    
    BOOST_CHECK(b9 * b10==5332114);
}

BOOST_AUTO_TEST_CASE(output_should_be_formatted_correctly) 
{
  bigint b1(996);
  std::stringstream ss;
  ss << b1;
  BOOST_CHECK_EQUAL(ss.str(), "996");
  
  bigint b2(-996);
  std::stringstream ss2;
  ss2 << b2;
  BOOST_CHECK_EQUAL(ss2.str(), "-996");
  
  bigint b3(0);
  std::stringstream ss3;
  ss3 << b3;
  BOOST_CHECK_EQUAL(ss3.str(), "0");
  
  bigint b4(1000);
  std::stringstream ss4;
  ss4 << b4;
  BOOST_CHECK_EQUAL(ss4.str(), "1000");
}