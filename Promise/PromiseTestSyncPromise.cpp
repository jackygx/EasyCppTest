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

DEFINE_TEST_GROUP(BuildIn1Test)
{
	TEST_CASE("Failure case and not recover(return nullptr) in Catch.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		GetBuildIn1Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn1Promise(30, 40.0f, "test2", false);

		})->Catch([&](const char *, float, int) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Catch([&](const char *i, float j, int k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we return nullptr */
			return nullptr;

		})->Then([&](int, float, const char *) {
			/* Then method will not be called for promise 2. */
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and not recover(not return) in Catch.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		GetBuildIn1Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn1Promise(30, 40.0f, "test2", false);

		})->Catch([&](const char *, float, int) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Catch([&](const char *i, float j, int k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do not return */

		})->Then([&](int, float, const char *) {
			/* Then method will not be called for promise 2. */
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and do recover in Catch.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		int ret = GetBuildIn1Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn1Promise(30, 40.0f, "test2", false);

		})->Catch([&](const char *, float, int) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Catch([&](const char *i, float j, int k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN("test2", 40.0f, 30);
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do the recover */
			return CBuildIn1PromiseParamsPtr(50, 60.0f, "test3");

		})->Then([&](int i, float j, const char *k) {
			/* Now we are recovered from the Catch */
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

			return 100;
		});

		CHECK_VAL(idx, 3);
		CHECK_VAL(ret, 100);
	}

	TEST_CASE("Failure case and do recover in Catch (different order).") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		int ret = GetBuildIn1Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn1Promise(30, 40.0f, "test2", false);

		})->Catch([&](const char *, float, int) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Then([&](int, float, const char *) {
		/* Because the Catch is not called (not recovered).
		 * This Then method will NOT be called. */
			CHECK(false, "Should not be called");

			return 100;

		})->Catch([&](const char *i, float j, int k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN("test2", 40.0f, 30);
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

DEFINE_TEST_GROUP(BuildIn2Test)
{
	TEST_CASE("Failure case and not recover(return nullptr) in Catch.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		GetBuildIn2Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn2Promise(30, 40.0f, "test2", false);

		})->Catch([&](int, float, const char *) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Catch([&](int i, float j, const char *k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we return nullptr */
			return nullptr;

		})->Then([&](int, float, const char *) {
			/* Then method will not be called for promise 2. */
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and not recover(not return) in Catch.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		GetBuildIn2Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn2Promise(30, 40.0f, "test2", false);

		})->Catch([&](int, float, const char *) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Catch([&](int i, float j, const char *k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do not return */

		})->Then([&](int, float, const char *) {
			/* Then method will not be called for promise 2. */
			CHECK(false, "Should not be called");

		});

		CHECK_VAL(idx, 2);
	}

	TEST_CASE("Failure case and do recover in Catch.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		int ret = GetBuildIn2Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn2Promise(30, 40.0f, "test2", false);

		})->Catch([&](int, float, const char *) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Catch([&](int i, float j, const char *k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

			/* Do not recover from the error.
			 * This time we do the recover */
			return CBuildIn2PromiseParamsPtr(50, 60.0f, "test3");

		})->Then([&](int i, float j, const char *k) {
			/* Now we are recovered from the Catch */
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

			return 100;
		});

		CHECK_VAL(idx, 3);
		CHECK_VAL(ret, 100);
	}

	TEST_CASE("Failure case and do recover in Catch (different order).") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		int ret = GetBuildIn2Promise(10, 20.0f, "test1", true)
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a false SyncPromise */
			return GetBuildIn2Promise(30, 40.0f, "test2", false);

		})->Catch([&](int, float, const char *) {
		/* Catch promise 1. No error, will NOT be called. */
			CHECK(false, "Should not be called");

		})->Then([&](int, float, const char *) {
		/* Because the Catch is not called (not recovered).
		 * This Then method will NOT be called. */
			CHECK(false, "Should not be called");

			return 100;

		})->Catch([&](int i, float j, const char *k) {
		/* Catch promise 2. Will be called. */
			CHECK_BUILD_IN(30, 40.0f, "test2");
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

DEFINE_TEST_GROUP(BuildInMixTest)
{
	TEST_CASE("Mix BuildIn1, BuildIn2 and BuildIn3.") {
		int idx = 0;

		/* 1. SyncPromise (true) */
		auto ret = GetBuildIn1Promise(10, 20.0f, "test1", true)
		/* 1. Then (take) */
		->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. SyncPromise (true) */
			return GetBuildIn1Promise(30, 40.0f, "test2", true);

		/* 1. Catch (not take) */
		})->Catch([&](const char *, float, int) {
			CHECK(false, "Should not be called");

		/* 2. Then (take) */
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

		/* 3. SyncPromise (false) */
			return GetBuildIn2Promise(50, 60.0f, "test3", false);

		/* 2. Catch (not take) */
		})->Catch([&](const char *, float, int) {
			CHECK(false, "Should not be called");

		/* 3. Then (not take) */
		})->Then([&](int, float, const char *) {
			CHECK(false, "Should not be called");

		/* 4.1 Promise (true/ignore) */
			return GetBuildIn2Promise(70, 80.0f, "test4", true);

		/* 3. Catch (take) */
		})->Catch([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

		/* 4.2 Promise (true) */
			return GetBuildIn2Promise(90, 100.0f, "test5", true);

		/* 4. Then (take) */
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(90, 100.0f, "test5");
			CHECK_VAL(idx++, 3);

		/* 5.1 Promise (false). */
			return GetBuildIn1Promise(110, 120.0f, "test6", false);

		/* 4. Catch (not take) */
		})->Catch([&](int, float, const char *) {
			CHECK(false, "Should not be called");

		/* 5.2 Promise (true/ignore). */
			return GetBuildIn1Promise(111, 121.0f, "test6.1", true);

		/* 5. Catch (take) */
		})->Catch([&](const char *i, float j, int k) {
			CHECK_BUILD_IN("test6", 120.0f, 110);
			CHECK_VAL(idx++, 4);

		/* 6.1 Promise (true only). */
			return CBuildIn1PromiseParamsPtr(130, 140.0f, "test7");

		/* 5. Then (take, it is recovered) */
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(130, 140.0f, "test7");
			CHECK_VAL(idx++, 5);

		/* 6.2 Promise (true only) */
			return GetBuildIn3Promise(150, 160.0f, "test8");

		/* 6. Then (take) */
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(150, 160.0f, "test8");
			CHECK_VAL(idx++, 6);

			return 100;
		});

		CHECK_VAL(idx, 6);
		//CHECK_VAL(ret, 100);
	}
}


void SyncPromise(void)
{
	START_TEST();

	RUN_TEST_GROUP(BuildIn1Test);
	RUN_TEST_GROUP(BuildIn2Test);
	RUN_TEST_GROUP(BuildInMixTest);

	STOP_TEST();
}

