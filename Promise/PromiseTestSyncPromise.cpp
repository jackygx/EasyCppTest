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
}

DEFINE_TEST_GROUP(BuildIn3Test)
{
}

DEFINE_TEST_GROUP(BuildInMixTest)
{
	TEST_CASE("All succeed case with different type.") {
		int idx = 0;

		/* 1. we create a SyncPromise */
		auto promise = GetBuildIn1Promise(10, 20.0f, "test1", true);

		int ret = promise->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(10, 20.0f, "test1");
			CHECK_VAL(idx++, 0);

		/* 2. We return a SyncPromise */
			return GetBuildIn1Promise(30, 40.0f, "test2", true);
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(30, 40.0f, "test2");
			CHECK_VAL(idx++, 1);

		/* 3. We return a different SyncPromise */
			return GetBuildIn2Promise(50, 60.0f, "test3", true);
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(50, 60.0f, "test3");
			CHECK_VAL(idx++, 2);

		/* 4. Keep returning the SyncPromise */
			return GetBuildIn2Promise(70, 80.0f, "test4", true);
		})->Then([&](int i, float j, const char *k) {
			CHECK_BUILD_IN(70, 80.0f, "test4");
			CHECK_VAL(idx++, 3);

			return 100;
		})->Catch([&](const char *, float, int) {
			/* Catch promise 1.
			 * No error, will NOT be called.
			 * We return nullptr here.
			 * It should be the same effect to no return. */
			CHECK(false, "Should not be called");

			return nullptr;

		})->Catch([&](const char *, float, int) {
			/* Catch promise 2.
			 * No error, will NOT be called.
			 * We do not return here.
			 * It should be the same effect to return nullptr. */
			CHECK(false, "Should not be called");

		})->Catch([&](int, float, const char *) {
			/* Catch promise 3.
			 * No error, will NOT be called.
			 * We do not return here.
			 * It should be the same effect to return nullptr. */
			CHECK(false, "Should not be called");

		})->Catch([&](int, float, const char *) {
			/* Catch promise 4.
			 * No error, will NOT be called.
			 * We do not return here.
			 * It should be the same effect to return nullptr. */
			CHECK(false, "Should not be called");
		});

		CHECK_VAL(idx, 4);
		CHECK_VAL(ret, 100);
	}
}


void SyncPromise(void)
{
	START_TEST();

	RUN_TEST_GROUP(BuildIn1Test);
	RUN_TEST_GROUP(BuildIn2Test);
	RUN_TEST_GROUP(BuildIn3Test);
	RUN_TEST_GROUP(BuildInMixTest);
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

