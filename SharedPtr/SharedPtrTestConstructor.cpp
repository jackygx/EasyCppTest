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
	TEST_CASE("Test IBaseCPtr") {
		IBaseCPtr base;
		CHECK_EMPTY(base);
	}

	TEST_CASE("Test IConstBaseCPtr") {
		IConstBaseCPtr base;
		CHECK_EMPTY(base);
	}

	TEST_CASE("Test CBaseAPtr(non-const)") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CBaseBPtr(non-const)") {
		CBaseBPtr base;
		CHECK_BASEB(base, CI_BASEB, 1, 3);
	}

	TEST_CASE("Test CDerivePtr(non-const)") {
		CDerivePtr derive;
		CHECK_DERIVE(derive, 1, 3);
	}

	TEST_CASE("Test CConstBaseAPtr(const)") {
		CConstBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CConstBaseBPtr(const)") {
		CConstBaseBPtr base;
		CHECK_BASEB(base, CI_BASEB, 1, 2);
	}

	TEST_CASE("Test CConstDerivePtr(const)") {
		CConstDerivePtr derive;
		CHECK_DERIVE(derive, 1, 2);
	}
}

DEFINE_TEST_GROUP(NullConstructor)
{
	TEST_CASE("Test CBaseAPtr(non-const)") {
		CBaseAPtr base(nullptr);
		CHECK_EMPTY(base);
	}

	TEST_CASE("Test CBaseBPtr(non-const)") {
		CBaseBPtr base(nullptr);
		CHECK_EMPTY(base);
	}

	TEST_CASE("Test CDerivePtr(non-const)") {
		CDerivePtr derive(nullptr);
		CHECK_EMPTY(derive);
	}

	TEST_CASE("Test CConstBaseAPtr(const)") {
		CConstBaseAPtr base(nullptr);
		CHECK_EMPTY(base);
	}

	TEST_CASE("Test CConstBaseBPtr(const)") {
		CConstBaseBPtr base(nullptr);
		CHECK_EMPTY(base);
	}

	TEST_CASE("Test CConstDerivePtr(const)") {
		CConstDerivePtr derive(nullptr);
		CHECK_EMPTY(derive);
	}
}

