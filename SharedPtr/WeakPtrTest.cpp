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

#include "WeakPtrTest.hpp"

DEFINE_TEST_GROUP(WeakPtrForNullptr)
{
	TEST_CASE("Lock works for empty pointer") {
		CBaseAWeakPtr base;
		CConstBaseAWeakPtr cbase;
		CHECK(!base.Lock(), "Base lock: ", HEX(base.Lock().Get()));
		CHECK(!cbase.Lock(), "CBase lock: ", HEX(cbase.Lock().Get()));
	}

	TEST_CASE("GetRef works for empty pointer") {
		CBaseAWeakPtr base;
		CConstBaseAWeakPtr cbase;
		CHECK(0 == base.GetRef(), "GetRef: ", DEC(base.GetRef()));
		CHECK(0 == cbase.GetRef(), "GetRef: ", DEC(cbase.GetRef()));
	}

	TEST_CASE("GetWeakRef works for empty pointer") {
		CBaseAWeakPtr base;
		CConstBaseAWeakPtr cbase;
		CHECK(0 == base.GetWeakRef(), "GetRef: ", DEC(base.GetRef()));
		CHECK(0 == cbase.GetWeakRef(), "GetRef: ", DEC(cbase.GetRef()));
	}
	TEST_CASE("Release works for empty pointer") {
		CBaseAWeakPtr base;
		CConstBaseAWeakPtr cbase;
		CHECK_WEAK_EMPTY(base);
		CHECK_WEAK_EMPTY(cbase);

		base.Release();
		cbase.Release();
		CHECK_WEAK_EMPTY(base);
		CHECK_WEAK_EMPTY(cbase);
	}
}

DEFINE_TEST_GROUP(WeakPtrConstructor)
{
	TEST_CASE("Construct from same type") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);

		/* non-const => non-const */
		CBaseAWeakPtr wbase1(base);
		CHECK_BASEA(base, CI_BASEA, 1, 2);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);
		CHECK_WEAK(wbase1, 1, 2);

		/* non-const => const */
		CConstBaseAWeakPtr cwbase1(base);
		CHECK_BASEA(base, CI_BASEA, 1, 3);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);
		CHECK_WEAK(wbase1, 1, 3);
		CHECK_WEAK(cwbase1, 1, 3);

		/* const => const */
		CConstBaseAWeakPtr cwbase2(cbase);
		CHECK_BASEA(base, CI_BASEA, 1, 3);
		CHECK_BASEA(cbase, CI_BASEA, 1, 2);
		CHECK_WEAK(wbase1, 1, 3);
		CHECK_WEAK(cwbase1, 1, 3);
		CHECK_WEAK(cwbase2, 1, 2);

		/* const => non-const will cause compile error */
#if 0
		CBaseAWeakPtr wbase2(cbase);
