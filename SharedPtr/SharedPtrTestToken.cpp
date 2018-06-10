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

DEFINE_TEST_GROUP(Token)
{
	TEST_CASE("Test CBaseAPtr copy from token (non-const)") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		void *token = base.ToToken();
		CHECK_BASEA(base, CI_BASEA, 2, 1);

		CBaseAPtr base1((CBaseAToken *)token);
		CHECK_BASEA(base, CI_BASEA, 3, 1);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_SAME_PTR(base.Get(), base1.Get());

		CBaseAPtr base2((CBaseAToken *)token);
		CHECK_BASEA(base, CI_BASEA, 4, 1);
		CHECK_BASEA(base1, CI_BASEA, 4, 1);
		CHECK_BASEA(base2, CI_BASEA, 4, 1);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		((CBaseAToken *)token)->Release();
		token = nullptr;

		CHECK_BASEA(base, CI_BASEA, 3, 1);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_BASEA(base2, CI_BASEA, 3, 1);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CBaseBPtr copy from token (non-const)") {
		CBaseBPtr base;
		CHECK_BASEB(base, CI_BASEB, 1, 3);

		void *token = base.ToToken();
		CHECK_BASEB(base, CI_BASEB, 2, 3);

		CBaseBPtr base1((CBaseBToken *)token);
		CHECK_BASEB(base, CI_BASEB, 3, 3);
		CHECK_BASEB(base1, CI_BASEB, 3, 3);
		CHECK_SAME_PTR(base.Get(), base1.Get());

		CBaseBPtr base2((CBaseBToken *)token);
		CHECK_BASEB(base, CI_BASEB, 4, 3);
		CHECK_BASEB(base1, CI_BASEB, 4, 3);
		CHECK_BASEB(base2, CI_BASEB, 4, 3);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		((CBaseBToken *)token)->Release();
		token = nullptr;

		CHECK_BASEB(base, CI_BASEB, 3, 3);
		CHECK_BASEB(base1, CI_BASEB, 3, 3);
		CHECK_BASEB(base2, CI_BASEB, 3, 3);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CDerivePtr copy from token (non-const)") {
		CDerivePtr derive;
		CHECK_DERIVE(derive, 1, 3);

		void *token = derive.ToToken();
		CHECK_DERIVE(derive, 2, 3);

		CDerivePtr derive1((CDeriveToken *)token);
		CHECK_DERIVE(derive, 3, 3);
		CHECK_DERIVE(derive1, 3, 3);
		CHECK_SAME_PTR(derive.Get(), derive1.Get());

		CDerivePtr derive2((CDeriveToken *)token);
		CHECK_DERIVE(derive, 4, 3);
		CHECK_DERIVE(derive1, 4, 3);
		CHECK_DERIVE(derive2, 4, 3);
		CHECK_SAME_PTR(derive.Get(), derive1.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		((CDeriveToken *)token)->Release();
		token = nullptr;

		CHECK_DERIVE(derive, 3, 3);
		CHECK_DERIVE(derive1, 3, 3);
		CHECK_DERIVE(derive2, 3, 3);
		CHECK_SAME_PTR(derive.Get(), derive1.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
	}

	TEST_CASE("Test CConstBaseAPtr copy from token (const)") {
		CConstBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		void *token = base.ToToken();
		CHECK_BASEA(base, CI_BASEA, 2, 1);

		CConstBaseAPtr base1((CConstBaseAToken *)token);
		CHECK_BASEA(base, CI_BASEA, 3, 1);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_SAME_PTR(base.Get(), base1.Get());

		CConstBaseAPtr base2((CConstBaseAToken *)token);
		CHECK_BASEA(base, CI_BASEA, 4, 1);
		CHECK_BASEA(base1, CI_BASEA, 4, 1);
		CHECK_BASEA(base2, CI_BASEA, 4, 1);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		((CConstBaseAToken *)token)->Release();
		token = nullptr;

		CHECK_BASEA(base, CI_BASEA, 3, 1);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_BASEA(base2, CI_BASEA, 3, 1);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CConstBaseBPtr copy from token (const)") {
		CConstBaseBPtr base;
		CHECK_BASEB(base, CI_BASEB, 1, 2);

		void *token = base.ToToken();
		CHECK_BASEB(base, CI_BASEB, 2, 2);

		CConstBaseBPtr base1((CConstBaseBToken *)token);
		CHECK_BASEB(base, CI_BASEB, 3, 2);
		CHECK_BASEB(base1, CI_BASEB, 3, 2);
		CHECK_SAME_PTR(base.Get(), base1.Get());

		CConstBaseBPtr base2((CConstBaseBToken *)token);
		CHECK_BASEB(base, CI_BASEB, 4, 2);
		CHECK_BASEB(base1, CI_BASEB, 4, 2);
		CHECK_BASEB(base2, CI_BASEB, 4, 2);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());

		((CConstBaseBToken *)token)->Release();
		token = nullptr;

		CHECK_BASEB(base, CI_BASEB, 3, 2);
		CHECK_BASEB(base1, CI_BASEB, 3, 2);
		CHECK_BASEB(base2, CI_BASEB, 3, 2);
		CHECK_SAME_PTR(base.Get(), base1.Get());
		CHECK_SAME_PTR(base1.Get(), base2.Get());
	}

	TEST_CASE("Test CConstDerivePtr copy from token (const)") {
		CConstDerivePtr derive;
		CHECK_DERIVE(derive, 1, 2);

		void *token = derive.ToToken();
		CHECK_DERIVE(derive, 2, 2);

		CConstDerivePtr derive1((CConstDeriveToken *)token);
		CHECK_DERIVE(derive, 3, 2);
		CHECK_DERIVE(derive1, 3, 2);
		CHECK_SAME_PTR(derive.Get(), derive1.Get());

		CConstDerivePtr derive2((CConstDeriveToken *)token);
		CHECK_DERIVE(derive, 4, 2);
		CHECK_DERIVE(derive1, 4, 2);
		CHECK_DERIVE(derive2, 4, 2);
		CHECK_SAME_PTR(derive.Get(), derive1.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());

		((CConstDeriveToken *)token)->Release();
		token = nullptr;

		CHECK_DERIVE(derive, 3, 2);
		CHECK_DERIVE(derive1, 3, 2);
		CHECK_DERIVE(derive2, 3, 2);
		CHECK_SAME_PTR(derive.Get(), derive1.Get());
		CHECK_SAME_PTR(derive1.Get(), derive2.Get());
	}
}

void Token(void)
{
	START_TEST();

	RUN_TEST_GROUP(Token);

	STOP_TEST();
}

