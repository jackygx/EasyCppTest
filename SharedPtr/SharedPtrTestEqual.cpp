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
	TEST_CASE("Test CBaseAPtr = nullptr (non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = nullptr;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CBaseBPtr = nullptr (non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = nullptr;
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CDerivePtr = nullptr (non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = nullptr;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_EMPTY(derive2);
	}

	TEST_CASE("Test CConstBaseAPtr = nullptr (const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = nullptr;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CConstBaseBPtr = nullptr (const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = nullptr;
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CConstDerivePtr = nullptr (const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = nullptr;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_EMPTY(derive2);
	}
}

DEFINE_TEST_GROUP(EqualFromSharedPtrLref)
{
	TEST_CASE("Test CBaseAPtr = CBaseAPtr (nullptr) (non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3(nullptr);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CBaseBPtr = CBaseBPtr (nullptr) (non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CBaseBPtr base3(nullptr);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_EMPTY(base3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CDerivePtr = CDerivePtr (nullptr) (non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3(nullptr);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_EMPTY(derive3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = derive3;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_EMPTY(derive2);
		CHECK_EMPTY(derive3);
	}

	TEST_CASE("Test CConstBaseAPtr = CBaseAPtr/CConstBaseAPtr (nullptr)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CBaseAPtr base3(nullptr);
		CConstBaseAPtr base4(base1);
		CConstBaseAPtr base5(nullptr);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_BASEA(base2, CI_BASEA, 3, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 3, 1);
		CHECK_EMPTY(base5);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base1.Get(), base4.Get());

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);

		base4 = base5;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base4);
		CHECK_EMPTY(base5);
	}

	TEST_CASE("Test CBaseBPtr = CBaseBPtr/CConstBaseBPtr (nullptr)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CBaseBPtr base3(nullptr);
		CConstBaseBPtr base4(base1);
		CConstBaseBPtr base5(nullptr);
		CHECK_BASEB(base1, CI_BASEB, 3, 2);
		CHECK_BASEB(base2, CI_BASEB, 3, 2);
		CHECK_EMPTY(base3);
		CHECK_BASEB(base4, CI_BASEB, 3, 2);
		CHECK_EMPTY(base5);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base1.Get(), base4.Get());

		base2 = base3;
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base4, CI_BASEB, 2, 2);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);

		base4 = base5;
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_EMPTY(base4);
		CHECK_EMPTY(base5);
	}

	TEST_CASE("Test CDerivePtr = CDerivePtr/CConstDerivePtr (nullptr)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3(nullptr);
		CConstDerivePtr derive4(derive1);
		CConstDerivePtr derive5(nullptr);
		CHECK_DERIVE(derive1, 3, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_EMPTY(derive3);
		CHECK_DERIVE(derive4, 3, 2);
		CHECK_EMPTY(derive5);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive4.Get());

		derive2 = derive3;
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_EMPTY(derive2);
		CHECK_EMPTY(derive3);

		derive4 = derive5;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_EMPTY(derive4);
		CHECK_EMPTY(derive5);
	}

	TEST_CASE("Test CBaseAPtr = CBaseAPtr (non-const = non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2.Get(), base3.Get());
	}

	TEST_CASE("Test CBaseBPtr = CBaseBPtr (non-const = non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CBaseBPtr base3;
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_BASEB(base3, CI_BASEB, 1, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_BASEB(base3, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base2.Get(), base3.Get());
	}

	TEST_CASE("Test CDerivePtr = CDerivePtr (non-const = non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 1, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = derive3;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_SAME_PTR(derive3.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CConstBaseAPtr (const = const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstBaseAPtr base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2.Get(), base3.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CConstBaseBPtr (const = const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CConstBaseBPtr base3;
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_BASEB(base3, CI_BASEB, 1, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_BASEB(base3, CI_BASEB, 2, 2);
		CHECK_SAME_PTR(base2.Get(), base3.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CConstDerivePtr (const = const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 1, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = derive3;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CBaseAPtr (const = non-const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CBaseAPtr base3;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2.Get(), base3.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CBaseBPtr (const = non-const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CBaseBPtr base3;
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_BASEB(base3, CI_BASEB, 1, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = base3;
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_BASEB(base3, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base2.Get(), base3.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CDerivePtr (const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 1, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = derive3;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_SAME_PTR(derive3.Get(), derive2.Get());
	}

	/* Equal from CSharedPtr (lref) same type
	 * (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base1;
	CBaseAPtr base2;
	base2 = base1;
#endif

	TEST_CASE("Test CBaseAPtr = CDerivePtr (non-const = non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CDerivePtr derive;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = derive;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base2.Get(), derive.Get());
	}

	TEST_CASE("Test CBaseBPtr = CDerivePtr (non-const = non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CDerivePtr derive;
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = derive;
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_BASEB(base2, CI_BASEB_DERIVE, 2, 5);
		CHECK_DERIVE(derive, 2, 5);
		CHECK_SAME_PTR(base2.Get(), derive.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CConstDerivePtr (const = const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstDerivePtr derive;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = derive;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_SAME_PTR(base2.Get(), derive.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CConstDerivePtr (const = const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CConstDerivePtr derive;
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = derive;
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base2.Get(), derive.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CDerivePtr (const = non-const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CDerivePtr derive;
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = derive;
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base2.Get(), derive.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CDerivePtr (const = non-const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CDerivePtr derive;
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = derive;
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB_DERIVE, 2, 4);
		CHECK_DERIVE(derive, 2, 4);
		CHECK_SAME_PTR(base2.Get(), derive.Get());
	}

	/* (non-const = const) causes compile error */
#if 0
	CBaseAPtr base;
	CConstDerivePtr derive;
	base = derive;
#endif

	TEST_CASE("Test CDerivePtr = CBaseAPtr (valid) (non-const = non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 3);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());
	}

	TEST_CASE("Test CDerivePtr = CBaseBPtr (valid) (non-const = non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseBPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 5);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 3, 5);
		CHECK_DERIVE(derive3, 3, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 3, 5);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CConstBaseAPtr (valid) (const = const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_DERIVE(derive3, 3, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 2);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CConstBaseBPtr (valid) (const = const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstBaseBPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 3, 3);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CBaseAPtr (valid) (const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_DERIVE(derive3, 3, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 3, 3);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CBaseBPtr (valid) (const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseBPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 5);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = base;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 3, 5);
		CHECK_DERIVE(derive3, 3, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 3, 5);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());
	}

	/* Equal from CSharedPtr (lref) from a valid base
	 * (const to non-const) causes compile error */
#if 0
	CDerivePtr derive1;
	CConstDerivePtr derive2;
	CConstBaseAPtr base(derive2);
	derive1 = base;
#endif

	TEST_CASE("Test CDerivePtr = CBaseAPtr (invalid)") {
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

	TEST_CASE("Test CDerivePtr = CBaseBPtr (invalid)") {
		CBaseBPtr base;
		CConstBaseBPtr cbase;
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
	TEST_CASE("Test CBaseAPtr = CBaseAPtr (nullptr) (non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3(nullptr);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = std::move(base3);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CBaseBPtr = CBaseBPtr (nullptr) (non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CBaseBPtr base3(nullptr);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_EMPTY(base3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = std::move(base3);
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CDerivePtr = CDerivePtr (nullptr) (non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3(nullptr);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_EMPTY(derive3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = std::move(derive3);
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_EMPTY(derive2);
		CHECK_EMPTY(derive3);
	}

	TEST_CASE("Test CConstBaseAPtr = CBaseAPtr/CConstBaseAPtr (nullptr)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CBaseAPtr base3(nullptr);
		CConstBaseAPtr base4(base1);
		CConstBaseAPtr base5(nullptr);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_BASEA(base2, CI_BASEA, 3, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 3, 1);
		CHECK_EMPTY(base5);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base1.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);

		base4 = std::move(base5);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_EMPTY(base4);
		CHECK_EMPTY(base5);
	}

	TEST_CASE("Test CBaseBPtr = CBaseBPtr/CConstBaseBPtr (nullptr)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CBaseBPtr base3(nullptr);
		CConstBaseBPtr base4(base1);
		CConstBaseBPtr base5(nullptr);
		CHECK_BASEB(base1, CI_BASEB, 3, 2);
		CHECK_BASEB(base2, CI_BASEB, 3, 2);
		CHECK_EMPTY(base3);
		CHECK_BASEB(base4, CI_BASEB, 3, 2);
		CHECK_EMPTY(base5);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base1.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base4, CI_BASEB, 2, 2);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);

		base4 = std::move(base5);
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_EMPTY(base4);
		CHECK_EMPTY(base5);
	}

	TEST_CASE("Test CDerivePtr = CDerivePtr/CConstDerivePtr (nullptr)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3(nullptr);
		CConstDerivePtr derive4(derive1);
		CConstDerivePtr derive5(nullptr);
		CHECK_DERIVE(derive1, 3, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_EMPTY(derive3);
		CHECK_DERIVE(derive4, 3, 2);
		CHECK_EMPTY(derive5);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive4.Get());

		derive2 = std::move(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_EMPTY(derive2);
		CHECK_EMPTY(derive3);

		derive4 = std::move(derive5);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_EMPTY(derive4);
		CHECK_EMPTY(derive5);
	}

	TEST_CASE("Test CBaseAPtr = CBaseAPtr (non-const = non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CBaseAPtr base3;
		CBaseAPtr base4(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base3.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2.Get(), base4.Get());
	}

	TEST_CASE("Test CBaseBPtr = CBaseBPtr (non-const = non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CBaseBPtr base3;
		CBaseBPtr base4(base3);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_BASEB(base3, CI_BASEB, 2, 3);
		CHECK_BASEB(base4, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base3.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_EMPTY(base3);
		CHECK_BASEB(base4, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base2.Get(), base4.Get());
	}

	TEST_CASE("Test CDerivePtr = CDerivePtr (non-const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstDerivePtr derive4(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), derive4.Get());

		derive2 = std::move(derive3);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_EMPTY(derive3);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_SAME_PTR(derive2.Get(), derive4.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CConstBaseAPtr (const = const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstBaseAPtr base3;
		CConstBaseAPtr base4(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base3.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2.Get(), base4.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CConstBaseBPtr (const = const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CConstBaseBPtr base3;
		CConstBaseBPtr base4(base3);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_BASEB(base3, CI_BASEB, 2, 2);
		CHECK_BASEB(base4, CI_BASEB, 2, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base3.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_EMPTY(base3);
		CHECK_BASEB(base4, CI_BASEB, 2, 2);
		CHECK_SAME_PTR(base2.Get(), base4.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CConstDerivePtr (const = const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstDerivePtr derive4(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), derive4.Get());

		derive2 = std::move(derive3);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_EMPTY(derive3);
		CHECK_DERIVE(derive4, 2, 2);
		CHECK_SAME_PTR(derive2.Get(), derive4.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CBaseAPtr (const = non-const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CBaseAPtr base3;
		CBaseAPtr base4(base3);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_BASEA(base3, CI_BASEA, 2, 1);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(base3.Get(), base4.Get());

		base2 = std::move(base3);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_EMPTY(base3);
		CHECK_BASEA(base4, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base2.Get(), base4.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CBaseBPtr (const = non-const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CBaseBPtr base3;
		CBaseBPtr base4(base3);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_BASEB(base3, CI_BASEB, 2, 3);
		CHECK_BASEB(base4, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		base2 = std::move(base3);
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_EMPTY(base3);
		CHECK_BASEB(base4, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base2.Get(), base4.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CDerivePtr (const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CDerivePtr derive4(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive4, 2, 3);
		CHECK_DERIVE(derive4, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), derive4.Get());

		derive2 = std::move(derive3);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_EMPTY(derive3);
		CHECK_DERIVE(derive4, 2, 3);
		CHECK_SAME_PTR(derive2.Get(), derive4.Get());
	}

	/* Equal from CSharedPtr (lref) same type
	 * (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base1;
	CBaseAPtr base2;
	base2 = base1;
#endif

	TEST_CASE("Test CBaseAPtr = CDerivePtr (non-const = non-const)") {
		CBaseAPtr base1;
		CBaseAPtr base2(base1);
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		base2 = std::move(derive1);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base2.Get(), derive2.Get());
	}

	TEST_CASE("Test CBaseBPtr = CDerivePtr (non-const = non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		base2 = std::move(derive1);
		CHECK_BASEB(base1, CI_BASEB, 1, 3);
		CHECK_BASEB(base2, CI_BASEB_DERIVE, 2, 5);
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 2, 5);
		CHECK_SAME_PTR(base2.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CConstDerivePtr (const = const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		base2 = std::move(derive1);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 2);
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(base2.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CConstDerivePtr (const = const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		base2 = std::move(derive1);
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB_DERIVE, 2, 3);
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base2.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseAPtr = CDerivePtr (const = non-const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		base2 = std::move(derive1);
		CHECK_BASEA(base1, CI_BASEA, 1, 1);
		CHECK_BASEA(base2, CI_BASEA_DERIVE, 2, 3);
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base2.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseBPtr = CDerivePtr (const = non-const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		base2 = std::move(derive1);
		CHECK_BASEB(base1, CI_BASEB, 1, 2);
		CHECK_BASEB(base2, CI_BASEB_DERIVE, 2, 4);
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 2, 4);
		CHECK_SAME_PTR(base2.Get(), derive2.Get());
	}

	/* (non-const = const) causes compile error */
#if 0
	CBaseAPtr base;
	CConstDerivePtr derive;
	base = derive;
#endif

	TEST_CASE("Test CDerivePtr = CBaseAPtr (valid) (non-const = non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = std::move(base);
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_EMPTY(base);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	TEST_CASE("Test CDerivePtr = CBaseBPtr (valid) (non-const = non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseBPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 5);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = std::move(base);
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 2, 5);
		CHECK_DERIVE(derive3, 2, 5);
		CHECK_EMPTY(base);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CConstBaseAPtr (valid) (const = const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = std::move(base);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 2);
		CHECK_EMPTY(base);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CConstBaseBPtr (valid) (const = const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CConstDerivePtr derive3;
		CConstBaseBPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = std::move(base);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_EMPTY(base);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CBaseAPtr (valid) (const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseAPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = std::move(base);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_DERIVE(derive3, 2, 3);
		CHECK_EMPTY(base);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	TEST_CASE("Test CConstDerivePtr = CBaseBPtr (valid) (const = non-const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CDerivePtr derive3;
		CBaseBPtr base(derive3);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_DERIVE(derive3, 2, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 5);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK_SAME_PTR(derive3.Get(), base.Get());

		derive2 = std::move(base);
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 2, 5);
		CHECK_DERIVE(derive3, 2, 5);
		CHECK_EMPTY(base);
		CHECK_SAME_PTR(derive2.Get(), derive3.Get());
	}

	/* Equal from CSharedPtr (lref) from a valid base
	 * (const to non-const) causes compile error */
#if 0
	CDerivePtr derive1;
	CConstDerivePtr derive2;
	CConstBaseAPtr base(derive2);
	derive1 = base;
#endif

	TEST_CASE("Test CDerivePtr = CBaseAPtr (invalid)") {
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

	TEST_CASE("Test CDerivePtr = CBaseBPtr (invalid)") {
		CBaseBPtr base;
		CConstBaseBPtr cbase;
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
	TEST_CASE("Test CDerivePtr = CDerivePtr(10) (non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = 10;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK_DIFFERENT_PTR(derive1.Get(), derive2.Get());
		CHECK(derive2->Get() == 10, "Derive2: %d", derive2->Get());
	}

	TEST_CASE("Test CConstDerivePtr = CDerivePtr(10) (const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = 10;
		CHECK_DERIVE(derive1, 1, 2);
		CHECK_DERIVE(derive2, 1, 2);
		CHECK_DIFFERENT_PTR(derive1.Get(), derive2.Get());
		CHECK(derive2->Get() == 10, "Derive2: %d", derive2->Get());
	}

	TEST_CASE("Test CDerivePtr = CTypeDeriveImplicitConvertPtr") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CTypeDeriveImplicitConvertPtr val(1111);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = val;
		CHECK_DERIVE(derive1, 1, 3);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK_DIFFERENT_PTR(derive1.Get(), derive2.Get());
		CHECK(derive2->Get() == 1111, "Derive2: %d", derive2->Get());
	}
}

DEFINE_TEST_GROUP(EqualFromOverload)
{
	TEST_CASE("Test CDerivePtr = CTypeDeriveEqual") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		derive2 = CTypeDeriveEqual(10);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
		CHECK(derive1->Get() == 10, "Derive1: %d", derive1->Get());
		CHECK(derive2->Get() == 10, "Derive2: %d", derive2->Get());
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