#endif
	}

	TEST_CASE("Construct from derive") {
		CDerivePtr derive;
		CConstDerivePtr cderive;
		CHECK_DERIVE(derive, 1, 3);
		CHECK_DERIVE(cderive, 1, 2);

		/* non-const => non-const */
		CBaseAWeakPtr wbase1(derive);
		CHECK_DERIVE(derive, 1, 4);
		CHECK_DERIVE(cderive, 1, 2);
		CHECK_WEAK(wbase1, 1, 4);

		/* non-const => const */
		CConstBaseAWeakPtr cwbase1(derive);
		CHECK_DERIVE(derive, 1, 5);
		CHECK_DERIVE(cderive, 1, 2);
		CHECK_WEAK(wbase1, 1, 5);
		CHECK_WEAK(cwbase1, 1, 5);

		/* const => const */
		CConstBaseAWeakPtr cwbase2(cderive);
		CHECK_DERIVE(derive, 1, 5);
		CHECK_DERIVE(cderive, 1, 3);
		CHECK_WEAK(wbase1, 1, 5);
		CHECK_WEAK(cwbase1, 1, 5);
		CHECK_WEAK(cwbase2, 1, 3);

		/* const => non-const will cause compile error */
#if 0
		CBaseAWeakPtr wbase2(cderive);
#endif
	}

	TEST_CASE("Construct from valid base") {
		CDerivePtr derive;
		CConstDerivePtr cderive;
		CBaseAPtr base(derive);
		CConstBaseAPtr cbase(cderive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_DERIVE(cderive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 2);

		/* non-const => non-const */
		CDeriveWeakPtr wderive1(base);
		CHECK_DERIVE(derive, 2, 4);
		CHECK_DERIVE(cderive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 4);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 2);
		CHECK_WEAK(wderive1, 2, 4);

		/* non-const => const */
		CConstDeriveWeakPtr cwderive1(base);
		CHECK_DERIVE(derive, 2, 5);
		CHECK_DERIVE(cderive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 5);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 2);
		CHECK_WEAK(wderive1, 2, 5);
		CHECK_WEAK(cwderive1, 2, 5);

		/* const => const */
		CConstDeriveWeakPtr cwderive2(cbase);
		CHECK_DERIVE(derive, 2, 5);
		CHECK_DERIVE(cderive, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 5);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 3);
		CHECK_WEAK(wderive1, 2, 5);
		CHECK_WEAK(cwderive1, 2, 5);
		CHECK_WEAK(cwderive2, 2, 3);

		/* const => non-const will cause compile error */
#if 0
		CDeriveWeakPtr wbase2(cbase);
#endif
	}

	TEST_CASE("Construct from invalid base") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);

		/* non-const => non-const */
		CHECK_THROW(CDeriveWeakPtr wderive1(base));

		/* non-const => const */
		CHECK_THROW(CConstDeriveWeakPtr cwderive1(base));

		/* const => const */
		CHECK_THROW(CConstDeriveWeakPtr cwderive2(cbase));

		/* const => non-const will cause compile error */
#if 0
		CDeriveWeakPtr wderive2(cbase);
#endif
	}
}

DEFINE_TEST_GROUP(WeakPtrOperatorEqual)
{
	TEST_CASE("Operator equal from same type") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);

		/* non-const => non-const */
		CBaseAWeakPtr wbase1;
		CHECK_WEAK_EMPTY(wbase1);
		wbase1 = base;
		CHECK_BASEA(base, CI_BASEA, 1, 2);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);
		CHECK_WEAK(wbase1, 1, 2);

		/* non-const => const */
		CConstBaseAWeakPtr cwbase1;
		CHECK_WEAK_EMPTY(cwbase1);
		cwbase1 = base;
		CHECK_BASEA(base, CI_BASEA, 1, 3);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);
		CHECK_WEAK(wbase1, 1, 3);
		CHECK_WEAK(cwbase1, 1, 3);

		/* const => const */
		CConstBaseAWeakPtr cwbase2;
		CHECK_WEAK_EMPTY(cwbase2);
		cwbase2 = cbase;
		CHECK_BASEA(base, CI_BASEA, 1, 3);
		CHECK_BASEA(cbase, CI_BASEA, 1, 2);
		CHECK_WEAK(wbase1, 1, 3);
		CHECK_WEAK(cwbase1, 1, 3);
		CHECK_WEAK(cwbase2, 1, 2);

		/* const => non-const will cause compile error */
#if 0
		CBaseAWeakPtr wbase2;
		wbase2 = cbase;
