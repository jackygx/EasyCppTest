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
static void token(void)
{
	TEST_STEP(30, 1, "Token",
			  "Should work") {
		CParentPtr p;
		CHECK_ID(p, CI_PARENT);

		{
			auto token = p.ToToken();
			CHECK(2 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p1(token, true);
			CHECK(3 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p2(token, true);
			CHECK(4 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p3(token, true);
			CHECK(5 == p.GetRef(), "ref: %d", p.GetRef());

			token->Release();
		}

		CHECK(1 == p.GetRef(), "ref: %d", p.GetRef());

		{
			auto token = p.ToToken();
			CHECK(2 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p1(token, true);
			CHECK(3 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p2(token, true);
			CHECK(4 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p3(token, true);
			CHECK(5 == p.GetRef(), "ref: %d", p.GetRef());

			CParentPtr p4(token);
			CHECK(5 == p.GetRef(), "ref: %d", p.GetRef());
		}

		CHECK(1 == p.GetRef(), "ref: %d", p.GetRef());
	}
}

static void operator_others(void)
{
	TEST_STEP(82, 1, "operator []",
			  "CSharedPtr<this> == null") {
		CConstParentPtr p(nullptr);
		CHECK_THROW(p[10]);
	}

	TEST_STEP(82, 2, "operator []",
			  "CSharedPtr<this> != null, non-const") {
		CParentPtr p(1);
		CHECK(11 == p[10], "p[10] = %d", p[10]);
	}

	TEST_STEP(82, 3, "operator []",
			  "CSharedPtr<this> != null, const") {
		CConstParentPtr p(1);
		CHECK(10 == p[10], "p[10] = %d", p[10]);
	}

	TEST_STEP(83, 1, "operator void(...)",
			  "CSharedPtr<this> == null") {
		CParentPtr p(nullptr);
		CHECK_THROW(p("test"));
	}

	TEST_STEP(83, 2, "operator void(...)",
			  "CSharedPtr<this> != null, non-const") {
		CParentPtr p(1);
		p("test");
		CHECK(5 == p->GetNum(), "num: %d", p->GetNum());
	}

	TEST_STEP(83, 3, "operator void(...)",
			  "CSharedPtr<this> != null, const") {
		CConstParentPtr p(1);
		p("test");
		CHECK(1 == p->GetNum(), "num: %d", p->GetNum());
	}

	TEST_STEP(84, 1, "operator non-void(...)",
			  "CSharedPtr<this> == null") {
		CParentPtr p(nullptr);
		CHECK_THROW(p(10));
	}

	TEST_STEP(84, 2, "operator non-void(...)",
			  "CSharedPtr<this> != null, non-const") {
		CParentPtr p(1);
		CHECK(11 == p(10), "p(10) = %d", p(10));
	}

	TEST_STEP(84, 3, "operator non-void(...)",
			  "CSharedPtr<this> != null, const") {
		CConstParentPtr p(1);
		CHECK(10 == p(10), "p(10) = %d", p(10));
	}

	TEST_STEP(85, 1, "operator ->",
			  "CSharedPtr<this> == null") {
		CParentPtr p(nullptr);
		CHECK_THROW(p->GetNum());
	}

	TEST_STEP(85, 2, "operator ->",
			  "CSharedPtr<this> != null, non-const") {
		CParentPtr p(1);
		p->SetNum(10);
		CHECK(10 == p->GetNum(), "num: %d", p->GetNum());
	}

	TEST_STEP(85, 3, "operator ->",
			  "CSharedPtr<this> != null, const") {
		CConstParentPtr p(1);
		CHECK(1 == p->GetNum(), "num: %d", p->GetNum());
	}

	TEST_STEP(86, 1, "operator *",
			  "CSharedPtr<this> == null") {
		CParentPtr p(nullptr);
		CHECK_THROW(*p);
	}

	TEST_STEP(86, 2, "operator *",
			  "CSharedPtr<this> != null") {
		CParentPtr p(1);
		CHECK(1 == (*p).GetNum(), "num: %d", (*p).GetNum());
	}
}

static void others(void)
{
	TEST_STEP(90, 1, "Release this shared pointer",
			  "CSharedPtr<this> == null") {
		CParentPtr p(nullptr);
		CHECK(0 == p.GetRef(), "ref: %d", p.GetRef());
		p.Release();
		CHECK(0 == p.GetRef(), "ref: %d", p.GetRef());
	}

	TEST_STEP(90, 2, "Release this shared pointer",
			  "CSharedPtr<this> != null") {
		CParentPtr p;
		CHECK(1 == p.GetRef(), "ref: %d", p.GetRef());
		p.Release();
		CHECK(0 == p.GetRef(), "ref: %d", p.GetRef());
	}
}

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
#if 0
	DO_TEST(token);
	DO_TEST(operator_others);
	DO_TEST(others);
	DO_TEST(reference);
#endif
}

