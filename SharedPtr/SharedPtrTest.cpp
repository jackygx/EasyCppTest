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

#define SHOW_TEST_STEP

#include "SharedPtrTest.hpp"

#if 0
static void reference(void)
{
	TEST_STEP(0, 0, "Reference",
			  "") {
		CParentPtr p1;
		CHECK(1 == p1.GetRef(), "ref: %d", p1.GetRef());
		CHECK(2 == p1.GetWeakRef(), "ref: %d", p1.GetWeakRef());
		CParentPtr p2(p1);
		CHECK(2 == p1.GetRef(), "ref: %d", p1.GetRef());
		CHECK(2 == p1.GetWeakRef(), "ref: %d", p2.GetWeakRef());
		CHECK(2 == p2.GetRef(), "ref: %d", p2.GetRef());
		CHECK(2 == p2.GetWeakRef(), "ref: %d", p2.GetWeakRef());
		{
			CParentPtr p3(p1);
			CHECK(3 == p1.GetRef(), "ref: %d", p1.GetRef());
			CHECK(2 == p1.GetWeakRef(), "ref: %d", p1.GetWeakRef());
			CHECK(3 == p2.GetRef(), "ref: %d", p2.GetRef());
			CHECK(2 == p2.GetWeakRef(), "ref: %d", p2.GetWeakRef());
			CHECK(3 == p3.GetRef(), "ref: %d", p3.GetRef());
			CHECK(2 == p3.GetWeakRef(), "ref: %d", p3.GetWeakRef());
		}
		CHECK(2 == p1.GetRef(), "ref: %d", p1.GetRef());
		CHECK(2 == p1.GetWeakRef(), "ref: %d", p1.GetWeakRef());
		CHECK(2 == p2.GetRef(), "ref: %d", p2.GetRef());
		CHECK(2 == p2.GetWeakRef(), "ref: %d", p2.GetWeakRef());

		CParentWeakPtr p4(p1);
		CHECK(2 == p1.GetRef(), "ref: %d", p1.GetRef());
		CHECK(3 == p1.GetWeakRef(), "ref: %d", p1.GetWeakRef());
		CHECK(2 == p2.GetRef(), "ref: %d", p2.GetRef());
		CHECK(3 == p2.GetWeakRef(), "ref: %d", p2.GetWeakRef());
		CHECK(2 == p4.GetRef(), "ref: %d", p4.GetRef());
		CHECK(3 == p4.GetWeakRef(), "ref: %d", p4.GetWeakRef());

		p1.Release();
		CHECK(0 == p1.GetRef(), "ref: %d", p1.GetRef());
		CHECK(0 == p1.GetWeakRef(), "ref: %d", p1.GetWeakRef());
		CHECK(1 == p2.GetRef(), "ref: %d", p2.GetRef());
		CHECK(3 == p2.GetWeakRef(), "ref: %d", p2.GetWeakRef());
		CHECK(1 == p4.GetRef(), "ref: %d", p4.GetRef());
		CHECK(3 == p4.GetWeakRef(), "ref: %d", p4.GetWeakRef());

		p2.Release();
		CHECK(0 == p1.GetRef(), "ref: %d", p1.GetRef());
		CHECK(0 == p1.GetWeakRef(), "ref: %d", p1.GetWeakRef());
		CHECK(0 == p2.GetRef(), "ref: %d", p2.GetRef());
		CHECK(0 == p2.GetWeakRef(), "ref: %d", p2.GetWeakRef());
		CHECK(0 == p4.GetRef(), "ref: %d", p4.GetRef());
		CHECK(1 == p4.GetWeakRef(), "ref: %d", p4.GetWeakRef());
	}

	TEST_STEP(1, 2, "Construct for class",
			  "Should call class's default constructor for class") {
		CParentPtr p1;
		CHECK_ID(p1, CI_PARENT);
		CHECK(0 == p1->GetNum(), "Num: ", DEC(p1->GetNum()));
		CHECK(1 == p1.GetRef(), "Ref: ", DEC(p1.GetRef()));
		CHECK(2 == p1.GetWeakRef(), "WeakRef: ", DEC(p1.GetWeakRef()));

		CParentPtr p2(nullptr);
		CHECK(0 == p2.GetRef(), "Ref: %d", p2.GetRef());
		CHECK(0 == p2.GetWeakRef(), "WeakRef: %d", p2.GetWeakRef());

		CChildPtr c1;
		CHECK(1 == c1.GetRef(), "Ref: %d", c1.GetRef());
		CHECK(2 == c1.GetWeakRef(), "WeakRef: %d", c1.GetWeakRef());

		{
			CParentPtr p3(p1->Share());
			CHECK(2 == p3.GetRef(), "Ref: %d", p3.GetRef());
			CHECK(2 == p3.GetWeakRef(), "WeakRef: %d", p3.GetWeakRef());
			CHECK(2 == p1.GetRef(), "Ref: %d", p1.GetRef());
			CHECK(2 == p1.GetWeakRef(), "WeakRef: %d", p1.GetWeakRef());

			p2 = CParentPtr();
			CParentPtr p4(p2);
			CHECK(2 == p2.GetRef(), "Ref: %d", p2.GetRef());
			CHECK(2 == p2.GetWeakRef(), "WeakRef: %d", p2.GetWeakRef());
			CHECK(2 == p4.GetRef(), "Ref: %d", p4.GetRef());
			CHECK(2 == p4.GetWeakRef(), "WeakRef: %d", p4.GetWeakRef());
			p2.Release();
			CHECK(0 == p2.GetRef(), "Ref: %d", p2.GetRef());
			CHECK(0 == p2.GetWeakRef(), "WeakRef: %d", p2.GetWeakRef());
			CHECK(1 == p4.GetRef(), "Ref: %d", p4.GetRef());
			CHECK(2 == p4.GetWeakRef(), "WeakRef: %d", p4.GetWeakRef());
		}
		CHECK(1 == p1.GetRef(), "Ref: %d", p1.GetRef());
		/* CParent inherit CSharedPtr<CParent> */
		CHECK(2 == p1.GetWeakRef(), "WeakRef: %d", p1.GetWeakRef());

		CHECK(0 == p2.GetRef(), "Ref: %d", p2.GetRef());
		CHECK(0 == p2.GetWeakRef(), "WeakRef: %d", p2.GetWeakRef());
	}
}
#endif

TEST_CASE_ENTRY()
{
	RUN_TEST(Constructor);
	RUN_TEST(Equal);
	RUN_TEST(IsEqual);
	RUN_TEST(AddEqual);
	RUN_TEST(SubEqual);
	RUN_TEST(Compare);
	RUN_TEST(Token);
	RUN_TEST(OtherOperators);
	RUN_TEST(Others);
#if 0
	DO_TEST(reference);
#endif
}