#endif
	}

	TEST_CASE("Construct from derive") {
		CDerivePtr derive;
		CConstDerivePtr cderive;
		CHECK_DERIVE(derive, 1, 3);
		CHECK_DERIVE(cderive, 1, 2);

		/* non-const => non-const */
		CBaseAWeakPtr wbase1;
		CHECK_WEAK_EMPTY(wbase1);
		wbase1 = derive;
		CHECK_DERIVE(derive, 1, 4);
		CHECK_DERIVE(cderive, 1, 2);
		CHECK_WEAK(wbase1, 1, 4);

		/* non-const => const */
		CConstBaseAWeakPtr cwbase1;
		CHECK_WEAK_EMPTY(cwbase1);
		cwbase1 = derive;
		CHECK_DERIVE(derive, 1, 5);
		CHECK_DERIVE(cderive, 1, 2);
		CHECK_WEAK(wbase1, 1, 5);
		CHECK_WEAK(cwbase1, 1, 5);

		/* const => const */
		CConstBaseAWeakPtr cwbase2;
		CHECK_WEAK_EMPTY(cwbase2);
		cwbase2 = cderive;
		CHECK_DERIVE(derive, 1, 5);
		CHECK_DERIVE(cderive, 1, 3);
		CHECK_WEAK(wbase1, 1, 5);
		CHECK_WEAK(cwbase1, 1, 5);
		CHECK_WEAK(cwbase2, 1, 3);

		/* const => non-const will cause compile error */
#if 0
		CBaseAWeakPtr wbase1;
		wbase1 = cderive;
#endif
	}

	TEST_CASE("Construct from valid base") {
		CDerivePtr derive;
		CConstDerivePtr cderive;
		CBaseAPtr base(derive);
		CConstBaseAPtr cbase(cderive);
		CHECK_DERIVE(derive, 2, 3);
		CHECK_DERIVE(cderive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 3);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 2);

		/* non-const => non-const */
		CDeriveWeakPtr wderive1;
		CHECK_WEAK_EMPTY(wderive1);
		wderive1 = base;
		CHECK_DERIVE(derive, 2, 4);
		CHECK_DERIVE(cderive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 4);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 2);
		CHECK_WEAK(wderive1, 2, 4);

		/* non-const => const */
		CConstDeriveWeakPtr cwderive1;
		CHECK_WEAK_EMPTY(cwderive1);
		cwderive1 = base;
		CHECK_DERIVE(derive, 2, 5);
		CHECK_DERIVE(cderive, 2, 2);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 5);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 2);
		CHECK_WEAK(wderive1, 2, 5);
		CHECK_WEAK(cwderive1, 2, 5);

		/* const => const */
		CConstDeriveWeakPtr cwderive2;
		CHECK_WEAK_EMPTY(cwderive2);
		cwderive2 = cbase;
		CHECK_DERIVE(derive, 2, 5);
		CHECK_DERIVE(cderive, 2, 3);
		CHECK_BASEA(base, CI_BASEA_DERIVE, 2, 5);
		CHECK_BASEA(cbase, CI_BASEA_DERIVE, 2, 3);
		CHECK_WEAK(wderive1, 2, 5);
		CHECK_WEAK(cwderive1, 2, 5);
		CHECK_WEAK(cwderive2, 2, 3);

		/* const => non-const will cause compile error */
#if 0
		CDeriveWeakPtr wderive1;
		wderive1 = cbase;
#endif
	}

	TEST_CASE("Construct from invalid base") {
		CBaseAPtr base;
		CConstBaseAPtr cbase;
		CHECK_BASEA(base, CI_BASEA, 1, 1);
		CHECK_BASEA(cbase, CI_BASEA, 1, 1);

		CDeriveWeakPtr wderive;
		CConstDeriveWeakPtr cwderive;
		CHECK_WEAK_EMPTY(wderive);
		CHECK_WEAK_EMPTY(cwderive);

		/* non-const => non-const */
		CHECK_THROW(wderive = base);

		/* non-const => const */
		CHECK_THROW(cwderive = base);

		/* const => const */
		CHECK_THROW(cwderive = cbase);

		/* const => non-const will cause compile error */
#if 0
		wderive = cbase;
#endif
	}
}

