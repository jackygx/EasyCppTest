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
	TEST_CASE("Create from nullptr token will throw error") {
		CHECK_THROW(CBaseAPtr base((CBaseAToken *)nullptr));
	}

	TEST_CASE("Copy create from token") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		auto token = base.ToToken();
		CHECK_BASEA(base, CI_BASEA, 2, 1);

		CBaseAPtr base1(token, TokenOps::COPY);
		CHECK_BASEA(base, CI_BASEA, 3, 1);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_SAME_PTR(base, base1);

		CBaseAPtr base2(token, TokenOps::COPY);
		CHECK_BASEA(base, CI_BASEA, 4, 1);
		CHECK_BASEA(base1, CI_BASEA, 4, 1);
		CHECK_BASEA(base2, CI_BASEA, 4, 1);
		CHECK_SAME_PTR(base, base1);
		CHECK_SAME_PTR(base1, base2);

		token->Release();
		token = nullptr;

		CHECK_BASEA(base, CI_BASEA, 3, 1);
		CHECK_BASEA(base1, CI_BASEA, 3, 1);
		CHECK_BASEA(base2, CI_BASEA, 3, 1);
		CHECK_SAME_PTR(base, base1);
		CHECK_SAME_PTR(base1, base2);
	}

	TEST_CASE("Move create from token") {
		CBaseAPtr base;
		CHECK_BASEA(base, CI_BASEA, 1, 1);

		auto token = base.ToToken();
		CHECK_BASEA(base, CI_BASEA, 2, 1);

		CBaseAPtr base1(token, TokenOps::MOVE);
		CHECK_BASEA(base, CI_BASEA, 2, 1);
		CHECK_BASEA(base1, CI_BASEA, 2, 1);
		CHECK_SAME_PTR(base, base1);

		CHECK_THROW(CBaseAPtr base2(token, TokenOps::COPY));
		CHECK_THROW(CBaseAPtr base3(token, TokenOps::MOVE));

		token->Release();
		token = nullptr;
	}
}

void Token(void)
{
	START_TEST();

	RUN_TEST_GROUP(Token);

	STOP_TEST();
}

