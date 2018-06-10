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

#ifndef __SHARED_PTR_TEST_HPP__
#define __SHARED_PTR_TEST_HPP__

#include <EasyCpp.hpp>
#include "../EasyCppTest.hpp"

#include "Base.hpp"
#include "Derive.hpp"

template <class T>
inline void CheckEmpty(T &&t, const char *func, int line)
{
	__CHECK(!t, func, line, "%p", t.Get());
	__CHECK(0 == t.GetRef(), func, line, "Ref: %d", t.GetRef());
	__CHECK(0 == t.GetWeakRef(), func, line, "WeakRef: %d", t.GetWeakRef());
}

#define CHECK_EMPTY(t) CheckEmpty(t, __func__, __LINE__)

template <class T>
inline void CheckID(T &&t, ClassIdentify id, const char *func, int line)
{
	__CHECK(id == t->Identify(), func, line, "Identify: %d", t->Identify());
}

#define CHECK_ID(base, id) CheckID(base, id, __func__, __LINE__)

template <class T>
inline void CheckBaseA(T &&base, ClassIdentify vid,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CHECK(base, func, line, "Base is nullptr");
	CheckID(base, CI_BASEA, func, line);
	__CHECK(vid == base->GetBaseAType(), func, line,
			"GetBaseAType: %d", base->GetBaseAType());
	__CHECK(ref == base.GetRef(), func, line, "Ref: %d", base.GetRef());
	__CHECK(wref == base.GetWeakRef(), func, line, "WeakRef: %d", base.GetWeakRef());
}
#define CHECK_BASEA(base, vid, ref, wref) \
	CheckBaseA(base, vid, ref, wref, __func__, __LINE__)

template <class T>
inline void __CheckBaseB(T &&base, ClassIdentify vid,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CHECK(base, func, line, "Base is nullptr");
	CheckID(base, CI_BASEB, func, line);
	__CHECK(vid == base->GetBaseBType(), func, line,
			"GetBaseAType: %d", base->GetBaseBType());
	__CHECK(ref == base.GetRef(), func, line, "Ref: %d", base.GetRef());
	__CHECK(wref == base.GetWeakRef(), func, line, "WeakRef: %d", base.GetWeakRef());
}

template <class T,
		 ENABLE_IF(!IS_CONST(T))>
inline void CheckBaseB(const CSharedPtr<T> &base, ClassIdentify vid,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CheckBaseB(base, vid, ref, wref, func, line);

	do {
		auto share1(base->ShareTest());
		__CheckBaseB(base, vid, ref + 1, wref, func, line);
		__CheckBaseB(share1, vid, ref + 1, wref, func, line);

		auto share2(base->ConstShareTest());
		__CheckBaseB(base, vid, ref + 2, wref, func, line);
		__CheckBaseB(share1, vid, ref + 2, wref, func, line);
		__CheckBaseB(share2, vid, ref + 2, wref, func, line);
	} while (0);

	__CheckBaseB(base, vid, ref, wref, func, line);
}

template <class T,
		 ENABLE_IF(IS_CONST(T))>
inline void CheckBaseB(const CSharedPtr<T> &base, ClassIdentify vid,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CheckBaseB(base, vid, ref, wref, func, line);

	do {
		auto share2(base->ConstShareTest());
		__CheckBaseB(base, vid, ref + 1, wref, func, line);
		__CheckBaseB(share2, vid, ref + 1, wref, func, line);
	} while (0);

	__CheckBaseB(base, vid, ref, wref, func, line);
}
#define CHECK_BASEB(base, vid, ref, wref) \
	CheckBaseB(base, vid, ref, wref, __func__, __LINE__)

template <class T>
void inline __CheckDerive(T &&derive,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CHECK(derive, func, line, "derive is nullptr");
	CheckID(derive, CI_DERIVE, func, line);
	__CHECK(CI_BASEA_DERIVE == derive->GetBaseAType(), func, line,
			"GetBaseAType: %d", derive->GetBaseAType());
	__CHECK(CI_BASEB_DERIVE == derive->GetBaseBType(), func, line,
			"GetBaseAType: %d", derive->GetBaseBType());
	__CHECK(ref == derive.GetRef(), func, line, "Ref: %d", derive.GetRef());
	__CHECK(wref == derive.GetWeakRef(), func, line, "WeakRef: %d", derive.GetWeakRef());
}

template <class T,
		 ENABLE_IF(!IS_CONST(T))>
inline void CheckDerive(const CSharedPtr<T> &derive,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CheckDerive(derive, ref, wref, func, line);

	do {
		auto share1(derive->ShareTest());
		__CheckDerive(derive, ref + 1, wref, func, line);
		__CheckDerive(share1, ref + 1, wref, func, line);

		auto share2(derive->ConstShareTest());
		__CheckDerive(derive, ref + 2, wref, func, line);
		__CheckDerive(share2, ref + 2, wref, func, line);
		__CheckDerive(share2, ref + 2, wref, func, line);
	} while (0);

	__CheckDerive(derive, ref, wref, func, line);
}

template <class T,
		 ENABLE_IF(IS_CONST(T))>
inline void CheckDerive(const CSharedPtr<T> &derive,
		uint32_t ref, uint32_t wref, const char *func, int line)
{
	__CheckDerive(derive, ref, wref, func, line);

	do {
		auto share2(derive->ConstShareTest());
		__CheckDerive(derive, ref + 1, wref, func, line);
		__CheckDerive(share2, ref + 1, wref, func, line);
	} while (0);

	__CheckDerive(derive, ref, wref, func, line);
}

#define CHECK_DERIVE(derive, ref, wref) \
	CheckDerive(derive, ref, wref, __func__, __LINE__)

#define CHECK_DIFFERENT_PTR(ptr1, ptr2) \
	do { \
		CHECK((ptr1) != (ptr2), #ptr1 ": %p, " #ptr2 ": %p", ptr1, ptr2); \
	} while (0)

#define CHECK_SAME_PTR(ptr1, ptr2) \
	do { \
		CHECK((ptr1) == (ptr2), #ptr1 ": %p, " #ptr2 ": %p", ptr1, ptr2); \
	} while (0)

void Constructor(void);
void Equal(void);
void IsEqual(void);
void AddEqual(void);
void SubEqual(void);
void Compare(void);
void Token(void);
void OtherOperators(void);
void Others(void);

#endif /* __SHARED_PTR_TEST_HPP__ */

