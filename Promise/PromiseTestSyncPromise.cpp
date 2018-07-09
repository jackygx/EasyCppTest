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

#include "PromiseTest.hpp"
#include "PromiseTestSyncPromise.hpp"

DEFINE_TEST_GROUP(BuildInType)
{
	TEST_CASE("Test Sync promise with built-in type (succeed).") {
		int idx = 0;
		auto promise = GetBuildInSucceedPromise(10, 20.0f, "test1");

		promise->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

			return 20.0f;
		})->Catch([&](int) {
			return nullptr;
		});

//		CHECK_VAL(idx, 3);
//		CHECK_VAL(ret, 100);
	}

#if 0
	TEST_CASE("Test Sync promise with built-in type (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return GetBuildInPromise(30, 40.0f, "test2");
		})->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 30);
			CHECK_FLOAT(j, 40.0f);
			CHECK_STRING(k, "test2");
			CHECK_INT(idx, 1);
			idx = 2;

			return GetBuildInPromise();
		})->Then([&](int, float, const char *) {
			CHECK(false, "Should not catch");

			return GetBuildInPromise(50, 60.0f, "test3");
		})->Then([&](int, float, const char *) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 2);
			idx = 3;

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, -100);
	}
#endif
}

#if 0
DEFINE_TEST_GROUP(StructureType)
{
	TEST_CASE("Test Sync promise with struct type (succeed).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return GetStructPromise(true);
		})->Then([&](const SyncPromiseStruct1 &promise1,
					 const SyncPromiseStruct2 &promise2) {
			CHECK_INT(promise1.i, 10);
			CHECK_FLOAT(promise1.j, 20.0f);
			CHECK_STRING(promise1.k, "test1");

			CHECK_STRING(promise2.i, "test2");
			CHECK_FLOAT(promise2.j, 40.0f);
			CHECK_INT(promise2.k, 30);

			CHECK_INT(idx, 1);
			idx = 2;

			return GetStructPromise(true);
		})->Then([&](const SyncPromiseStruct1 &promise1,
					 const SyncPromiseStruct2 &promise2) {
			CHECK_INT(promise1.i, 10);
			CHECK_FLOAT(promise1.j, 20.0f);
			CHECK_STRING(promise1.k, "test1");

			CHECK_STRING(promise2.i, "test2");
			CHECK_FLOAT(promise2.j, 40.0f);
			CHECK_INT(promise2.k, 30);

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with struct type (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return GetStructPromise(false);
		})->Then([&](const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &) {
			CHECK(false, "Should not catch");

			return GetStructPromise(true);
		})->Then([&](const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 1);
			idx = 2;

			return -100;
		});

		CHECK_INT(idx, 2);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(SharedPtrType)
{
	TEST_CASE("Test Sync promise with CSharedPtr (succeed).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return GetSharedPtrPromise(true);
		})->Then([&](const CSyncPromise1Ptr &promise1,
					 const CSyncPromise2Ptr &promise2) {
			CHECK_INT(promise1->GetI(), 10);
			CHECK_FLOAT(promise1->GetJ(), 20.0f);
			CHECK_STRING(promise1->GetK(), "test1");

			CHECK_STRING(promise2->GetI(), "test2");
			CHECK_FLOAT(promise2->GetJ(), 30.0f);
			CHECK_INT(promise2->GetK(), 40);

			CHECK_INT(idx, 1);
			idx = 2;

			return GetSharedPtrPromise(true);
		})->Then([&](const CSyncPromise1Ptr &promise1,
					 const CSyncPromise2Ptr &promise2) {
			CHECK_INT(promise1->GetI(), 10);
			CHECK_FLOAT(promise1->GetJ(), 20.0f);
			CHECK_STRING(promise1->GetK(), "test1");

			CHECK_STRING(promise2->GetI(), "test2");
			CHECK_FLOAT(promise2->GetJ(), 30.0f);
			CHECK_INT(promise2->GetK(), 40);

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with CSharedPtr (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return GetSharedPtrPromise(false);
		})->Then([&](const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &) {
			CHECK(false, "Should not catch");

			return GetSharedPtrPromise(true);
		})->Then([&](const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 1);
			idx = 2;

			return -100;
		});

		CHECK_INT(idx, 2);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(AnonymousBuildInType)
{
	TEST_CASE("Test Sync promise with built-in type (succeed).") {
		int idx = 0;

		auto promise = CreateSyncPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(30, 40.0f, "test2");
		})->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 30);
			CHECK_FLOAT(j, 40.0f);
			CHECK_STRING(k, "test2");
			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(50, 60.0f, "test3");
		})->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 50);
			CHECK_FLOAT(j, 60.0f);
			CHECK_STRING(k, "test3");
			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with built-in type (failure).") {
		int idx = 0;

		auto promise = CreateSyncPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(30, 40.0f, "test2");
		})->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 30);
			CHECK_FLOAT(j, 40.0f);
			CHECK_STRING(k, "test2");
			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise<int, float, const char *>();
		})->Then([&](int, float, const char *) {
			CHECK(false, "Should not catch");

			return CreateSyncPromise(50, 60.0f, "test3");
		})->Then([&](int, float, const char *) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 2);
			idx = 3;

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(AnonymousStructureType)
{
	TEST_CASE("Test Sync promise with struct type (succeed).") {
		int idx = 0;

		auto promise = CreateSyncPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(SyncPromiseStruct1{10, 20.0f, "test1"},
									 SyncPromiseStruct2{"test2", 40.0f, 30});
		})->Then([&](const SyncPromiseStruct1 &promise1,
					 const SyncPromiseStruct2 &promise2) {
			CHECK_INT(promise1.i, 10);
			CHECK_FLOAT(promise1.j, 20.0f);
			CHECK_STRING(promise1.k, "test1");

			CHECK_STRING(promise2.i, "test2");
			CHECK_FLOAT(promise2.j, 40.0f);
			CHECK_INT(promise2.k, 30);

			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(SyncPromiseStruct1{50, 60.0f, "test3"},
									 SyncPromiseStruct2{"test4", 80.0f, 70});
		})->Then([&](const SyncPromiseStruct1 &promise1,
					 const SyncPromiseStruct2 &promise2) {
			CHECK_INT(promise1.i, 50);
			CHECK_FLOAT(promise1.j, 60.0f);
			CHECK_STRING(promise1.k, "test3");

			CHECK_STRING(promise2.i, "test4");
			CHECK_FLOAT(promise2.j, 80.0f);
			CHECK_INT(promise2.k, 70);

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with struct type (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise<SyncPromiseStruct1, SyncPromiseStruct2>();
		})->Then([&](const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &) {
			CHECK(false, "Should not catch");

			return CreateSyncPromise(SyncPromiseStruct1{50, 60.0f, "test3"},
									 SyncPromiseStruct2{"test4", 80.0f, 70});
		})->Then([&](const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 1);
			idx = 2;

			return -100;
		});

		CHECK_INT(idx, 2);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(AnonymousSharedPtrType)
{
	TEST_CASE("Test Sync promise with CSharedPtr (succeed).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(CSyncPromise1Ptr(10, 20.0f, "test1"),
									 CSyncPromise2Ptr("test2", 30.0f, 40));
		})->Then([&](const CSyncPromise1Ptr &promise1,
					 const CSyncPromise2Ptr &promise2) {
			CHECK_INT(promise1->GetI(), 10);
			CHECK_FLOAT(promise1->GetJ(), 20.0f);
			CHECK_STRING(promise1->GetK(), "test1");

			CHECK_STRING(promise2->GetI(), "test2");
			CHECK_FLOAT(promise2->GetJ(), 30.0f);
			CHECK_INT(promise2->GetK(), 40);

			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(CSyncPromise1Ptr(50, 60.0f, "test3"),
									 CSyncPromise2Ptr("test4", 80.0f, 70));
		})->Then([&](const CSyncPromise1Ptr &promise1,
					 const CSyncPromise2Ptr &promise2) {
			CHECK_INT(promise1->GetI(), 50);
			CHECK_FLOAT(promise1->GetJ(), 60.0f);
			CHECK_STRING(promise1->GetK(), "test3");

			CHECK_STRING(promise2->GetI(), "test4");
			CHECK_FLOAT(promise2->GetJ(), 80.0f);
			CHECK_INT(promise2->GetK(), 70);

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with CSharedPtr (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise<CSyncPromise1Ptr, CSyncPromise2Ptr>();
		})->Then([&](const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &) {
			CHECK(false, "Should not catch");

			return CreateSyncPromise(CSyncPromise1Ptr(50, 60.0f, "test3"),
									 CSyncPromise2Ptr("test4", 80.0f, 70));
		})->Then([&](const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 1);
			idx = 2;

			return -100;
		});

		CHECK_INT(idx, 2);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(ProxyBuildInType)
{
	TEST_CASE("Test Sync promise with proxy built-in type (succeed).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(GetBuildInPromise(30, 40.0f, "test2"), 50, 60.0f, "test3");
		})->Then([&](int i, float j, const char *k, int i1, float j1, const char *k1) {
			CHECK_INT(i, 30);
			CHECK_FLOAT(j, 40.0f);
			CHECK_STRING(k, "test2");

			CHECK_INT(i1, 50);
			CHECK_FLOAT(j1, 60.0f);
			CHECK_STRING(k1, "test3");

			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(GetBuildInPromise(50, 60.0f, "test3"), 70, 80.0f, "test4");
		})->Then([&](int i, float j, const char *k, int i1, float j1, const char *k1) {
			CHECK_INT(i, 50);
			CHECK_FLOAT(j, 60.0f);
			CHECK_STRING(k, "test3");

			CHECK_INT(i1, 70);
			CHECK_FLOAT(j1, 80.0f);
			CHECK_STRING(k1, "test4");

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with built-in type (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(GetBuildInPromise(30, 40.0f, "test2"), 50, 60.0f, "test3");
		})->Then([&](int i, float j, const char *k, int i1, float j1, const char *k1) {
			CHECK_INT(i, 30);
			CHECK_FLOAT(j, 40.0f);
			CHECK_STRING(k, "test2");

			CHECK_INT(i1, 50);
			CHECK_FLOAT(j1, 60.0f);
			CHECK_STRING(k1, "test3");

			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(GetBuildInPromise(), 70, 80.0f, "test4");
		})->Then([&](int, float, const char *, int, float, const char *) {
			CHECK(false, "Should not catch");

			return CreateSyncPromise(GetBuildInPromise(50, 60.0f, "test3"), 70, 80.0f, "test4");
		})->Then([&](int, float, const char *, int, float, const char *) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 2);
			idx = 3;

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(ProxyStructureType)
{
	TEST_CASE("Test Sync promise with struct type (succeed).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(GetStructPromise(true), GetStructPromise(true));
		})->Then([&](const SyncPromiseStruct1 &promise1,
					 const SyncPromiseStruct2 &promise2,
					 const SyncPromiseStruct1 &promise3,
					 const SyncPromiseStruct2 &promise4) {
			CHECK_INT(promise1.i, 10);
			CHECK_FLOAT(promise1.j, 20.0f);
			CHECK_STRING(promise1.k, "test1");

			CHECK_STRING(promise2.i, "test2");
			CHECK_FLOAT(promise2.j, 40.0f);
			CHECK_INT(promise2.k, 30);

			CHECK_INT(promise3.i, 10);
			CHECK_FLOAT(promise3.j, 20.0f);
			CHECK_STRING(promise3.k, "test1");

			CHECK_STRING(promise4.i, "test2");
			CHECK_FLOAT(promise4.j, 40.0f);
			CHECK_INT(promise4.k, 30);

			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(GetStructPromise(true), GetStructPromise(true));
		})->Then([&](const SyncPromiseStruct1 &promise1,
					 const SyncPromiseStruct2 &promise2,
					 const SyncPromiseStruct1 &promise3,
					 const SyncPromiseStruct2 &promise4) {
			CHECK_INT(promise1.i, 10);
			CHECK_FLOAT(promise1.j, 20.0f);
			CHECK_STRING(promise1.k, "test1");

			CHECK_STRING(promise2.i, "test2");
			CHECK_FLOAT(promise2.j, 40.0f);
			CHECK_INT(promise2.k, 30);

			CHECK_INT(promise3.i, 10);
			CHECK_FLOAT(promise3.j, 20.0f);
			CHECK_STRING(promise3.k, "test1");

			CHECK_STRING(promise4.i, "test2");
			CHECK_FLOAT(promise4.j, 40.0f);
			CHECK_INT(promise4.k, 30);

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with struct type (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(GetStructPromise(false), GetStructPromise(true));
		})->Then([&](const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &,
					 const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &) {
			CHECK(false, "Should not catch");

			return CreateSyncPromise(GetStructPromise(true), GetStructPromise(true));
		})->Then([&](const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &,
					 const SyncPromiseStruct1 &,
					 const SyncPromiseStruct2 &) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 1);
			idx = 2;

			return -100;
		});

		CHECK_INT(idx, 2);
		CHECK_INT(ret, -100);
	}
}

