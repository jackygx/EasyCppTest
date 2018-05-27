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

DEFINE_TEST_GROUP(EqualFromNull)
{
	TEST_CASE("Should be nullptr") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);

		base2 = nullptr;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
	}
}

DEFINE_TEST_GROUP(EqualFromSharedPtrLref)
{
	TEST_CASE("Shold be nullptr if input is nullptr") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3(nullptr);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_SAME_PTR(base1, base2);

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Should work from same type (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base1, base2);

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2, base3);
	}

	TEST_CASE("Should work from same type (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstBaseAPtr base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base1, base2);

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2, base3);
	}

	TEST_CASE("Should work from same type (non-const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CBaseAPtr base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base1, base2);

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2, base3);
	}

	/* Equal from CSharedPtr (lref) same type
	 * (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base1;
	CBaseAPtr base2;
	base2 = base1;
#endif

	TEST_CASE("Should work from derive (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CDerivePtr derive;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(base1, base2);

		base2 = derive;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base2, derive);
	}

	TEST_CASE("Should work from derive (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstDerivePtr derive;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(base1, base2);

		base2 = derive;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_SAME_PTR(base2, derive);
	}

	TEST_CASE("Should work from derive (non-const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CDerivePtr derive;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(base1, base2);

		base2 = derive;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base2, derive);
	}

	/* Equal from CSharedPtr (lref) from derive
	 * (const to non-const) causes compile error */
#if 0
	CBaseAPtr base;
	CConstDerivePtr derive;
	base = derive;
#endif

	TEST_CASE("Should work from a valid base (non-const to non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive3, base);

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 3);
		CHECK_SAME_PTR(derive2, derive3);
		CHECK_SAME_PTR(derive3, base);
	}

	TEST_CASE("Should work from a valid base (const to const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive3, base);

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_DERIVE(derive3, 3, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 2);
		CHECK_SAME_PTR(derive2, derive3);
		CHECK_SAME_PTR(derive3, base);
	}

	TEST_CASE("Should work from a valid base (non-const to const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive3, base);

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 3);
		CHECK_SAME_PTR(derive2, derive3);
		CHECK_SAME_PTR(derive3, base);
	}

	/* Equal from CSharedPtr (lref) from a valid base
	 * (const to non-const) causes compile error */
#if 0
	CDerivePtr derive1;
	CConstDerivePtr derive2;
	CConstBaseAPtr base(derive2);
	derive1 = base;
#endif

	TEST_CASE("Should work from an invalid base") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CDerivePtr derive(nullptr);
		CConstDerivePtr cderive(nullptr);
		CHECK_EMPTY(derive);
		CHECK_EMPTY(cderive);

		CHECK_THROW(cderive = base);
		CHECK_THROW(cderive = cbase);
		CHECK_THROW(derive = base);

		/* Equal from CSharedPtr (lref) from an invalid base type
		 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(derive = cbase);
#endif
	}
}

DEFINE_TEST_GROUP(EqualFromSharedPtrRref)
{
	TEST_CASE("Should be nullptr if input is nullptr") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3(nullptr);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_SAME_PTR(base1, base2);

		base2 = std::move(base3);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}


	TEST_CASE("Should work from same type (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3;
		CBaseAPtr base4(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
		CHECK_SAME_PTR(base3, base4);

		base2 = std::move(base3);

		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2, base4);
	}

	TEST_CASE("Should work from same type (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstBaseAPtr base3;
		CConstBaseAPtr base4(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
		CHECK_SAME_PTR(base3, base4);

		base2 = std::move(base3);

		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2, base4);
	}

	TEST_CASE("Should work from same type (non-const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CBaseAPtr base3;
		CBaseAPtr base4(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
		CHECK_SAME_PTR(base3, base4);

		base2 = std::move(base3);

		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2, base4);
	}

	/* Equal from CSharedPtr (rref) from same type
	 * (const to non-const) causes compile error */
#if 0
	CBaseAPtr base1;
	CConstBaseAPtr base2;
	base1 == std::move(base2);
