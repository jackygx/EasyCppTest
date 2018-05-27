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

#ifndef __COMPARE_HPP__
#define __COMPARE_HPP__

#include <EasyCpp.hpp>

DEFINE_CLASS(CompareNone);
DEFINE_CLASS(CompareBoth);
DEFINE_CLASS(CompareBigger);
DEFINE_CLASS(CompareSmaller);
HAS_MEMBER(Get);

class CCompareNone
{
public:
	inline CCompareNone(int val) :
		mVal(val)
	{
		/* Does nothing */
	}

	inline int Get(void) const
	{
		return mVal;
	}

	template <class T>
	inline bool operator == (const T &t) const
	{
		return mVal == t->Get();
	}

	inline bool operator == (const CCompareNone &i) const
	{
		return mVal == i.Get();
	}

private:
	int mVal;
};

class CCompareBoth
{
public:
	inline CCompareBoth(int val) :
		mVal(val)
	{
		/* Does nothing */
	}

	inline int Get(void) const
	{
		return mVal;
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator == (const CSharedPtr<T> &t) const
	{
		return mVal == t->Get();
	}

	inline bool operator == (const CCompareBoth &i) const
	{
		return mVal == i.Get();
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator > (const CSharedPtr<T> &t) const
	{
		return mVal > t->Get();
	}

	inline bool operator > (const CCompareBoth &i) const
	{
		return mVal > i.Get();
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator < (const CSharedPtr<T> &t) const
	{
		return mVal < t->Get();
	}

	inline bool operator < (const CCompareBoth &i) const
	{
		return mVal < i.Get();
	}

private:
	int mVal;
};


class CCompareBigger
{
public:
	inline CCompareBigger(int val) :
		mVal(val)
	{
		/* Does nothing */
	}

	inline int Get(void) const
	{
		return mVal;
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator == (const CSharedPtr<T> &t) const
	{
		return mVal == t->Get();
	}

	inline bool operator == (const CCompareBigger &i) const
	{
		return mVal == i.Get();
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator > (const CSharedPtr<T> &t) const
	{
		return mVal > t->Get();
	}

	inline bool operator > (const CCompareBoth &i) const
	{
		return mVal > i.Get();
	}

private:
	int mVal;
};

class CCompareSmaller
{
public:
	inline CCompareSmaller(int val) :
		mVal(val)
	{
		/* Does nothing */
	}

	inline int Get(void) const
	{
		return mVal;
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator == (const CSharedPtr<T> &t) const
	{
		return mVal == t->Get();
	}

	inline bool operator == (const CCompareSmaller&i) const
	{
		return mVal == i.Get();
	}

	template <class T,
			 ENABLE_IF(has_member_Get<T>)>
	inline bool operator < (const CSharedPtr<T> &t) const
	{
		return mVal < t->Get();
	}

	inline bool operator < (const CCompareSmaller&i) const
	{
		return mVal < i.Get();
	}

private:
	int mVal;
};

#endif /* __COMPARE_HPP__ */

