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

DEFINE_TEST_GROUP(DefaultConstructor)
{
	TEST_CASE("Should call default constructor for the class") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}

	TEST_CASE("Should be nullptr for the interface") {
		IBaseCPtr base;
		CHECK_EMPTY(base);
	}
}

DEFINE_TEST_GROUP(NullConstructor)
{
	TEST_CASE("Should be nullptr") {
		CBaseAPtr base(nullptr);
		CHECK_EMPTY(base);
	}
}

DEFINE_TEST_GROUP(CopyConstructor)
{
	TEST_CASE("Shold be nullptr if input is nullptr") {
		CBaseAPtr base1(nullptr);
		CBaseAPtr base2(base1);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Shold increase Ref if input is not nullptr") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
	}
}

DEFINE_TEST_GROUP(MoveConstructor)
{
	TEST_CASE("Shold be nullptr if input is nullptr") {
		CBaseAPtr base1(nullptr);
		CBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Shold NOT increase Ref if input is not nullptr") {
		CBaseAPtr base1;
		CBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
	}
}

DEFINE_TEST_GROUP(PointerConstructor)
{
	TEST_CASE("Should throw error if input is nullptr") {
		CBaseA *base1 = nullptr;
		CHECK_THROW(CBaseAPtr base2(base1));
	}

	TEST_CASE("Should succeed from same type (non-const to non-const)") {
		CBaseA *base1 = new CBaseA;
		CBaseAPtr base2(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
		CHECK_SAME(base2.Get(), base1, HEX);
	}

	TEST_CASE("Should succeed from same type (const to const)") {
		const CBaseA *base1 = new CBaseA;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
		CHECK_SAME(base2.Get(), base1, HEX);
	}

	TEST_CASE("Should succeed from same type (non-const to const)") {
		CBaseA *base1 = new CBaseA;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
		CHECK_SAME(base2.Get(), base1, HEX);
	}

	/* Constructor from pointer from same type
	 * (const to non-const) causes compile error */
#if 0
	const CBaseA *base1 = new CBaseA;
	CBaseAPtr base2(base1);
#endif

	TEST_CASE("Should succeed from derive type (non-const to non-const)") {
		CDerive *derive = new CDerive();
		CBaseAPtr base(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		CHECK_SAME(base.Get(), derive, HEX);
	}

	TEST_CASE("Should succeed from derive type (const to const)") {
		const CDerive *derive = new CDerive();
		CConstBaseAPtr base(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		CHECK_SAME(base.Get(), derive, HEX);
	}

	TEST_CASE("Should succeed from derive type (non-const to const)") {
		CDerive *derive = new CDerive();
		CConstBaseAPtr base(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		CHECK_SAME(base.Get(), derive, HEX);
	}

	/* Constructor from pointer from derive type
	 * (const to non-const) causes compile error */
#if 0
	const CDerive *derive = new CDerive();
	CBaseAPtr base(derive);
#endif

	TEST_CASE("Should succeed from a valid base type (non-const to non-const)") {
		CBaseA *base = new CDerive();
		CDerivePtr derive(base);
		/* For non-const instance, 2 weak ref will be hold.
		 * One for non-const weakptr and the other for const weakptr */
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME(derive.Get(), base, HEX);
	}

	TEST_CASE("Should succeed from a valid base type (const to const)") {
		const CBaseA *base = new CDerive();
		CConstDerivePtr derive(base);
		/* For const instance, 1 weak ref will be hold.
		 * non-const weakptr will be nullptr. */
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME(derive.Get(), base, HEX);
	}

	TEST_CASE("Should succeed from a valid base type (non-const to const)") {
		CBaseA *base = new CDerive();
		CConstDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME(derive.Get(), base, HEX);
	}

	/* Constructor from pointer from a valid base type
	 * (const to non-const) causes compile error */
#if 0
	const CBaseA *base = new CDerive();
	CDerivePtr derive(base);
#endif

	TEST_CASE("Should throw error from an invalid base type") {
		CBaseA *base = new CBaseA;
		const CBaseA *cbase = base;
		CHECK_THROW(CDerivePtr derive(base));
		CHECK_THROW(CConstDerivePtr derive(cbase));
		CHECK_THROW(CConstDerivePtr derive(base));
	/* Constructor from pointer from an invalid base type
	 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(CDerivPtr derive(cbase));;
#endif
	}

	TEST_CASE("The customer deleter should work") {
		int i = 0;
		{
			CBaseA *base1 = new CBaseA;
			CBaseAPtr base2(base1, [&](CBaseA *ptr) {
				i = 1;
				delete ptr;
			});
		}

		CHECK(1 == i, "i: ", DEC(i));
	}
}

DEFINE_TEST_GROUP(SharedBaseConstructor)
{
	TEST_CASE("Should throw error if input is nullptr") {
		CHECK_THROW(CBaseAPtr base((CSharedBase<CBaseA> *)(nullptr)));
	}

	TEST_CASE("Should work if input is NOT nullptr") {
		CBaseAPtr base(AllocCreateSharedBase<CBaseA>());
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}
}

DEFINE_TEST_GROUP(SharedPtrLrefConstructor)
{
	TEST_CASE("Should be nullptr if input is nullptr") {
		CBaseAPtr base1(nullptr);
		CBaseAPtr base2(base1);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Should work from same type (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
	}

	TEST_CASE("Should work from same type (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
	}

	TEST_CASE("Should work from same type (non-const to const)") {
		CBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1, base2);
	}

	/* Constructor from CSharedPtr (lref) same type
	 * (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base1;
	CBaseAPtr base2(base1);
#endif

	TEST_CASE("Should work from derive (non-const to non-const)") {
		CDerivePtr derive;
		CBaseAPtr base(derive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(base, derive);
	}

	TEST_CASE("Should work from derive (const to const)") {
		CConstDerivePtr derive;
		CConstBaseAPtr base(derive);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_SAME_PTR(base, derive);
	}

	TEST_CASE("Should work from derive (non-const to const)") {
		CDerivePtr derive;
		CConstBaseAPtr base(derive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(base, derive);
	}

	/* Constructor from CSharedPtr (lref) from derive
	 * (const to non-const) causes compile error */
#if 0
	CConstDerivePtr derive;
	CBaseAPtr base(derive);
#endif

	TEST_CASE("Should work from a valid base (non-const to non-const)") {
		CBaseAPtr base(new CDerive());
		CDerivePtr derive(base);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base, derive);
	}

	TEST_CASE("Should work from a valid base (const to const)") {
		CConstBaseAPtr base(new CDerive());
		CConstDerivePtr derive(base);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_SAME_PTR(base, derive);
	}

	TEST_CASE("Should work from a valid base (non-const to const)") {
		CBaseAPtr base(new CDerive());
		CConstDerivePtr derive(base);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_SAME_PTR(base, derive);
	}

	/* Constructor from CSharedPtr (lref) from a valid base
	 * (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base(new CDerive());
	CDerivePtr derive(base);
#endif

	TEST_CASE("Should work from an invalid base") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CHECK_THROW(CDerivePtr derive(base));
		CHECK_THROW(CConstDerivePtr derive(base));
		CHECK_THROW(CConstDerivePtr derive(cbase));
		/* Constructor from CSharedPtr (lref) from an invalid base type
		 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(CDerivePtr derive(cbase));
#endif
	}
}

DEFINE_TEST_GROUP(SharedPtrRrefConstructor)
{
	TEST_CASE("Should be nullptr if input is nullptr") {
		CBaseAPtr base1(nullptr);
		CBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base2);
	}


	TEST_CASE("Should work from same type (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
	}

	TEST_CASE("Should work from same type (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
	}

	TEST_CASE("Should work from same type (non-const to const)") {
		CBaseAPtr base1;
		CConstBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
	}

	/* Constructor from CSharedPtr (rref) from same type
	 * (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base1;
	CBaseAPtr base2(std::move(base1));
#endif

	TEST_CASE("Should work from derive (non-const to non-const)") {
		CDerivePtr derive;
		CBaseAPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 3);
	}

	TEST_CASE("Should work from derive (const to const)") {
		CConstDerivePtr derive;
		CConstBaseAPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 2);
	}

	TEST_CASE("Should work from derive (non-const to const)") {
		CDerivePtr derive;
		CConstBaseAPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 3);
	}

	/* Constructor from CSharedPtr (rref) from derive
	 * (const to non-const) causes compile error */
#if 0
	CConstDerivePtr derive;
	CBaseAPtr base(std::move(derive));
#endif

	TEST_CASE("Should work from a valid base (non-const to non-const)") {
		CDerivePtr derive1;
		CBaseAPtr base(derive1);
		CDerivePtr derive2(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive1, 2, 3)
		CHECK_DERIVE(derive2, 2, 3);
	}

	TEST_CASE("Should work from a valid base (const to const)") {
		CConstDerivePtr derive1;
		CConstBaseAPtr base(derive1);
		CConstDerivePtr derive2(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive1, 2, 2)
		CHECK_DERIVE(derive2, 2, 2);
	}

	TEST_CASE("Should work from a valid base (non-const to const)") {
		CDerivePtr derive1;
		CBaseAPtr base(derive1);
		CConstDerivePtr derive2(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive1, 2, 3)
		CHECK_DERIVE(derive2, 2, 3);
	}

	/* Constructor from CSharedPtr (rref) from a valid base
	 * (const to non-const) causes compile error */
#if 0
	CConstDerivePtr derive1;
	CConstBaseAPtr base(derive1);
	CDerivePtr derive2(std::move(base));
#endif
}

DEFINE_TEST_GROUP(SharedPtrMixConstructor)
{
	TEST_CASE("Should work for lref, lref, lref") {
		CTypeDeriveConstructorPtr i(1);
		CTypeDeriveConstructorPtr j(2);
		CTypeDeriveConstructorPtr k(3);

		CDerivePtr derive(i, j, k);
		CHECK_DERIVE(derive, 1, 3);
		CHECK(100 + 1 + 2 + 3 == derive->Get(),
				"derive->Get(): ", DEC(derive->Get()));
	}

	TEST_CASE("Should work for lref, rref, lref") {
		CTypeDeriveConstructorPtr i(1);
		CTypeDeriveConstructorPtr j(2);
		CTypeDeriveConstructorPtr k(3);

		CDerivePtr derive(i, std::move(j), k);
		CHECK_DERIVE(derive, 1, 3);
		CHECK(200 + 1 + 2 + 3 == derive->Get(),
				"derive->Get(): ", DEC(derive->Get()));
	}

	TEST_CASE("Should work for lref, rref, rref") {
		CTypeDeriveConstructorPtr i(1);
		CTypeDeriveConstructorPtr j(2);
		CTypeDeriveConstructorPtr k(3);

		CDerivePtr derive(i, std::move(j), std::move(k));
		CHECK_DERIVE(derive, 1, 3);
		CHECK(200 + 1 + 2 + 3 == derive->Get(),
				"derive->Get(): ", DEC(derive->Get()));
	}
}

void Constructor(void)
{
	START_TEST();

	RUN_TEST_GROUP(DefaultConstructor);
	RUN_TEST_GROUP(NullConstructor);
	RUN_TEST_GROUP(CopyConstructor);
	RUN_TEST_GROUP(MoveConstructor);
	RUN_TEST_GROUP(PointerConstructor);
	RUN_TEST_GROUP(SharedBaseConstructor);
	RUN_TEST_GROUP(SharedPtrLrefConstructor);
	RUN_TEST_GROUP(SharedPtrRrefConstructor);
	RUN_TEST_GROUP(SharedPtrMixConstructor);

	STOP_TEST();
}

