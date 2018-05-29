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

DEFINE_TEST_GROUP(OperatorSquareBracket)
{
	TEST_CASE("Should work for non-const type") {
		CDerivePtr derive(20);
		CTypeDeriveSquareBracketsPtr i(10);
		CHECK_DERIVE(derive, 1, 3);

		CHECK(30 == derive[i], "derive: ", DEC(derive->Get()));
	}

	TEST_CASE("Should work for const type") {
		CConstDerivePtr derive(20);
		CTypeDeriveSquareBracketsPtr i(10);
		CHECK_DERIVE(derive, 1, 2);

		CHECK(30 == derive[i], "derive: ", DEC(derive->Get()));
	}
}

DEFINE_TEST_GROUP(OperatorBool)
{
	TEST_CASE("Should work for true") {
		CDerivePtr derive;
		CHECK_DERIVE(derive, 1, 3);

		CHECK(derive, "derive: does empty");
	}

	TEST_CASE("Should work for false") {
		CDerivePtr derive(nullptr);
		CHECK_EMPTY(derive);

		CHECK(!derive, "derive is not empty");
	}
}

DEFINE_TEST_GROUP(OperatorFunction)
{
	TEST_CASE("Should work for non-const type") {
		CDerivePtr derive(10);
		CTypeDeriveFunction1Ptr i(1);
		CTypeDeriveFunction2Ptr j(2);
		CTypeDeriveFunction3Ptr k(3);
		CHECK_DERIVE(derive, 1, 3);

		CHECK(16 == derive(i, std::move(j), k)->Get(),
			  "derive operator function fail");
	}

	TEST_CASE("Should work for const type") {
		CConstDerivePtr derive(10);
		CTypeDeriveFunction1Ptr i(1);
		CTypeDeriveFunction2Ptr j(2);
		CTypeDeriveFunction3Ptr k(3);
		CHECK_DERIVE(derive, 1, 2);

		CHECK(4 == derive(i, std::move(j), k)->Get(),
			  "const derive operator function fail");
	}
}

DEFINE_TEST_GROUP(OperatorArray)
{
	TEST_CASE("Should work for non-const type") {
		CDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 3);

		CHECK(10 == derive->Get(),
			  "derive operator array fail");
	}

	TEST_CASE("Should work for const type") {
		CConstDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 2);

		CHECK(10 == derive->Get(),
			  "const derive operator function fail");
	}
}

DEFINE_TEST_GROUP(OperatorStar)
{
	TEST_CASE("Should work for non-const type") {
		CDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 3);

		CHECK(10 == (*derive).Get(),
			  "derive operator array fail");
	}

	TEST_CASE("Should work for const type") {
		CConstDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 2);

		CHECK(10 == (*derive).Get(),
			  "const derive operator function fail");
	}
}

void OtherOperators(void)
{
	START_TEST();

	RUN_TEST_GROUP(OperatorSquareBracket);
	RUN_TEST_GROUP(OperatorBool);
	RUN_TEST_GROUP(OperatorFunction);
	RUN_TEST_GROUP(OperatorArray);
	RUN_TEST_GROUP(OperatorStar);

	STOP_TEST();
}

