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

#ifndef __PROMISE_TEST_SYNC_PROMISE_HPP__
#define __PROMISE_TEST_SYNC_PROMISE_HPP__

#include <Interface/Interface.hpp>

DEFINE_SYNC_PROMISE(BuildIn, (int, float, const char *), (int));

#define CHECK_BUILD_IN(_i, _j, _k) \
	CHECK_VAL(i, _i); \
	CHECK_VAL(j, _j); \
	CHECK_VAL(k, _k)

CBuildInPromisePtr GetBuildInSucceedPromise(int i, float j, const char *k)
{
	return CBuildInPromisePtr(i, j, k);
}

CBuildInPromisePtr GetBuildInFailPromise(int i)
{
	return CBuildInPromisePtr(i);
}

#if 0
struct SyncPromiseStruct1 {
	int i;
	float j;
	const char *k;
};

struct SyncPromiseStruct2 {
	const char *i;
	float j;
	int k;
};

DEFINE_SYNC_PROMISE(Structure,
					(struct SyncPromiseStruct1, struct SyncPromiseStruct2));

CStructurePromisePtr GetStructPromise(bool result)
{
	struct SyncPromiseStruct1 promise1 = {
		.i = 10,
		.j = 20.0f,
		.k = "test1",
	};

	struct SyncPromiseStruct2 promise2 = {
		.i = "test2",
		.j = 40.0f,
		.k = 30,
	};

	if (result) {
		return CStructurePromisePtr(promise1, promise2);
	} else {
		return CStructurePromisePtr();
	}
}

DEFINE_CLASS(SyncPromise1);
DEFINE_CLASS(SyncPromise2);

class CSyncPromise1
{
public:
	CSyncPromise1(int i, float j, const char *k) :
		mI(i),
		mJ(j),
		mK(k)
	{
		/* Does nothing */
	}

	int GetI(void) const
	{
		return mI;
	}

	float GetJ(void) const
	{
		return mJ;
	}

	const char *GetK(void) const
	{
		return mK;
	}

private:
	int mI;
	float mJ;
	const char *mK;
};

class CSyncPromise2
{
public:
	CSyncPromise2(const char *i, float j, int k) :
		mI(i),
		mJ(j),
		mK(k)
	{
		/* Does nothing */
	}

	const char *GetI(void) const
	{
		return mI;
	}

	float GetJ(void) const
	{
		return mJ;
	}

	int GetK(void) const
	{
		return mK;
	}

private:
	const char *mI;
	float mJ;
	int mK;
};

DEFINE_SYNC_PROMISE(SharedPtr,
					CSyncPromise1Ptr,
					CSyncPromise2Ptr);

CSharedPtrPromisePtr GetSharedPtrPromise(bool result)
{
	CSyncPromise1Ptr promise1(10, 20.0f, "test1");
	CSyncPromise2Ptr promise2("test2", 30.0f, 40);

	if (result) {
		return CSharedPtrPromisePtr(promise1, promise2);
	} else {
		return CSharedPtrPromisePtr();
	}
}
#endif

#endif /* __PROMISE_TEST_SYNC_PROMISE_HPP__ */