#endif

	TEST_CASE("Should work from derive (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base1, base2);
		CHECK_SAME_PTR(derive1, derive2);

		base2 = std::move(derive2);

		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_EMPTY(derive2);
		CHECK_SAME_PTR(base2, derive1);
	}

	TEST_CASE("Should work from derive (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(base1, base2);
		CHECK_SAME_PTR(derive1, derive2);

		base2 = std::move(derive2);

		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_EMPTY(derive2);
		CHECK_SAME_PTR(base2, derive1);
	}

	TEST_CASE("Should work from derive (non-const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base1, base2);
		CHECK_SAME_PTR(derive1, derive2);

		base2 = std::move(derive2);

		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_EMPTY(derive2);
		CHECK_SAME_PTR(base2, derive1);
	}

	/* Equal from CSharedPtr (rref) from derive
	 * (const to non-const) causes compile error */
#if 0
	CBaseAPtr base;
	CConstDerivePtr derive;
	base = std::move(derive);
#endif

	TEST_CASE("Should work from a valid base (non-const to non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CBaseAPtr base(derive2);
		CDerivePtr derive3;
		CDerivePtr derive4(derive3);
		CHECK_DERIVE(derive1, 3, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_DERIVE(derive4, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive1, base);
		CHECK_SAME_PTR(derive3, derive4);

		derive3 = std::move(base);

		CHECK_DERIVE(derive1, 3, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_DERIVE(derive4, 1, 3);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive1, derive3);
	}

	TEST_CASE("Should work from a valid base (const to const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstBaseAPtr base(derive2);
		CConstDerivePtr derive3;
		CConstDerivePtr derive4(derive3);
		CHECK_DERIVE(derive1, 3, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive1, base);
		CHECK_SAME_PTR(derive3, derive4);

		derive3 = std::move(base);

		CHECK_DERIVE(derive1, 3, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive3, 3, 2);
		CHECK_DERIVE(derive4, 1, 2);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive1, derive3);
	}

	TEST_CASE("Should work from a valid base (non-const to const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CBaseAPtr base(derive2);
		CConstDerivePtr derive3;
		CConstDerivePtr derive4(derive3);
		CHECK_DERIVE(derive1, 3, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 3);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive1, base);
		CHECK_SAME_PTR(derive3, derive4);

		derive3 = std::move(base);

		CHECK_DERIVE(derive1, 3, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_DERIVE(derive4, 1, 2);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK_SAME_PTR(derive1, derive3);
	}

	/* Equal from CSharedPtr (rref) from a valid base
	 * (const to non-const) causes compile error */
#if 0
	CConstDerivePtr derive1;
	CConstBaseAPtr base(derive1);
	CDerivePtr derive2;
	derive2 = std::move(base);
#endif

	TEST_CASE("Should work from an invalid base") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CDerivePtr derive(nullptr);
		CConstDerivePtr cderive(nullptr);
		CHECK_EMPTY(derive);
		CHECK_EMPTY(cderive);

		CHECK_THROW(cderive = std::move(base));
		CHECK_THROW(cderive = std::move(cbase));
		CHECK_THROW(derive = std::move(base));

		/* Equal from CSharedPtr (lref) from an invalid base type
		 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(derive = cbase);
#endif
	}
}

DEFINE_TEST_GROUP(EqualFromConstructor)
{
	TEST_CASE("Should work from constructor") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);

		derive2 = 10;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK_DIFFERENT_PTR(derive1, derive2);
		CHECK(derive2->Get() == 10, "Derive2: ", DEC(derive2->Get()));
	}

	TEST_CASE("Should work from implicit convert") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CTypeDeriveImplicitConvertPtr val(1111);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);

		derive2 = val;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK_DIFFERENT_PTR(derive1, derive2);
		CHECK(derive2->Get() == 1111, "Derive2: ", DEC(derive2->Get()));
	}
}

DEFINE_TEST_GROUP(EqualFromOverload)
{
	TEST_CASE("Should work from implicit convert") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);

		derive2 = CTypeDeriveEqual(10);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1, derive2);
		CHECK(derive1->Get() == 10, "Derive1: ", DEC(derive1->Get()));
		CHECK(derive2->Get() == 10, "Derive2: ", DEC(derive2->Get()));
	}
}

void Equal(void)
{
	START_TEST();

	RUN_TEST_GROUP(EqualFromNull);
	RUN_TEST_GROUP(EqualFromSharedPtrLref);
	RUN_TEST_GROUP(EqualFromSharedPtrRref);
	RUN_TEST_GROUP(EqualFromConstructor);
	RUN_TEST_GROUP(EqualFromOverload);

	STOP_TEST();
}

