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

DEFINE_TEST_GROUP(IsEqualFromNull)
{
	TEST_CASE("Empty pointer is equal to nullptr") {
		CBaseAPtr base(nullptr);

		CHECK(base == nullptr, "base: %p", base.Get());
		CHECK(nullptr == base, "base: %p", base.Get());
		CHECK(!(base != nullptr), "base: %p", base.Get());
		CHECK(!(nullptr != base), "base: %p", base.Get());
	}

	TEST_CASE("Non-empty pointer is not equal to nullptr") {
		CBaseAPtr base;

		CHECK(base != nullptr, "base: %p", base.Get());
		CHECK(nullptr != base, "base: %p", base.Get());
		CHECK(!(base == nullptr), "base: %p", base.Get());
		CHECK(!(nullptr == base), "base: %p", base.Get());
	}
}

DEFINE_TEST_GROUP(IsEqualFromOverload)
{
	TEST_CASE("Empty pointer is not equal to overload") {
		CDerivePtr derive(nullptr);
		CTypeDeriveIsEqualPtr i(10);

		CHECK(derive != i, "derive: %p", derive.Get());
		CHECK(i != derive, "derive: %p", derive.Get());
		CHECK(!(derive == i), "derive: %p", derive.Get());
		CHECK(!(i == derive), "derive: %p", derive.Get());
	}

	TEST_CASE("Non-empty pointer may equal to overload") {
		CDerivePtr derive(10);
		CTypeDeriveIsEqualPtr i(10);
		CTypeDeriveIsEqualPtr j(20);

		CHECK(derive == i, "derive: %d", derive->Get());
		CHECK(i == derive, "derive: %d", derive->Get());
		CHECK(!(derive != i), "derive: %d", derive->Get());
		CHECK(!(i != derive), "derive: %d", derive->Get());

		CHECK(derive != j, "derive: %d", derive->Get());
		CHECK(j != derive, "derive: %d", derive->Get());
		CHECK(!(derive == j), "derive: %d", derive->Get());
		CHECK(!(j == derive), "derive: %d", derive->Get());
	}
}

DEFINE_TEST_GROUP(IsEqualFromConstructor)
{
	TEST_CASE("Empty pointer is not equal to constructor") {
		CDerivePtr derive(nullptr);

		CHECK(derive != 10, "derive: %p", derive.Get());
		CHECK(10 != derive, "derive: %p", derive.Get());
		CHECK(!(derive == 10), "derive: %p", derive.Get());
		CHECK(!(10 == derive), "derive: %p", derive.Get());
	}

	TEST_CASE("Empty pointer is not equal to implicit conversion") {
		CDerivePtr derive(nullptr);
		CTypeDeriveImplicitConvertPtr i(10);

		CHECK(derive != i, "derive: %p", derive.Get());
		CHECK(i != derive, "derive: %p", derive.Get());
		CHECK(!(derive == i), "derive: %p", derive.Get());
		CHECK(!(i == derive), "derive: %p", derive.Get());
	}

	TEST_CASE("Non-empty pointer may equal to constructor") {
		CDerivePtr derive(10);

		CHECK(derive == 10, "derive: %d", derive->Get());
		CHECK(10 == derive, "derive: %d", derive->Get());
		CHECK(!(derive != 10), "derive: %d", derive->Get());
		CHECK(!(10 != derive), "derive: %d", derive->Get());

		CHECK(derive != 20, "derive: %d", derive->Get());
		CHECK(20 != derive, "derive: %d", derive->Get());
		CHECK(!(derive == 20), "derive: %d", derive->Get());
		CHECK(!(20 == derive), "derive: %d", derive->Get());
	}

	TEST_CASE("Non-empty pointer may equal to implicit conversion") {
		CDerivePtr derive(618);
		CTypeDeriveImplicitConvertPtr i(618);
		CTypeDeriveImplicitConvertPtr j(1111);

		CHECK(derive == i, "derive: %d", derive->Get());
		CHECK(i == derive, "derive: %d", derive->Get());
		CHECK(!(derive != i), "derive: %d", derive->Get());
		CHECK(!(i != derive), "derive: %d", derive->Get());

		CHECK(derive != j, "derive: %d", derive->Get());
		CHECK(j != derive, "derive: %d", derive->Get());
		CHECK(!(derive == j), "derive: %d", derive->Get());
		CHECK(!(j == derive), "derive: %d", derive->Get());
	}
}

void IsEqual(void)
{
	START_TEST();

	RUN_TEST_GROUP(IsEqualFromNull);
	RUN_TEST_GROUP(IsEqualFromOverload);
	RUN_TEST_GROUP(IsEqualFromConstructor);

	STOP_TEST();
}

