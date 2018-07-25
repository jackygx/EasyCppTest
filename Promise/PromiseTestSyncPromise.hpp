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

DEFINE_SYNC_PROMISE(SyncPromise1,
					(int, float, const char *, CSyncPromise1Ptr),
					(const char *, float, int, CSyncPromise2Ptr));
DEFINE_SYNC_PROMISE(SyncPromise2,
					(int, float, const char *, CSyncPromise1Ptr),
					(int, float, const char *, CSyncPromise1Ptr));

#define CHECK_BUILD_IN(_i, _j, _k) \
	CHECK_VAL(i, _i); \
	CHECK_VAL(j, _j); \
	CHECK_VAL(k, _k)

#define CHECK_CLASS(c, _i, _j, _k) \
	CHECK_VAL(c->GetI(), _i); \
	CHECK_VAL(c->GetJ(), _j); \
	CHECK_VAL(c->GetK(), _k);

inline CSyncPromise1PromisePtr GetSyncPromise1Promise(int i, float j, const char *k, bool result)
{
	if (result) {
		return CSyncPromise1PromisePtr(i, j, k, CSyncPromise1Ptr(i, j, k));
	} else {
		return CSyncPromise1PromisePtr(k, j, i, CSyncPromise2Ptr(k, j, i));
	}
}

inline CSyncPromise2PromisePtr GetSyncPromise2Promise(int i, float j, const char *k, bool result)
{
	return CSyncPromise2PromisePtr(i, j, k, CSyncPromise1Ptr(i, j, k), result);
}

inline decltype(auto) GetSyncPromise3Promise(int i, float j, const char *k)
{
	return CreateSyncPromise(CSyncPromise2Ptr(k, j, i), i, j, k);
}

#endif /* __PROMISE_TEST_SYNC_PROMISE_HPP__ */

