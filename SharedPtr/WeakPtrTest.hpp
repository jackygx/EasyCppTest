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

#ifndef __WEAK_PTR_TEST_HPP__
#define __WEAK_PTR_TEST_HPP__

#include "SharedPtrTest.hpp"

#define CHECK_WEAK_EMPTY(t) \
	CHECK(!t.Lock(), "Lock: %p", t.Lock().Get()); \
	CHECK(0 == t.GetRef(), "Ref: %d", t.GetRef()); \
	CHECK(0 == t.GetWeakRef(), "WeakRef: %d", t.GetWeakRef());

#define CHECK_WEAK(t, ref, wref) \
	CHECK(t.Lock(), "Weak reference is empty"); \
	CHECK(ref == t.GetRef(), "Ref: %d", t.GetRef()); \
	CHECK(wref == t.GetWeakRef(), "WeakRef: %d", t.GetWeakRef());

#endif /* __WEAK_PTR_TEST_HPP__ */

