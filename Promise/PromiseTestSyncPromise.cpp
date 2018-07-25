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

DEFINE_TEST_GROUP(SyncPromise1Test)
{
	TEST_CASE("Failure case and not recover(return nullptr) in Catch.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		GetSyncPromise1Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (false) */
			return GetSyncPromise1Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](const char *, float, int, const CSyncPromise2Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Catch (take) */
		})->Catch([&](const char *i, float j, int k, const CSyncPromise2Ptr &promise) {
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_CLASS(promise, "test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we return nullptr */
			return nullptr;

		/* 2. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and not recover(not return) in Catch.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		GetSyncPromise1Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (false) */
			return GetSyncPromise1Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](const char *, float, int, const CSyncPromise2Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Catch (take) */
		})->Catch([&](const char *i, float j, int k, const CSyncPromise2Ptr &promise) {
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_CLASS(promise, "test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do not return */

		/* 2. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and do recover in Catch.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		int ret = GetSyncPromise1Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (false) */
			return GetSyncPromise1Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](const char *, float, int, const CSyncPromise2Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Catch (take) */
		})->Catch([&](const char *i, float j, int k, const CSyncPromise2Ptr &promise) {
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_CLASS(promise, "test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do the recover */
			return CSyncPromise1PromiseParamsPtr(50, 60.0f, "test3",
					CSyncPromise1Ptr(50, 60.0f, "test3"));

		/* 2. Then (take) */
		})->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_CLASS(promise, 50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

			return 100;
		});

		CHECK_VAL(idx, 3);
		CHECK_VAL(ret, 100);
	}

	TEST_CASE("Failure case and do recover in Catch (different order).") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		int ret = GetSyncPromise1Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (false) */
			return GetSyncPromise1Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](const char *, float, int, const CSyncPromise2Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

			return 100;

		/* 2. Catch (take) */
		})->Catch([&](const char *i, float j, int k, const CSyncPromise2Ptr &promise) {
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_CLASS(promise, "test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* This time we do the recover.
			 * The return type should match
			 * the return type of the previous Then method. */
			return 200;
		});

		CHECK_VAL(idx, 2);
		CHECK_VAL(ret, 200);
	}
}

DEFINE_TEST_GROUP(SyncPromise2Test)
{
	TEST_CASE("Failure case and not recover(return nullptr) in Catch.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		GetSyncPromise2Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (false) */
			return GetSyncPromise2Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Catch (take) */
		})->Catch([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_CLASS(promise, 30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we return nullptr */
			return nullptr;

		/* 2. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			/* Then method will not be called for promise 2. */
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and not recover(not return) in Catch.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		GetSyncPromise2Promise(10, 20.0f, "test1", true)
		/* 1. Then (get) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (false) */
			return GetSyncPromise2Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Catch (take) */
		})->Catch([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_CLASS(promise, 30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do not return */

		/* 2. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			/* Then method will not be called for promise 2. */
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and do recover in Catch.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		int ret = GetSyncPromise2Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (true) */
			return GetSyncPromise2Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not true) */
		})->Catch([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Catch (take) */
		})->Catch([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_CLASS(promise, 30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do the recover */
			return CSyncPromise2PromiseParamsPtr(50, 60.0f, "test3",
					CSyncPromise1Ptr(50, 60.0f, "test3"));

		/* 2. Then (take) */
		})->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			/* Now we are recovered from the Catch */
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_CLASS(promise, 50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

			return 100;
		});

		CHECK_VAL(idx, 3);
		CHECK_VAL(ret, 100);
	}

	TEST_CASE("Failure case and do recover in Catch (different order).") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		int ret = GetSyncPromise2Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (true) */
			return GetSyncPromise2Promise(30, 40.0f, "test2", false);

		/* 1. Catch (not take) */
		})->Catch([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

			return 100;

		/* 2. Catch (take) */
		})->Catch([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_CLASS(promise, 30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do the recover.
			 * The return type should match
			 * the return type of the previous Then method. */
			return 200;
		});

		CHECK_VAL(idx, 2);
		CHECK_VAL(ret, 200);
	}
}

DEFINE_TEST_GROUP(SyncPromiseMixTest)
{
	TEST_CASE("Mix SyncPromise1, SyncPromise2 and SyncPromise3.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		auto ret = GetSyncPromise1Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_CLASS(promise, 10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (true) */
			return GetSyncPromise1Promise(30, 40.0f, "test2", true);

		/* 1. Catch (not take) */
		})->Catch([&](const char *, float, int, const CSyncPromise2Ptr &) {
			CHECK(false, "Should not be called");

		/* 2. Then (take) */
		})->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_CLASS(promise, 30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

		/* 3. SyncPromise (false) */
			return GetSyncPromise2Promise(50, 60.0f, "test3", false);

		/* 2. Catch (not take) */
		})->Catch([&](const char *, float, int, const CSyncPromise2Ptr &) {
			CHECK(false, "Should not be called");

		/* 3. Then (not take) */
		})->Then([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		/* 4.1 Promise (true/ignore) */
			return GetSyncPromise2Promise(70, 80.0f, "test4", true);

		/* 3. Catch (take) */
		})->Catch([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_CLASS(promise, 50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

		/* 4.2 Promise (true) */
			return GetSyncPromise2Promise(90, 100.0f, "test5", true);

		/* 4. Then (take) */
		})->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(90, 100.0f, "test5");
			CHECK_CLASS(promise, 90, 100.0f, "test5");
			CHECK_VAL(idx++, 3);

		/* 5.1 Promise (false). */
			return GetSyncPromise1Promise(110, 120.0f, "test6", false);

		/* 4. Catch (not take) */
		})->Catch([&](int, float, const char *, const CSyncPromise1Ptr &) {
			CHECK(false, "Should not be called");

		/* 5.2 Promise (true/ignore). */
			return GetSyncPromise1Promise(111, 121.0f, "test6.1", true);

		/* 5. Catch (take) */
		})->Catch([&](const char *i, float j, int k, const CSyncPromise2Ptr &promise) {
			CHECK_BUILD_IN("test6", 120.0f, 110);
			CHECK_CLASS(promise, "test6", 120.0f, 110);
			CHECK_VAL(idx++, 4);

		/* 6.1 Promise (true only). */
			return CSyncPromise1PromiseParamsPtr(130, 140.0f, "test7",
					CSyncPromise1Ptr(130, 140.0f, "test7"));

		/* 5. Then (take, it is recovered) */
		})->Then([&](int i, float j, const char *k, const CSyncPromise1Ptr &promise) {
			CHECK_BUILD_IN(130, 140.0f, "test7");
			CHECK_CLASS(promise, 130, 140.0f, "test7");
			CHECK_VAL(idx++, 5);

		/* 6.2 Promise (true only) */
			return GetSyncPromise3Promise(150, 160.0f, "test8");

		/* 6. Then (take) */
		})->Then([&](const CSyncPromise2Ptr &promise, int i, float j, const char *k) {
			CHECK_CLASS(promise, "test8", 160.0f, 150);
			CHECK_BUILD_IN(150, 160.0f, "test8");
			CHECK_VAL(idx++, 6);

			return 100;
		});

		CHECK_VAL(idx, 7);
		//CHECK_VAL(ret, 100);
	}
}


void SyncPromise(void)
{
	START_TEST();

	RUN_TEST_GROUP(SyncPromise1Test);
	RUN_TEST_GROUP(SyncPromise2Test);
	RUN_TEST_GROUP(SyncPromiseMixTest);

	STOP_TEST();
}