DEFINE_TEST_GROUP(CopyConstructor)
{
	TEST_CASE("Test CBaseAPtr(nullptr) to CBaseAPtr/CConstBaseAPtr") {
		CBaseAPtr base1(nullptr);
		CBaseAPtr base2(base1);
		CConstBaseAPtr base3(base1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CBaseBPtr(nullptr) to CBaseBPtr/CConstBaseBPtr") {
		CBaseBPtr base1(nullptr);
		CBaseBPtr base2(base1);
		CConstBaseBPtr base3(base1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CDerivePtr(nullptr) to CDerivePtr/CConstDerivePtr") {
		CDerivePtr derive1(nullptr);
		CDerivePtr derive2(derive1);
		CConstDerivePtr derive3(derive1);
		CHECK_EMPTY(derive2);
		CHECK_EMPTY(derive3);
	}

	TEST_CASE("Test CConstBaseAPtr(nullptr) to CConstBaseAPtr") {
		CConstBaseAPtr base1(nullptr);
		CConstBaseAPtr basea2(base1);
		CHECK_EMPTY(basea2);
	}

	TEST_CASE("Test CConstBaseBPtr(nullptr) to CConstBaseBPtr") {
		CConstBaseBPtr base1(nullptr);
		CConstBaseBPtr base2(base1);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CConstDerivePtr(nullptr) to CConstDerivePtr") {
		CConstDerivePtr derive1(nullptr);
		CConstDerivePtr derive2(derive1);
		CHECK_EMPTY(derive2);
	}

	TEST_CASE("Test CBaseAPtr to CBaseAPtr (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr basea2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(basea2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), basea2.Get());
	}

	TEST_CASE("Test CBaseBPtr to CBaseBPtr (non-const to non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(base1);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CDerivePtr to CDerivePtr (non-const to non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseAPtr to CConstBaseAPtr (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CConstBaseBPtr to CConstBaseBPtr (const to const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CHECK_BASEB(base1, CI_BASEB, 2, 2);
		CHECK_BASEB(base2, CI_BASEB, 2, 2);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CConstDerivePtr to CConstDerivePtr (const to const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 2);
		CHECK_DERIVE(derive2, 2, 2);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
	}

	TEST_CASE("Test CBaseAPtr to CConstBaseAPtr (non-const to const)") {
		CBaseAPtr base1;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_BASEA(base2, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CBaseBPtr to CConstBaseBPtr (non-const to const)") {
		CBaseBPtr base1;
		CConstBaseBPtr base2(base1);
		CHECK_BASEB(base1, CI_BASEB, 2, 3);
		CHECK_BASEB(base2, CI_BASEB, 2, 3);
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CDerivePtr to CConstDerivePtr (non-const to const)") {
		CDerivePtr derive1;
		CConstDerivePtr derive2(derive1);
		CHECK_DERIVE(derive1, 2, 3);
		CHECK_DERIVE(derive2, 2, 3);
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
	}

	/* (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base1;
	CBaseAPtr base2(base1);
#endif
}

DEFINE_TEST_GROUP(MoveConstructor)
{
	TEST_CASE("Test CBaseAPtr(nullptr) to CBaseAPtr/CConstBaseAPtr") {
		CBaseAPtr base1(nullptr);
		CBaseAPtr base2(std::move(base1));
		CConstBaseAPtr base3(std::move(base1));
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CBaseBPtr(nullptr) to CBaseBPtr/CConstBaseBPtr") {
		CBaseBPtr base1(nullptr);
		CBaseBPtr base2(std::move(base1));
		CConstBaseBPtr base3(std::move(base1));
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test CDerivePtr(nullptr) to CDerivePtr/CConstDerivePtr") {
		CDerivePtr derive1(nullptr);
		CDerivePtr derive2(std::move(derive1));
		CConstDerivePtr derive3(std::move(derive1));
		CHECK_EMPTY(derive2);
		CHECK_EMPTY(derive3);
	}

	TEST_CASE("Test CConstBaseAPtr(nullptr) to CConstBaseAPtr") {
		CConstBaseAPtr base1(nullptr);
		CConstBaseAPtr basea2(std::move(base1));
		CHECK_EMPTY(basea2);
	}

	TEST_CASE("Test CConstBaseBPtr(nullptr) to CConstBaseBPtr") {
		CConstBaseBPtr base1(nullptr);
		CConstBaseBPtr base2(std::move(base1));
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CConstDerivePtr(nullptr) to CConstDerivePtr") {
		CConstDerivePtr derive1(nullptr);
		CConstDerivePtr derive2(std::move(derive1));
		CHECK_EMPTY(derive2);
	}

	TEST_CASE("Test CBaseAPtr to CBaseAPtr (non-const to non-const)") {
		CBaseAPtr base1;
		CBaseAPtr basea2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(basea2, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CBaseBPtr to CBaseBPtr (non-const to non-const)") {
		CBaseBPtr base1;
		CBaseBPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEB(base2, CI_BASEB, 1, 3);
	}

	TEST_CASE("Test CDerivePtr to CDerivePtr (non-const to non-const)") {
		CDerivePtr derive1;
		CDerivePtr derive2(std::move(derive1));
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 1, 3);
	}

	TEST_CASE("Test CConstBaseAPtr to CConstBaseAPtr (const to const)") {
		CConstBaseAPtr base1;
		CConstBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CConstBaseBPtr to CConstBaseBPtr (const to const)") {
		CConstBaseBPtr base1;
		CConstBaseBPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEB(base2, CI_BASEB, 1, 2);
	}

	TEST_CASE("Test CConstDerivePtr to CConstDerivePtr (const to const)") {
		CConstDerivePtr derive1;
		CConstDerivePtr derive2(std::move(derive1));
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 1, 2);
	}

	TEST_CASE("Test CBaseAPtr to CConstBaseAPtr (non-const to const)") {
		CBaseAPtr base1;
		CConstBaseAPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CBaseBPtr to CConstBaseBPtr (non-const to const)") {
		CBaseBPtr base1;
		CConstBaseBPtr base2(std::move(base1));
		CHECK_EMPTY(base1);
		CHECK_BASEB(base2, CI_BASEB, 1, 3);
	}

	TEST_CASE("Test CDerivePtr to CConstDerivePtr (non-const to const)") {
		CDerivePtr derive1;
		CConstDerivePtr derive2(std::move(derive1));
		CHECK_EMPTY(derive1);
		CHECK_DERIVE(derive2, 1, 3);
	}
}

DEFINE_TEST_GROUP(PointerConstructor)
{
	TEST_CASE("Test nullptr to CBaseAPtr/CConstBaseAPtr") {
		CBaseA *base1 = nullptr;
		CBaseAPtr base2(base1);
		CConstBaseAPtr base3(base1);
		CHECK_EMPTY(base2);
		CHECK_EMPTY(base3);
	}

	TEST_CASE("Test nullptr to CConstBaseAPtr (const)") {
		const CBaseA *base1 = nullptr;
		CConstBaseAPtr base2(base1);
		CHECK_EMPTY(base2);
	}

	TEST_CASE("Test CBaseA * to CBaseAPtr (non-const to non-const)") {
		CBaseA *base1 = new CBaseA;
		CBaseAPtr base2(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base2.Get(), base1);
	}

	TEST_CASE("Test CBaseB * to CBaseBPtr (non-const to non-const)") {
		CBaseB *base1 = new CBaseB;
		CBaseBPtr base2(base1);
		CHECK_BASEB(base2, CI_BASEB, 1, 3);
		CHECK_SAME_PTR(base2.Get(), base1);
	}

	TEST_CASE("Test CDerive * to CDerivePtr (non-const to non-const)") {
		CDerive *derive1 = new CDerive;
		CDerivePtr derive2(derive1);
		CHECK_DERIVE(derive2, 1, 3);
		CHECK_SAME_PTR(derive2.Get(), derive1);
	}

	TEST_CASE("Test const CBaseA * to CConstBaseAPtr (const to const)") {
		const CBaseA *base1 = new CBaseA;
		CConstBaseAPtr base2(base1);
		CHECK_BASEA(base2, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(base2.Get(), base1);
	}

	TEST_CASE("Test const CBaseB * to CConstBaseBPtr (const to const)") {
		const CBaseB *base1 = new CBaseB;
		CConstBaseBPtr base2(base1);
		CHECK_BASEB(base2, CI_BASEB, 1, 2);
		CHECK_SAME_PTR(base2.Get(), base1);
	}

	TEST_CASE("Test const CDerive * to CConstDerivePtr (const to const)") {
		const CDerive *derive1 = new CDerive;
		CConstDerivePtr derive2(derive1);
		CHECK_DERIVE(derive2, 1, 2);
		CHECK_SAME_PTR(derive2.Get(), derive1);
	}

	TEST_CASE("Test CBaseA * to CConstBaseAPtr (non-const to const)") {
		CBaseA *basea1 = new CBaseA;
		CConstBaseAPtr basea2(basea1);
		CHECK_BASEA(basea2, CI_BASEA, 1, 1);
		CHECK_SAME_PTR(basea2.Get(), basea1);
	}

	TEST_CASE("Test CBaseB * to CConstBaseBPtr (non-const to const)") {
		CBaseB *base1 = new CBaseB;
		CConstBaseBPtr base2(base1);
		CHECK_BASEB(base2, CI_BASEB, 1, 2);
		CHECK_SAME_PTR(base2.Get(), base1);
	}

	TEST_CASE("Test CDerive * to CConstDerivePtr (non-const to const)") {
		CDerive *derive1 = new CDerive;
		CConstDerivePtr derive2(derive1);
		CHECK_DERIVE(derive2, 1, 2);
		CHECK_SAME_PTR(derive2.Get(), derive1);
	}

	/* Constructor from pointer from same type
	 * (const to non-const) causes compile error */
#if 0
	const CBaseA *base1 = new CBaseA;
	CBaseAPtr base2(base1);
#endif

	TEST_CASE("Test CDerive * to CBaseAPtr (non-const to non-const)") {
		CDerive *derive = new CDerive();
		CBaseAPtr base(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		CHECK_SAME_PTR(base.Get(), derive);
	}

	TEST_CASE("Test CDerive * to CBaseBPtr (non-const to non-const)") {
		CDerive *derive = new CDerive();
		CBaseBPtr base(derive);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 3);
		CHECK_SAME_PTR(base.Get(), derive);
	}

	TEST_CASE("Test const CDerive * to CConstBaseAPtr (const to const)") {
		const CDerive *derive = new CDerive();
		CConstBaseAPtr base(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		CHECK_SAME_PTR(base.Get(), derive);
	}

	TEST_CASE("Test const CDerive * to CConstBaseBPtr (const to const)") {
		const CDerive *derive = new CDerive();
		CConstBaseBPtr base(derive);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 2);
		CHECK_SAME_PTR(base.Get(), derive);
	}

	TEST_CASE("Test CDerive * to CConstBaseAPtr (non-const to const)") {
		CDerive *derive = new CDerive();
		CConstBaseAPtr base(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		CHECK_SAME_PTR(base.Get(), derive);
	}

	TEST_CASE("Test CDerive * to CConstBaseBPtr (non-const to const)") {
		CDerive *derive = new CDerive();
		CConstBaseBPtr base(derive);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 2);
		CHECK_SAME_PTR(base.Get(), derive);
	}

	/* Constructor from pointer from derive type
	 * (const to non-const) causes compile error */
#if 0
	const CDerive *derive = new CDerive();
	CBaseAPtr base(derive);
#endif

	TEST_CASE("Test CBaseA *(valid) to CDerivePtr (non-const to non-const)") {
		CBaseA *base = new CDerive();
		CDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(derive.Get(), base);
	}

	TEST_CASE("Test CBaseB *(valid) to CDerivePtr (non-const to non-const)") {
		CBaseB *base = new CDerive();
		CDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 3);
		CHECK_SAME_PTR(derive.Get(), base);
	}

	TEST_CASE("Test const CBaseA *(valid) to CConstDerivePtr (const to const)") {
		const CBaseA *base = new CDerive();
		CConstDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(derive.Get(), base);
	}

	TEST_CASE("Test const CBaseB *(valid) to CConstDerivePtr (const to const)") {
		const CBaseB *base = new CDerive();
		CConstDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(derive.Get(), base);
	}

	TEST_CASE("Test CBaseA *(valid) to CConstDerivePtr (non-const to const)") {
		CBaseA *base = new CDerive();
		CConstDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(derive.Get(), base);
	}

	TEST_CASE("Test CBaseB *(valid) to CConstDerivePtr (non-const to const)") {
		CBaseB *base = new CDerive();
		CConstDerivePtr derive(base);
		CHECK_DERIVE(derive, 1, 2);
		CHECK_SAME_PTR(derive.Get(), base);
	}

	/* Constructor from pointer from a valid base type
	 * (const to non-const) causes compile error */
#if 0
	const CBaseA *base = new CDerive();
	CDerivePtr derive(base);
#endif

	TEST_CASE("Test CBaseA *(invalid) to CDerivePtr") {
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

	TEST_CASE("Test CBaseB *(invalid) to CDerivePtr") {
		CBaseB *base = new CBaseB;
		const CBaseB *cbase = base;
		CHECK_THROW(CDerivePtr derive(base));
		CHECK_THROW(CConstDerivePtr derive(cbase));
		CHECK_THROW(CConstDerivePtr derive(base));
	/* Constructor from pointer from an invalid base type
	 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(CDerivPtr derive(cbase));;
#endif
	}
}

static int FuncPointerDeleted = 0;
static uint64_t FuncPointerPtr = 0;

static void FuncPointerDeleterBaseA(CBaseA *base)
{
	FuncPointerDeleted = 1;
	FuncPointerPtr = (uint64_t)base;

	delete base;
}

static void FuncPointerDeleterBaseB(CBaseB *base)
{
	FuncPointerDeleted = 2;
	FuncPointerPtr = (uint64_t)base;

	delete base;
}

static void FuncPointerDeleterDerive(CDerive *derive)
{
	FuncPointerDeleted = 3;
	FuncPointerPtr = (uint64_t)derive;

	delete derive;
}

static void FuncPointerDeleterConstBaseA(const CBaseA *base)
{
	FuncPointerDeleted = 4;
	FuncPointerPtr = (uint64_t)base;

	delete base;
}

static void FuncPointerDeleterConstBaseB(const CBaseB *base)
{
	FuncPointerDeleted = 5;
	FuncPointerPtr = (uint64_t)base;

	delete base;
}

static void FuncPointerDeleterConstDerive(const CDerive *derive)
{
	FuncPointerDeleted = 6;
	FuncPointerPtr = (uint64_t)derive;

	delete derive;
}

DEFINE_TEST_GROUP(CustomerDeleter)
{
	TEST_CASE("Test function pointer for CBaseA (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseA *base = new CBaseA;

		{
			CBaseAPtr base2(base, FuncPointerDeleterBaseA);
			CHECK_BASEA(base2, CI_BASEA, 1, 1);
		}

		CHECK(1 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseB (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseB *base = new CBaseB;

		{
			CBaseBPtr base2(base, FuncPointerDeleterBaseB);
			CHECK_BASEB(base2, CI_BASEB, 1, 3);
		}

		CHECK(2 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;

		{
			CDerivePtr derive2(derive, FuncPointerDeleterDerive);
			CHECK_DERIVE(derive2, 1, 3);
		}

		CHECK(3 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CDerive => CBaseA (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;

		{
			CBaseAPtr base(derive, FuncPointerDeleterBaseA);
			CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		}

		CHECK(1 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CDerive => CBaseB (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;

		{
			CBaseBPtr base(derive, FuncPointerDeleterBaseB);
			CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 3);
		}

		CHECK(2 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)derive) == (FuncPointerPtr - 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseA => CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseA *base = new CDerive;

		{
			CDerivePtr derive(base, FuncPointerDeleterDerive);
			CHECK_DERIVE(derive, 1, 3);
		}

		CHECK(3 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseB => CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseB *base = new CDerive;

		{
			CDerivePtr derive(base, FuncPointerDeleterDerive);
			CHECK_DERIVE(derive, 1, 3);
		}

		CHECK(3 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)base) == (FuncPointerPtr + 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseA (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseA *base = new CBaseA;

		{
			CConstBaseAPtr base2(base, FuncPointerDeleterConstBaseA);
			CHECK_BASEA(base2, CI_BASEA, 1, 1);
		}

		CHECK(4 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseB (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseB *base = new CBaseB;

		{
			CConstBaseBPtr base2(base, FuncPointerDeleterConstBaseB);
			CHECK_BASEB(base2, CI_BASEB, 1, 2);
		}

		CHECK(5 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;

		{
			CConstDerivePtr derive2(derive, FuncPointerDeleterConstDerive);
			CHECK_DERIVE(derive2, 1, 2);
		}

		CHECK(6 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CDerive => CBaseA (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;

		{
			CConstBaseAPtr base(derive, FuncPointerDeleterConstBaseA);
			CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		}

		CHECK(4 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CDerive => CBaseB (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;

		{
			CConstBaseBPtr base(derive, FuncPointerDeleterConstBaseB);
			CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 2);
		}

		CHECK(5 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)derive) == (FuncPointerPtr - 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseA => CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseA *base = new CDerive;

		{
			CConstDerivePtr derive(base, FuncPointerDeleterConstDerive);
			CHECK_DERIVE(derive, 1, 2);
		}

		CHECK(6 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test function pointer for CBaseB => CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseB *base = new CDerive;

		{
			CConstDerivePtr derive(base, FuncPointerDeleterConstDerive);
			CHECK_DERIVE(derive, 1, 2);
		}

		CHECK(6 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)base) == (FuncPointerPtr + 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseA *base = new CBaseA;

		{
			CBaseAPtr base2(base, [](CBaseA *base) {
				FuncPointerDeleted = 7;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEA(base2, CI_BASEA, 1, 1);
		}

		CHECK(7 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseB *base = new CBaseB;

		{
			CBaseBPtr base2(base, [](CBaseB *base) {
				FuncPointerDeleted = 8;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEB(base2, CI_BASEB, 1, 3);
		}

		CHECK(8 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;

		{
			CDerivePtr derive2(derive, [](CDerive *derive) {
				FuncPointerDeleted = 9;
				FuncPointerPtr = (uint64_t)derive;
				delete derive;
			});
			CHECK_DERIVE(derive2, 1, 3);
		}

		CHECK(9 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseA (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;

		{
			CBaseAPtr base(derive, [](CBaseA *base) {
				FuncPointerDeleted = 7;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		}

		CHECK(7 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseB (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;

		{
			CBaseBPtr base(derive, [](CBaseB *base) {
				FuncPointerDeleted = 8;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 3);
		}

		CHECK(8 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)derive) == (FuncPointerPtr - 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA => CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseA *base = new CDerive;

		{
			CDerivePtr derive(base, [](CDerive *derive) {
				FuncPointerDeleted = 9;
				FuncPointerPtr = (uint64_t)derive;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 3);
		}

		CHECK(9 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB => CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseB *base = new CDerive;

		{
			CDerivePtr derive(base, [](CDerive *derive) {
				FuncPointerDeleted = 9;
				FuncPointerPtr = (uint64_t)derive;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 3);
		}

		CHECK(9 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)base) == (FuncPointerPtr + 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseA *base = new CBaseA;

		{
			CConstBaseAPtr base2(base, [](const CBaseA *base) {
				FuncPointerDeleted = 10;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEA(base2, CI_BASEA, 1, 1);
		}

		CHECK(10 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseB *base = new CBaseB;

		{
			CConstBaseBPtr base2(base, [](const CBaseB *base) {
				FuncPointerDeleted = 11;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEB(base2, CI_BASEB, 1, 2);
		}

		CHECK(11 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;

		{
			CConstDerivePtr derive2(derive, [](const CDerive *derive) {
				FuncPointerDeleted = 12;
				FuncPointerPtr = (uint64_t)derive;
				delete derive;
			});
			CHECK_DERIVE(derive2, 1, 2);
		}

		CHECK(12 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseA (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;

		{
			CConstBaseAPtr base(derive, [](const CBaseA *base) {
				FuncPointerDeleted = 10;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		}

		CHECK(10 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseB (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;

		{
			CConstBaseBPtr base(derive, [](const CBaseB *base) {
				FuncPointerDeleted = 11;
				FuncPointerPtr = (uint64_t)base;
				delete base;
			});
			CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 2);
		}

		CHECK(11 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)derive) == (FuncPointerPtr - 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA => CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseA *base = new CDerive;

		{
			CConstDerivePtr derive(base, [](const CDerive *derive) {
				FuncPointerDeleted = 12;
				FuncPointerPtr = (uint64_t)derive;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 2);
		}

		CHECK(12 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB => CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseB *base = new CDerive;

		{
			CConstDerivePtr derive(base, [](const CDerive *derive) {
				FuncPointerDeleted = 12;
				FuncPointerPtr = (uint64_t)derive;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 2);
		}

		CHECK(12 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(((uint64_t)base) == (FuncPointerPtr + 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (has closure) for CBaseA (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseA *base = new CBaseA;
		int i = 0;

		{
			CBaseAPtr base2(base, [&](CBaseA *base) {
				FuncPointerDeleted = 7;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEA(base2, CI_BASEA, 1, 1);
		}

		CHECK(7 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (has closure) for CBaseB (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseB *base = new CBaseB;
		int i = 0;

		{
			CBaseBPtr base2(base, [&](CBaseB *base) {
				FuncPointerDeleted = 8;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEB(base2, CI_BASEB, 1, 3);
		}

		CHECK(8 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (has closure) for CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;
		int i = 0;

		{
			CDerivePtr derive2(derive, [&](CDerive *derive) {
				FuncPointerDeleted = 9;
				FuncPointerPtr = (uint64_t)derive;
				i = 1;
				delete derive;
			});
			CHECK_DERIVE(derive2, 1, 3);
		}

		CHECK(9 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (has closure) for CDerive => CBaseA (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;
		int i = 0;

		{
			CBaseAPtr base(derive, [&](CBaseA *base) {
				FuncPointerDeleted = 7;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		}

		CHECK(7 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseB (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CDerive *derive = new CDerive;
		int i = 0;

		{
			CBaseBPtr base(derive, [&](CBaseB *base) {
				FuncPointerDeleted = 8;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 3);
		}

		CHECK(8 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK(((uint64_t)derive) == (FuncPointerPtr - 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA => CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseA *base = new CDerive;
		int i = 0;

		{
			CDerivePtr derive(base, [&](CDerive *derive) {
				FuncPointerDeleted = 9;
				FuncPointerPtr = (uint64_t)derive;
				i = 1;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 3);
		}

		CHECK(9 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB => CDerive (non-const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		CBaseB *base = new CDerive;
		int i = 0;

		{
			CDerivePtr derive(base, [&](CDerive *derive) {
				FuncPointerDeleted = 9;
				FuncPointerPtr = (uint64_t)derive;
				i = 1;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 3);
		}

		CHECK(9 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK(((uint64_t)base) == (FuncPointerPtr + 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseA *base = new CBaseA;
		int i = 0;

		{
			CConstBaseAPtr base2(base, [&](const CBaseA *base) {
				FuncPointerDeleted = 10;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEA(base2, CI_BASEA, 1, 1);
		}

		CHECK(10 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseB *base = new CBaseB;
		int i = 0;

		{
			CConstBaseBPtr base2(base, [&](const CBaseB *base) {
				FuncPointerDeleted = 11;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEB(base2, CI_BASEB, 1, 2);
		}

		CHECK(11 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "base: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;
		int i = 0;

		{
			CConstDerivePtr derive2(derive, [&](const CDerive *derive) {
				FuncPointerDeleted = 12;
				FuncPointerPtr = (uint64_t)derive;
				i = 1;
				delete derive;
			});
			CHECK_DERIVE(derive2, 1, 2);
		}

		CHECK(12 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseA (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;
		int i = 0;

		{
			CConstBaseAPtr base(derive, [&](const CBaseA *base) {
				FuncPointerDeleted = 10;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 1);
		}

		CHECK(10 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)derive == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CDerive => CBaseB (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CDerive *derive = new CDerive;
		int i = 0;

		{
			CConstBaseBPtr base(derive, [&](const CBaseB *base) {
				FuncPointerDeleted = 11;
				FuncPointerPtr = (uint64_t)base;
				i = 1;
				delete base;
			});
			CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 2);
		}

		CHECK(11 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK(((uint64_t)derive) == (FuncPointerPtr - 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  derive, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseA => CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseA *base = new CDerive;
		int i = 0;

		{
			CConstDerivePtr derive(base, [&](const CDerive *derive) {
				FuncPointerDeleted = 12;
				FuncPointerPtr = (uint64_t)derive;
				i = 1;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 2);
		}

		CHECK(12 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK((uint64_t)base == FuncPointerPtr,
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}

	TEST_CASE("Test lambda (no closure) for CBaseB => CDerive (const)") {
		FuncPointerDeleted = 0;
		FuncPointerPtr = 0;
		const CBaseB *base = new CDerive;
		int i = 0;

		{
			CConstDerivePtr derive(base, [&](const CDerive *derive) {
				FuncPointerDeleted = 12;
				FuncPointerPtr = (uint64_t)derive;
				i = 1;
				delete derive;
			});
			CHECK_DERIVE(derive, 1, 2);
		}

		CHECK(12 == FuncPointerDeleted, "FuncPointerDeleted: %d", FuncPointerDeleted);
		CHECK(1 == i, "i : %d", i);
		CHECK(((uint64_t)base) == (FuncPointerPtr + 8),
			  "derive: %p, FuncPointerPtr: 0x%lx",
			  base, FuncPointerPtr);
	}
}

DEFINE_TEST_GROUP(MakeShared)
{
	TEST_CASE("Test CBaseAPtr (non-const to non-const)") {
		CBaseAPtr base(MakeShared<CBaseA>());
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CBaseBPtr (non-const to non-const)") {
		CBaseBPtr base(MakeShared<CBaseB>());
		CHECK_BASEB(base, CI_BASEB, 1, 3);
	}

	TEST_CASE("Test CDerivePtr (non-const to non-const)") {
		CDerivePtr derive(MakeShared<CDerive>());
		CHECK_DERIVE(derive, 1, 3);
	}

	TEST_CASE("Test CConstBaseAPtr (const to const)") {
		CConstBaseAPtr base(MakeShared<const CBaseA>());
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CConstBaseBPtr (const to const)") {
		CConstBaseBPtr base(MakeShared<const CBaseB>());
		CHECK_BASEB(base, CI_BASEB, 1, 2);
	}

	TEST_CASE("Test CConstDerivePtr (const to const)") {
		CConstDerivePtr derive(MakeShared<const CDerive>());
		CHECK_DERIVE(derive, 1, 2);
	}

	TEST_CASE("Test CConstBaseAPtr (non-const to const)") {
		CConstBaseAPtr base(MakeShared<CBaseA>());
		CHECK_BASEA(base, CI_BASEA, 1, 1);
	}

	TEST_CASE("Test CConstBaseBPtr (non-const to const)") {
		CConstBaseBPtr base(MakeShared<CBaseB>());
		CHECK_BASEB(base, CI_BASEB, 1, 3);
	}

	TEST_CASE("Test CConstDerivePtr (non-const to const)") {
		CConstDerivePtr derive(MakeShared<CDerive>());
		CHECK_DERIVE(derive, 1, 3);
	}
}

DEFINE_TEST_GROUP(SharedPtrLrefConstructor)
{
	TEST_CASE("Test from CDerivePtr to CBaseAPtr (non-const to non-const)") {
		CDerivePtr derive;
		CBaseAPtr base(derive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CDerivePtr to CBaseBPtr (non-const to non-const)") {
		CDerivePtr derive;
		CBaseBPtr base(derive);
		CHECK_DERIVE(derive, 2, 5);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 5);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CConstDerivePtr to CConstBaseAPtr (const to const)") {
		CConstDerivePtr derive;
		CConstBaseAPtr base(derive);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CConstDerivePtr to CConstBaseBPtr (const to const)") {
		CConstDerivePtr derive;
		CConstBaseBPtr base(derive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 3);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CDerivePtr to CConstBaseAPtr (non-const to const)") {
		CDerivePtr derive;
		CConstBaseAPtr base(derive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CDerivePtr to CConstBaseBPtr (non-const to const)") {
		CDerivePtr derive;
		CConstBaseBPtr base(derive);
		CHECK_DERIVE(derive, 2, 4);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 4);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	/* (const to non-const) causes compile error */
#if 0
	CConstDerivePtr derive;
	CBaseAPtr base(derive);
#endif

	TEST_CASE("Test from CBaseAPtr(valid) to CDerivePtr (non-const to non-const)") {
		CBaseAPtr base(new CDerive());
		CDerivePtr derive(base);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CBaseBPtr(valid) to CDerivePtr (non-const to non-const)") {
		CBaseBPtr base(new CDerive());
		CDerivePtr derive(base);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 5);
		CHECK_DERIVE(derive, 2, 5);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CConstBaseAPtr(valid) to CConstDerivePtr (const to const)") {
		CConstBaseAPtr base(new CDerive());
		CConstDerivePtr derive(base);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CConstBaseBPtr(valid) to CConstDerivePtr (const to const)") {
		CConstBaseBPtr base(new CDerive());
		CConstDerivePtr derive(base);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 3);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CBaseAPtr(valid) to CConstDerivePtr (non-const to const)") {
		CBaseAPtr base(new CDerive());
		CConstDerivePtr derive(base);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 2);
		CHECK_DERIVE(derive, 2, 2);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	TEST_CASE("Test from CBaseBPtr(valid) to CConstDerivePtr (non-const to const)") {
		CBaseBPtr base(new CDerive());
		CConstDerivePtr derive(base);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 2, 4);
		CHECK_DERIVE(derive, 2, 4);
		CHECK_SAME_PTR(base.Get(), derive.Get());
	}

	/* (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base(new CDerive());
	CDerivePtr derive(base);
#endif

	TEST_CASE("Test from CBaseAPtr(invalid) to CDerivePtr") {
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

	TEST_CASE("Test from CBaseBPtr(invalid) to CDerivePtr") {
		CBaseBPtr base;
		CConstBaseBPtr cbase;
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
	TEST_CASE("Test from CDerivePtr to CBaseAPtr (non-const to non-const)") {
		CDerivePtr derive;
		CBaseAPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 3);
	}

	TEST_CASE("Test from CDerivePtr to CBaseBPtr (non-const to non-const)") {
		CDerivePtr derive;
		CBaseBPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 5);
	}

	TEST_CASE("Test from CConstDerivePtr to CConstBaseAPtr (const to const)") {
		CConstDerivePtr derive;
		CConstBaseAPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 2);
	}

	TEST_CASE("Test from CConstDerivePtr to CConstBaseBPtr (const to const)") {
		CConstDerivePtr derive;
		CConstBaseBPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 3);
	}

	TEST_CASE("Test from CDerivePtr to CConstBaseAPtr (non-const to const)") {
		CDerivePtr derive;
		CConstBaseAPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 1, 3);
	}

	TEST_CASE("Test from CDerivePtr to CConstBaseBPtr (non-const to const)") {
		CDerivePtr derive;
		CConstBaseBPtr base(std::move(derive));
		CHECK_EMPTY(derive);
		CHECK_BASEB(base, CI_BASEB_DERIVE, 1, 4);
	}

	/* (const to non-const) causes compile error */
#if 0
	CConstDerivePtr derive;
	CBaseAPtr base(derive);
#endif

	TEST_CASE("Test from CBaseAPtr(valid) to CDerivePtr (non-const to non-const)") {
		CBaseAPtr base(new CDerive());
		CDerivePtr derive(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive, 1, 3);
	}

	TEST_CASE("Test from CBaseBPtr(valid) to CDerivePtr (non-const to non-const)") {
		CBaseBPtr base(new CDerive());
		CDerivePtr derive(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive, 1, 5);
	}

	TEST_CASE("Test from CConstBaseAPtr(valid) to CConstDerivePtr (const to const)") {
		CConstBaseAPtr base(new CDerive());
		CConstDerivePtr derive(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive, 1, 2);
	}

	TEST_CASE("Test from CConstBaseBPtr(valid) to CConstDerivePtr (const to const)") {
		CConstBaseBPtr base(new CDerive());
		CConstDerivePtr derive(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive, 1, 3);
	}

	TEST_CASE("Test from CBaseAPtr(valid) to CConstDerivePtr (non-const to const)") {
		CBaseAPtr base(new CDerive());
		CConstDerivePtr derive(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive, 1, 2);
	}

	TEST_CASE("Test from CBaseBPtr(valid) to CConstDerivePtr (non-const to const)") {
		CBaseBPtr base(new CDerive());
		CConstDerivePtr derive(std::move(base));
		CHECK_EMPTY(base);
		CHECK_DERIVE(derive, 1, 4);
	}

	/* (const to non-const) causes compile error */
#if 0
	CConstBaseAPtr base(new CDerive());
	CDerivePtr derive(base);
#endif

	TEST_CASE("Test from CBaseAPtr(invalid) to CDerivePtr") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CHECK_THROW(CDerivePtr derive(std::move(base)));
		CHECK_THROW(CConstDerivePtr derive(std::move(base)));
		CHECK_THROW(CConstDerivePtr derive(std::move(cbase)));
		/* Constructor from CSharedPtr (lref) from an invalid base type
		 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(CDerivePtr derive(cbase));
#endif
	}

	TEST_CASE("Test from CBaseBPtr(invalid) to CDerivePtr") {
		CBaseBPtr base;
		CConstBaseBPtr cbase;
		CHECK_THROW(CDerivePtr derive(std::move(base)));
		CHECK_THROW(CConstDerivePtr derive(std::move(base)));
		CHECK_THROW(CConstDerivePtr derive(std::move(cbase)));
		/* Constructor from CSharedPtr (lref) from an invalid base type
		 * (const to non-const) causes compile error */
#if 0
		CHECK_THROW(CDerivePtr derive(cbase));
#endif
	}
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
				"derive->Get(): %d", derive->Get());
	}

	TEST_CASE("Should work for lref, rref, lref") {
		CTypeDeriveConstructorPtr i(1);
		CTypeDeriveConstructorPtr j(2);
		CTypeDeriveConstructorPtr k(3);

		CDerivePtr derive(i, std::move(j), k);
		CHECK_DERIVE(derive, 1, 3);
		CHECK(200 + 1 + 2 + 3 == derive->Get(),
				"derive->Get(): %d", derive->Get());
	}

	TEST_CASE("Should work for lref, rref, rref") {
		CTypeDeriveConstructorPtr i(1);
		CTypeDeriveConstructorPtr j(2);
		CTypeDeriveConstructorPtr k(3);

		CDerivePtr derive(i, std::move(j), std::move(k));
		CHECK_DERIVE(derive, 1, 3);
		CHECK(200 + 1 + 2 + 3 == derive->Get(),
				"derive->Get(): %d", derive->Get());
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
	RUN_TEST_GROUP(CustomerDeleter);
	RUN_TEST_GROUP(MakeShared);
	RUN_TEST_GROUP(SharedPtrLrefConstructor);
	RUN_TEST_GROUP(SharedPtrRrefConstructor);
	RUN_TEST_GROUP(SharedPtrMixConstructor);

	STOP_TEST();
}

