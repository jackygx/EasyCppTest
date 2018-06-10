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

DEFINE_TEST_GROUP(AddEqualFromNull)
{
	TEST_CASE("Nothing happen when empty pointer adds equal nullptr") {
		CBaseAPtr base(nullptr);
		CHECK_EMPTY(base);

		base += nullptr;
		CHECK_EMPTY(base);
	}

	TEST_CASE("Nothing happen when empty pointer adds equal nullptr") {
		CDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 3);

		derive += nullptr;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 10, "Derive: %d", derive->Get());
	}
}

DEFINE_TEST_GROUP(AddEqualFromOverload)
{
	TEST_CASE("Throw error when empty pointer adds equal to overload") {
		CDerivePtr derive(nullptr);
		CTypeDeriveAddEqualPtr i(10);

		CHECK_THROW(derive += i);
	}

	TEST_CASE("Call overload when non-empty pointer adds equal to overload") {
		CDerivePtr derive(10);
		CTypeDeriveAddEqualPtr i(10);
		CHECK_DERIVE(derive, 1, 3);

		derive += i;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 20, "Derive: %d", derive->Get());
	}
}

DEFINE_TEST_GROUP(AddEqualFromConstructor)
{
	TEST_CASE("Throw error when empty pointer adds equal to constructor") {
		CDerivePtr derive(nullptr);
		CHECK_EMPTY(derive);

		CHECK_THROW(derive += 10);
	}

	TEST_CASE("Throw error when empty pointer adds equal to implicit conversion") {
		CDerivePtr derive(nullptr);
		CTypeDeriveImplicitConvertPtr i(10);
		CHECK_EMPTY(derive);

		CHECK_THROW(derive += 10);
	}

	TEST_CASE("Call overload when non-empty pointer adds equal to constructor") {
		CDerivePtr derive(10);
		CHECK_DERIVE(derive, 1, 3);

		derive += 10;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 20, "Derive: %d", derive->Get());
	}

	TEST_CASE("Call overload when non-empty pointer adds equal to implicit conversion") {
		CDerivePtr derive(10);
		CTypeDeriveImplicitConvertPtr i(10);
		CHECK_DERIVE(derive, 1, 3);

		derive += i;
		CHECK_DERIVE(derive, 1, 3);
		CHECK(derive->Get() == 20, "Derive: %d", derive->Get());
	}
}

void AddEqual(void)
{
	START_TEST();

	RUN_TEST_GROUP(AddEqualFromNull);
	RUN_TEST_GROUP(AddEqualFromOverload);
	RUN_TEST_GROUP(AddEqualFromConstructor);

	STOP_TEST();
}