DEFINE_TEST_GROUP(WeakPtrLock)
{
	TEST_CASE("Should work for non-empty SharedPtr. (non-const)") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		CBaseAWeakPtr wbase(base);
		CHECK_BASEA(base, CI_BASEA, 1, 2);
		CHECK_WEAK(wbase, 1, 2);

		CBaseAPtr base1(wbase.Lock());
		CHECK_BASEA(base, CI_BASEA, 2, 2);
		CHECK_BASEA(base1, CI_BASEA, 2, 2);
		CHECK_WEAK(wbase, 2, 2);
	}

	TEST_CASE("Should work for non-empty SharedPtr. (const)") {
		CConstBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		CConstBaseAWeakPtr wbase(base);
		CHECK_BASEA(base, CI_BASEA, 1, 2);
		CHECK_WEAK(wbase, 1, 2);

		CConstBaseAPtr base1(wbase.Lock());
		CHECK_BASEA(base, CI_BASEA, 2, 2);
		CHECK_BASEA(base1, CI_BASEA, 2, 2);
		CHECK_WEAK(wbase, 2, 2);
	}

	TEST_CASE("Should return nullptr for empty SharedPtr. (non-const)") {
		CBaseAWeakPtr wbase;
		CHECK_WEAK_EMPTY(wbase);

		{
			CBaseAPtr base;
			CHECK_BASEA(base, CI_BASEA, 1, 1);

			wbase = base;
			CHECK_BASEA(base, CI_BASEA, 1, 2);
			CHECK_WEAK(wbase, 1, 2);
		}

		CHECK(0 == wbase.GetRef(),
			  "Ref: ",
			  DEC(wbase.GetRef()));
		CHECK(1 == wbase.GetWeakRef(),
			  "WeakRef: ",
			  DEC(wbase.GetWeakRef()));

		CBaseAPtr base(wbase.Lock());
		CHECK_EMPTY(base);
	}

	TEST_CASE("Should return nullptr for empty SharedPtr. (const)") {
		CConstBaseAWeakPtr wbase;
		CHECK_WEAK_EMPTY(wbase);

		{
			CConstBaseAPtr base;
			CHECK_BASEA(base, CI_BASEA, 1, 1);

			wbase = base;
			CHECK_BASEA(base, CI_BASEA, 1, 2);
			CHECK_WEAK(wbase, 1, 2);
		}

		CHECK(0 == wbase.GetRef(),
			  "Ref: ",
			  DEC(wbase.GetRef()));
		CHECK(1 == wbase.GetWeakRef(),
			  "WeakRef: ",
			  DEC(wbase.GetWeakRef()));

		CConstBaseAPtr base(wbase.Lock());
		CHECK_EMPTY(base);
	}
}

DEFINE_TEST_GROUP(WeakPtrRelease)
{
	TEST_CASE("Should work (non-const)") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		CBaseAWeakPtr wbase(base);
		CHECK_BASEA(base, CI_BASEA, 1, 2);
		CHECK_WEAK(wbase, 1, 2);

		wbase.Release();
		CHECK_BASEA(base, CI_BASEA, 1, 1);
		CHECK_WEAK_EMPTY(wbase);
	}

	TEST_CASE("Should work (const)") {
		CConstBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		CConstBaseAWeakPtr wbase(base);
		CHECK_BASEA(base, CI_BASEA, 1, 2);
		CHECK_WEAK(wbase, 1, 2);

		wbase.Release();
		CHECK_BASEA(base, CI_BASEA, 1, 1);
		CHECK_WEAK_EMPTY(wbase);
	}
}

void WeakPtrTest(void)
{
	START_TEST();

	RUN_TEST_GROUP(WeakPtrForNullptr);
	RUN_TEST_GROUP(WeakPtrConstructor);
	RUN_TEST_GROUP(WeakPtrOperatorEqual);
	RUN_TEST_GROUP(WeakPtrLock);
	RUN_TEST_GROUP(WeakPtrRelease);

	STOP_TEST();
}

