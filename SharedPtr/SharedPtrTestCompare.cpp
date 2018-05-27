/*
 * Copyright (c) 2018 Guo Xiang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* Uncomment to show the detail test cases */
//#define SHOW_TEST_CASE

#include "SharedPtrTest.hpp"
#include "Compare.hpp"

#define CHECK_COMPARE(condition) \
	CHECK(condition, #condition)

DEFINE_TEST_GROUP(CompareOverloadBoth)
{
	TEST_CASE("Overload both compare to overload none") {
		CCompareBothPtr left1(10);
		CCompareBothPtr left2(20);
		CCompareNonePtr right1(10);
		CCompareNonePtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload both compare to overload bigger") {
		CCompareBothPtr left1(10);
		CCompareBothPtr left2(20);
		CCompareBiggerPtr right1(10);
		CCompareBiggerPtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload both compare to overload smaller") {
		CCompareBothPtr left1(10);
		CCompareBothPtr left2(20);
		CCompareSmallerPtr right1(10);
		CCompareSmallerPtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload both compare to overload smaller") {
		CCompareBothPtr left1(10);
		CCompareBothPtr left2(20);
		CCompareBothPtr right1(10);
		CCompareBothPtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}
}

DEFINE_TEST_GROUP(CompareOverloadBigger)
{
	TEST_CASE("Overload bigger compare to overload none") {
		CCompareBiggerPtr left1(10);
		CCompareBiggerPtr left2(20);
		CCompareNonePtr right1(10);
		CCompareNonePtr right2(20);

//		CHECK_COMPARE(!(left1 < right1));
//		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
//		CHECK_COMPARE(!(right1 > left1));
//		CHECK_COMPARE(right1 >= left1);

//		CHECK_COMPARE(left1 < right2);
//		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
//		CHECK_COMPARE(right2 > left1);
//		CHECK_COMPARE(right2 >= left1);

//		CHECK_COMPARE(!(left2 < right1));
//		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
//		CHECK_COMPARE(!(right1 > left2));
//		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload bigger compare to overload bigger") {
		CCompareBiggerPtr left1(10);
		CCompareBiggerPtr left2(20);
		CCompareBiggerPtr right1(10);
		CCompareBiggerPtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload bigger compare to overload smaller") {
		CCompareBiggerPtr left1(10);
		CCompareBiggerPtr left2(20);
		CCompareSmallerPtr right1(10);
		CCompareSmallerPtr right2(20);

//		CHECK_COMPARE(!(left1 < right1));
//		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
//		CHECK_COMPARE(!(right1 > left1));
//		CHECK_COMPARE(right1 >= left1);

//		CHECK_COMPARE(left1 < right2);
//		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
//		CHECK_COMPARE(right2 > left1);
//		CHECK_COMPARE(right2 >= left1);

//		CHECK_COMPARE(!(left2 < right1));
//		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
//		CHECK_COMPARE(!(right1 > left2));
//		CHECK_COMPARE(!(right1 >= left2));
	}
}

DEFINE_TEST_GROUP(CompareOverloadSmaller)
{
	TEST_CASE("Overload smaller compare to overload none") {
		CCompareSmallerPtr left1(10);
		CCompareSmallerPtr left2(20);
		CCompareNonePtr right1(10);
		CCompareNonePtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
//		CHECK_COMPARE(!(left1 > right1));
//		CHECK_COMPARE(left1 >= right1);
//		CHECK_COMPARE(!(right1 < left1));
//		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
//		CHECK_COMPARE(!(left1 > right2));
//		CHECK_COMPARE(!(left1 >= right2));
//		CHECK_COMPARE(!(right2 < left1));
//		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
//		CHECK_COMPARE(left2 > right1);
//		CHECK_COMPARE(left2 >= right1);
//		CHECK_COMPARE(right1 < left2);
//		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload smaller compare to overload bigger") {
		CCompareSmallerPtr left1(10);
		CCompareSmallerPtr left2(20);
		CCompareBiggerPtr right1(10);
		CCompareBiggerPtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
//		CHECK_COMPARE(!(left1 > right1));
//		CHECK_COMPARE(left1 >= right1);
//		CHECK_COMPARE(!(right1 < left1));
//		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
//		CHECK_COMPARE(!(left1 > right2));
//		CHECK_COMPARE(!(left1 >= right2));
//		CHECK_COMPARE(!(right2 < left1));
//		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
//		CHECK_COMPARE(left2 > right1);
//		CHECK_COMPARE(left2 >= right1);
//		CHECK_COMPARE(right1 < left2);
//		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}

	TEST_CASE("Overload smaller compare to overload smaller") {
		CCompareSmallerPtr left1(10);
		CCompareSmallerPtr left2(20);
		CCompareSmallerPtr right1(10);
		CCompareSmallerPtr right2(20);

		CHECK_COMPARE(!(left1 < right1));
		CHECK_COMPARE(left1 <= right1);
		CHECK_COMPARE(!(left1 > right1));
		CHECK_COMPARE(left1 >= right1);
		CHECK_COMPARE(!(right1 < left1));
		CHECK_COMPARE(right1 <= left1);
		CHECK_COMPARE(!(right1 > left1));
		CHECK_COMPARE(right1 >= left1);

		CHECK_COMPARE(left1 < right2);
		CHECK_COMPARE(left1 <= right2);
		CHECK_COMPARE(!(left1 > right2));
		CHECK_COMPARE(!(left1 >= right2));
		CHECK_COMPARE(!(right2 < left1));
		CHECK_COMPARE(!(right2 <= left1));
		CHECK_COMPARE(right2 > left1);
		CHECK_COMPARE(right2 >= left1);

		CHECK_COMPARE(!(left2 < right1));
		CHECK_COMPARE(!(left2 <= right1));
		CHECK_COMPARE(left2 > right1);
		CHECK_COMPARE(left2 >= right1);
		CHECK_COMPARE(right1 < left2);
		CHECK_COMPARE(right1 <= left2);
		CHECK_COMPARE(!(right1 > left2));
		CHECK_COMPARE(!(right1 >= left2));
	}
}

DEFINE_TEST_GROUP(CompareConstructor)
{
	TEST_CASE("Overload both compare to constructor") {
		CCompareBothPtr left1(10);
		CCompareBothPtr left2(20);

		CHECK_COMPARE(!(left1 < 10));
		CHECK_COMPARE(left1 <= 10);
		CHECK_COMPARE(!(left1 > 10));
		CHECK_COMPARE(left1 >= 10);
		CHECK_COMPARE(!(10 < left1));
		CHECK_COMPARE(10 <= left1);
		CHECK_COMPARE(!(10 > left1));
		CHECK_COMPARE(10 >= left1);

		CHECK_COMPARE(left1 < 20);
		CHECK_COMPARE(left1 <= 20);
		CHECK_COMPARE(!(left1 > 20));
		CHECK_COMPARE(!(left1 >= 20));
		CHECK_COMPARE(!(20 < left1));
		CHECK_COMPARE(!(20 <= left1));
		CHECK_COMPARE(20 > left1);
		CHECK_COMPARE(20 >= left1);

		CHECK_COMPARE(!(left2 < 10));
		CHECK_COMPARE(!(left2 <= 10));
		CHECK_COMPARE(left2 > 10);
		CHECK_COMPARE(left2 >= 10);
		CHECK_COMPARE(10 < left2);
		CHECK_COMPARE(10 <= left2);
		CHECK_COMPARE(!(10 > left2));
		CHECK_COMPARE(!(10 >= left2));
	}

	TEST_CASE("Overload bigger compare to constructor") {
		CCompareBiggerPtr left1(10);
		CCompareBiggerPtr left2(20);

		CHECK_COMPARE(!(left1 < 10));
		CHECK_COMPARE(left1 <= 10);
		CHECK_COMPARE(!(left1 > 10));
		CHECK_COMPARE(left1 >= 10);
		CHECK_COMPARE(!(10 < left1));
		CHECK_COMPARE(10 <= left1);
		CHECK_COMPARE(!(10 > left1));
		CHECK_COMPARE(10 >= left1);

		CHECK_COMPARE(left1 < 20);
		CHECK_COMPARE(left1 <= 20);
		CHECK_COMPARE(!(left1 > 20));
		CHECK_COMPARE(!(left1 >= 20));
		CHECK_COMPARE(!(20 < left1));
		CHECK_COMPARE(!(20 <= left1));
		CHECK_COMPARE(20 > left1);
		CHECK_COMPARE(20 >= left1);

		CHECK_COMPARE(!(left2 < 10));
		CHECK_COMPARE(!(left2 <= 10));
		CHECK_COMPARE(left2 > 10);
		CHECK_COMPARE(left2 >= 10);
		CHECK_COMPARE(10 < left2);
		CHECK_COMPARE(10 <= left2);
		CHECK_COMPARE(!(10 > left2));
		CHECK_COMPARE(!(10 >= left2));
	}

	TEST_CASE("Overload smaller compare to constructor") {
		CCompareSmallerPtr left1(10);
		CCompareSmallerPtr left2(20);

		CHECK_COMPARE(!(left1 < 10));
		CHECK_COMPARE(left1 <= 10);
		CHECK_COMPARE(!(left1 > 10));
		CHECK_COMPARE(left1 >= 10);
		CHECK_COMPARE(!(10 < left1));
		CHECK_COMPARE(10 <= left1);
		CHECK_COMPARE(!(10 > left1));
		CHECK_COMPARE(10 >= left1);

		CHECK_COMPARE(left1 < 20);
		CHECK_COMPARE(left1 <= 20);
		CHECK_COMPARE(!(left1 > 20));
		CHECK_COMPARE(!(left1 >= 20));
		CHECK_COMPARE(!(20 < left1));
		CHECK_COMPARE(!(20 <= left1));
		CHECK_COMPARE(20 > left1);
		CHECK_COMPARE(20 >= left1);

		CHECK_COMPARE(!(left2 < 10));
		CHECK_COMPARE(!(left2 <= 10));
		CHECK_COMPARE(left2 > 10);
		CHECK_COMPARE(left2 >= 10);
		CHECK_COMPARE(10 < left2);
		CHECK_COMPARE(10 <= left2);
		CHECK_COMPARE(!(10 > left2));
		CHECK_COMPARE(!(10 >= left2));
	}
}

void Compare(void)
{
	START_TEST();

	RUN_TEST_GROUP(CompareOverloadBoth);
	RUN_TEST_GROUP(CompareOverloadBigger);
	RUN_TEST_GROUP(CompareOverloadSmaller);
	RUN_TEST_GROUP(CompareConstructor);

	STOP_TEST();
}

