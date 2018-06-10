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

DEFINE_TEST_GROUP(Release)
{
	TEST_CASE("Should work for non-const type") {
		CDerivePtr derive(20);
		CHECK_DERIVE(derive, 1, 3);

		derive.Release();
		CHECK_EMPTY(derive);
	}

	TEST_CASE("Should work for const type") {
		CConstDerivePtr derive(20);
		CHECK_DERIVE(derive, 1, 2);

		derive.Release();
		CHECK_EMPTY(derive);
	}
}

DEFINE_TEST_GROUP(Get)
{
	TEST_CASE("Should work for non-const type") {
		CDerivePtr derive(20);
		CHECK_DERIVE(derive, 1, 3);

		CHECK(20 == derive.Get()->Get(),
			  "derive: %d", derive.Get()->Get());
	}

	TEST_CASE("Should work for const type") {
		CConstDerivePtr derive(20);
		CHECK_DERIVE(derive, 1, 2);

		CHECK(20 == derive.Get()->Get(),
			  "const derive: %d", derive.Get()->Get());
	}
}

DEFINE_TEST_GROUP(Swap)
{
	TEST_CASE("Should work between same type (non-const to non-const)") {
		CDerivePtr derive1(10);
		CDerivePtr derive2(20);
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK(10 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(20 == derive2->Get(), "derive2: %d", derive2->Get());

		derive1.Swap(derive2);
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK(20 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(10 == derive2->Get(), "derive2: %d", derive2->Get());
	}

	TEST_CASE("Should work between same type (const to const)") {
		CConstDerivePtr derive1(10);
		CConstDerivePtr derive2(20);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 1, 2);
		CHECK(10 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(20 == derive2->Get(), "derive2: %d", derive2->Get());

		derive1.Swap(derive2);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 1, 2);
		CHECK(20 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(10 == derive2->Get(), "derive2: %d", derive2->Get());
	}

	TEST_CASE("Should work between valid parent and derive (non-const to non-const)") {
		CDerivePtr derive1(10);		/* derive1 -> 10 */
		CDerivePtr derive2(20);		/* derive2 -> 20 */
		CBaseAPtr base(derive2);	/* base    -> 20 */
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK(10 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(20 == derive2->Get(), "derive2: %d", derive2->Get());

		derive1.Swap(base);			/* derive1 -> 20 */
									/* derive2 -> 20 */
									/* base    -> 10 */
		CDerivePtr derive3(base);	/* derive3 -> 10 */
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK(20 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(20 == derive2->Get(), "derive2: %d", derive2->Get());
		CHECK(10 == derive3->Get(), "derive3: %d", derive3->Get());

		base.Swap(derive2);			/* derive1 -> 20 */
									/* derive2 -> 10 */
									/* base    -> 20 */
		derive3 = base;				/* derive3 -> 20 */
		CHECK_DERIVE(derive1, 3, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK(20 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(10 == derive2->Get(), "derive2: %d", derive2->Get());
		CHECK(20 == derive3->Get(), "derive3: %d", derive3->Get());
	}

	TEST_CASE("Should work between same type (const to const)") {
		CConstDerivePtr derive1(10);		/* derive1 -> 10 */
		CConstDerivePtr derive2(20);		/* derive2 -> 20 */
		CConstBaseAPtr base(derive2);		/* base    -> 20 */
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK(10 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(20 == derive2->Get(), "derive2: %d", derive2->Get());

		derive1.Swap(base);					/* derive1 -> 20 */
											/* derive2 -> 20 */
											/* base    -> 10 */
		CConstDerivePtr derive3(base);		/* derive3 -> 10 */
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK(20 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(20 == derive2->Get(), "derive2: %d", derive2->Get());
		CHECK(10 == derive3->Get(), "derive3: %d", derive3->Get());

		base.Swap(derive2);					/* derive1 -> 20 */
											/* derive2 -> 10 */
											/* base    -> 20 */
		derive3 = base;						/* derive3 -> 20 */
		CHECK_DERIVE(derive1, 3, 2);
		CHECK_DERIVE(derive2, 1, 2);
		CHECK_DERIVE(derive3, 3, 2);
		CHECK(20 == derive1->Get(), "derive1: %d", derive1->Get());
		CHECK(10 == derive2->Get(), "derive2: %d", derive2->Get());
		CHECK(20 == derive3->Get(), "derive3: %d", derive3->Get());
	}

/* Swap between const and non-const should now work */
#if 0
	CConstDerivePtr derive1;
	CDerivePtr derive2;
	derive2.Swap(derive1);
#endif

/* Swap between non-const and const should now work */
#if 0
	CConstDerivePtr derive1;
	CDerivePtr derive2;
	derive1.Swap(derive2);
#endif
}

void Others(void)
{
	START_TEST();

	RUN_TEST_GROUP(Release);
	RUN_TEST_GROUP(Get);
	RUN_TEST_GROUP(Swap);

	STOP_TEST();
}

