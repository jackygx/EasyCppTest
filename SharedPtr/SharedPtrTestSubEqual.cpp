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

DEFINE_TEST_GROUP(SubEqualFromNull)
{
	TEST_CASE("Nothing happen when empty pointer adds equal nullptr") {
		CBaseAPtr base(nullptr);
		CHECK_EMPTY(base);

		base -= nullptr;
		CHECK_EMPTY(base);
	}

	TEST_CASE("Nothing happen when empty pointer adds equal nullptr") {
		CDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 3);

		derive -= nullptr;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 10, "Derive: ", DEC(derive->Get()));
	}
}

DEFINE_TEST_GROUP(SubEqualFromOverload)
{
	TEST_CASE("Throw error when empty pointer adds equal to overload") {
		CDerivePtr derive(nullptr);
		CTypeDeriveSubEqualPtr i(10);

		CHECK_THROW(derive -= i);
	}

	TEST_CASE("Call overload when non-empty pointer adds equal to overload") {
		CDerivePtr derive(30);
		CTypeDeriveSubEqualPtr i(10);
		CHECK_DERIVE(derive, 1, 3);

		derive -= i;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 20, "Derive: ", DEC(derive->Get()));
	}
}

DEFINE_TEST_GROUP(SubEqualFromConstructor)
{
	TEST_CASE("Throw error when empty pointer adds equal to constructor") {
		CDerivePtr derive(nullptr);
		CHECK_EMPTY(derive);

		CHECK_THROW(derive -= 10);
	}

	TEST_CASE("Throw error when empty pointer adds equal to implicit conversion") {
		CDerivePtr derive(nullptr);
		CTypeDeriveImplicitConvertPtr i(10);
		CHECK_EMPTY(derive);

		CHECK_THROW(derive -= 10);
	}

	TEST_CASE("Call overload when non-empty pointer adds equal to constructor") {
		CDerivePtr derive(30);
		CHECK_DERIVE(derive, 1, 3);

		derive -= 10;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 20, "Derive: ", DEC(derive->Get()));
	}

	TEST_CASE("Call overload when non-empty pointer adds equal to implicit conversion") {
		CDerivePtr derive(30);
		CTypeDeriveImplicitConvertPtr i(10);
		CHECK_DERIVE(derive, 1, 3);

		derive -= i;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 20, "Derive: ", DEC(derive->Get()));
	}
}

void SubEqual(void)
{
	START_TEST();

	RUN_TEST_GROUP(SubEqualFromNull);
	RUN_TEST_GROUP(SubEqualFromOverload);
	RUN_TEST_GROUP(SubEqualFromConstructor);

	STOP_TEST();
}