DEFINE_TEST_GROUP(ProxySharedPtrType)
{
	TEST_CASE("Test Sync promise with CSharedPtr (succeed).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(GetSharedPtrPromise(true), GetSharedPtrPromise(true));
		})->Then([&](const CSyncPromise1Ptr &promise1,
					 const CSyncPromise2Ptr &promise2,
					 const CSyncPromise1Ptr &promise3,
					 const CSyncPromise2Ptr &promise4) {
			CHECK_INT(promise1->GetI(), 10);
			CHECK_FLOAT(promise1->GetJ(), 20.0f);
			CHECK_STRING(promise1->GetK(), "test1");

			CHECK_STRING(promise2->GetI(), "test2");
			CHECK_FLOAT(promise2->GetJ(), 30.0f);
			CHECK_INT(promise2->GetK(), 40);

			CHECK_INT(promise3->GetI(), 10);
			CHECK_FLOAT(promise3->GetJ(), 20.0f);
			CHECK_STRING(promise3->GetK(), "test1");

			CHECK_STRING(promise4->GetI(), "test2");
			CHECK_FLOAT(promise4->GetJ(), 30.0f);
			CHECK_INT(promise4->GetK(), 40);

			CHECK_INT(idx, 1);
			idx = 2;

			return CreateSyncPromise(GetSharedPtrPromise(true), GetSharedPtrPromise(true));
		})->Then([&](const CSyncPromise1Ptr &promise1,
					 const CSyncPromise2Ptr &promise2,
					 const CSyncPromise1Ptr &promise3,
					 const CSyncPromise2Ptr &promise4) {
			CHECK_INT(promise1->GetI(), 10);
			CHECK_FLOAT(promise1->GetJ(), 20.0f);
			CHECK_STRING(promise1->GetK(), "test1");

			CHECK_STRING(promise2->GetI(), "test2");
			CHECK_FLOAT(promise2->GetJ(), 30.0f);
			CHECK_INT(promise2->GetK(), 40);

			CHECK_INT(promise3->GetI(), 10);
			CHECK_FLOAT(promise3->GetJ(), 20.0f);
			CHECK_STRING(promise3->GetK(), "test1");

			CHECK_STRING(promise4->GetI(), "test2");
			CHECK_FLOAT(promise4->GetJ(), 30.0f);
			CHECK_INT(promise4->GetK(), 40);

			CHECK_INT(idx, 2);
			idx = 3;

			return 100;
		})->Catch([](void) {
			CHECK(false, "Should not catch");

			return -100;
		});

		CHECK_INT(idx, 3);
		CHECK_INT(ret, 100);
	}

	TEST_CASE("Test Sync promise with CSharedPtr (failure).") {
		int idx = 0;

		auto promise = GetBuildInPromise(10, 20.0f, "test1");

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_INT(i, 10);
			CHECK_FLOAT(j, 20.0f);
			CHECK_STRING(k, "test1");
			CHECK_INT(idx, 0);
			idx = 1;

			return CreateSyncPromise(GetSharedPtrPromise(false), GetSharedPtrPromise(true));
		})->Then([&](const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &,
					 const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &) {
			CHECK(false, "Should not catch");

			return CreateSyncPromise(GetSharedPtrPromise(true), GetSharedPtrPromise(true));
		})->Then([&](const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &,
					 const CSyncPromise1Ptr &,
					 const CSyncPromise2Ptr &) {
			CHECK(false, "Should not catch");

			return 100;
		})->Catch([&](void) {
			CHECK_INT(idx, 1);
			idx = 2;

			return -100;
		});

		CHECK_INT(idx, 2);
		CHECK_INT(ret, -100);
	}
}
#endif

void SyncPromise(void)
{
	START_TEST();

	RUN_TEST_GROUP(BuildInType);
#if 0
	RUN_TEST_GROUP(StructureType);
	RUN_TEST_GROUP(SharedPtrType);

	RUN_TEST_GROUP(AnonymousBuildInType);
	RUN_TEST_GROUP(AnonymousStructureType);
	RUN_TEST_GROUP(AnonymousSharedPtrType);

	RUN_TEST_GROUP(ProxyBuildInType);
	RUN_TEST_GROUP(ProxyStructureType);
	RUN_TEST_GROUP(ProxySharedPtrType);
#endif

	STOP_TEST();
}

