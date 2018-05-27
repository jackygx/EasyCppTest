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

#ifndef __DERIVE_HPP__
#define __DERIVE_HPP__

#include "Base.hpp"
#include "HelpType.hpp"

DEFINE_CLASS(Derive);

/* Used for Constructor overload */
DEFINE_HELP_TYPE(DeriveConstructor);
/* Used for Equal operator overload */
DEFINE_HELP_TYPE(DeriveEqual);
/* Used for IsEqual operator overload */
DEFINE_HELP_TYPE(DeriveIsEqual);
/* Used for AddEqual operator overload */
DEFINE_HELP_TYPE(DeriveAddEqual);
/* Used for SubEqual operator overload */
DEFINE_HELP_TYPE(DeriveSubEqual);

/* Used for implicit conversion */
DEFINE_CLASS(TypeDeriveImplicitConvert);

class CDerive :
	public CBaseA,
	public CBaseB,
	public CEnableSharedPtr<CDerive>
{
public:
	inline CDerive(int i = 0) :
		mNum(i)
	{
		/* Does nothing */
	}

	inline CDerive(const CTypeDeriveConstructorPtr &i,
				   const CTypeDeriveConstructorPtr &j,
				   const CTypeDeriveConstructorPtr &k) :
		mNum(100 + i->Get() + j->Get() + k->Get())
	{
		/* Does nothing */
	}

	inline CDerive(const CTypeDeriveConstructorPtr &i,
				   CTypeDeriveConstructorPtr &&j,
				   const CTypeDeriveConstructorPtr &k) :
		mNum(200 + i->Get() + j->Get() + k->Get())
	{
		/* Does nothing */
	}

	inline int Get(void) const
	{
		return mNum;
	}

	inline CDerive &operator = (const CTypeDeriveEqualPtr &i)
	{
		mNum = i->Get();
		return *this;
	}

	inline bool operator == (const CTypeDeriveIsEqualPtr &i) const
	{
		return mNum == i->Get();
	}

	inline bool operator == (const CDerive &i) const
	{
		return mNum == i.Get();
	}

	inline void operator += (const CTypeDeriveAddEqualPtr &i)
	{
		mNum += i->Get();
	}

	inline void operator += (const CDerive &i)
	{
		mNum += i.Get();
	}

	inline void operator -= (const CTypeDeriveSubEqualPtr &i)
	{
		mNum -= i->Get();
	}

	inline void operator -= (const CDerive &i)
	{
		mNum -= i.Get();
	}

	inline int operator [] (int i)
	{
		return i + mNum;
	}

	inline int operator [] (int i) const
	{
		return i;
	}

	inline int operator () (int i)
	{
		return i + mNum;
	}

	inline int operator () (int i) const
	{
		return i;
	}

	inline void operator () (const char *buf)
	{
		mNum += strlen(buf);
	}

	inline void operator () (const char *) const
	{
		/* Does nothing */
	}

	inline void SetNum(int i)
	{
		mNum = i;
	}

	inline enum ClassIdentify Identify(void) const
	{
		return CI_DERIVE;
	}

	virtual enum ClassIdentify GetBaseAType(void) const
	{
		return CI_BASEA_DERIVE;
	}

	virtual enum ClassIdentify GetBaseBType(void) const
	{
		return CI_BASEB_DERIVE;
	}

private:
	int mNum;
};

class CTypeDeriveImplicitConvert
{
public:
	inline CTypeDeriveImplicitConvert(int val) :
		mVal(val)
	{
		/* Does nothing */
	}

	template <class T = CDerivePtr,
			 ENABLE_IF(std::is_same<T, CDerivePtr>)>
	inline CDerivePtr Convert(void) const
	{
		return CDerivePtr(mVal);
	}

private:
	int mVal;
};

#endif /* __DERIVE_HPP__ */

