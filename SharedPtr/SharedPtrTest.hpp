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

#define SHOW_TEST_STEP

#include <EasyCpp.hpp>
#include <TestFramework.hpp>

#include "Base.hpp"
#include "Derive.hpp"

#define CHECK_ID(base, id) \
	do { \
		CHECK((id) == (base)->Identify(), \
			  "Identify: ", DEC((base)->Identify())); \
	} while (0)

/* Do not use inline function.
 * Otherwise, when error happens,
 * we cannot know exactly which line cause the error. */
#define CHECK_EMPTY(t) \
	CHECK(!t, HEX(t.Get())); \
	CHECK(0 == t.GetRef(), "Ref: ", DEC(t.GetRef())); \
	CHECK(0 == t.GetWeakRef(), "WeakRef: ", DEC(t.GetWeakRef()));

#define CHECK_BASEA(base, vid, ref, wref) \
	CHECK(base, "Base is nullptr"); \
	CHECK_ID(base, CI_BASEA); \
	CHECK(vid == base->GetBaseAType(), "GetBaseAType:: ", DEC(base->GetBaseAType())); \
	CHECK(ref == base.GetRef(), "Ref: ", DEC(base.GetRef())); \
	CHECK(wref == base.GetWeakRef(), "WeakRef: ", DEC(base.GetWeakRef()));

#define CHECK_BASEB(base, vid, ref, wref) \
	CHECK(base, "Base is nullptr"); \
	CHECK_ID(base, CI_BASEB); \
	CHECK(vid == base->GetBaseBType(), "GetBaseAType:: ", DEC(base->GetBaseBType())); \
	CHECK(ref == base.GetRef(), "Ref: ", DEC(base.GetRef())); \
	CHECK(wref == base.GetWeakRef(), "WeakRef: ", DEC(base.GetWeakRef()));

#define CHECK_DERIVE(derive, ref, wref) \
	CHECK(derive, "derive is nullptr"); \
	CHECK_ID(derive, CI_DERIVE); \
	CHECK(CI_BASEA_DERIVE == derive->GetBaseAType(), "GetBaseAType:: ", DEC(derive->GetBaseAType())); \
	CHECK(CI_BASEB_DERIVE == derive->GetBaseBType(), "GetBaseAType:: ", DEC(derive->GetBaseBType())); \
	CHECK(ref == derive.GetRef(), "Ref: ", DEC(derive.GetRef())); \
	CHECK(wref == derive.GetWeakRef(), "WeakRef: ", DEC(derive.GetWeakRef()));

#define CHECK_SAME_PTR(ptr1, ptr2) \
	do { \
		CHECK((ptr1).Get() == (ptr2).Get(), \
				#ptr1": ", HEX((ptr1).Get()), \
				#ptr2": ", HEX((ptr2).Get())); \
	} while (0)

#define CHECK_DIFFERENT_PTR(ptr1, ptr2) \
	do { \
		CHECK((ptr1).Get() != (ptr2).Get(), \
				#ptr1": ", HEX((ptr1).Get()), \
				#ptr2": ", HEX((ptr2).Get())); \
	} while (0)

#define CHECK_SAME(l, r, ToString) \
	do { \
		CHECK((l) == (r), \
			#l": ", ToString(l), \
			#r": ", ToString(r)); \
	} while (0)

void Constructor(void);
void Equal(void);
void IsEqual(void);
void AddEqual(void);
void SubEqual(void);
void Compare(void);
void Token(void);

#endif /* __SHARED_PTR_TEST_HPP__ */

