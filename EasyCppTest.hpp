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

#ifndef __EASYCPP_TEST_HPP__
#define __EASYCPP_TEST_HPP__

#include <stdio.h>
#include <Common/Color.hpp>

#define TEST_INFO(color, fmt, ...) \
	printf(color fmt COLOR_NONE "\n", ##__VA_ARGS__)

#define TEST_ERROR(func, line, fmt, ...) \
	TEST_INFO(COLOR_RED, "%s[%d]" fmt, func, line, ##__VA_ARGS__)

#define TEST_PASSED(fmt, ...) \
	TEST_INFO(COLOR_GREEN, fmt, ##__VA_ARGS__);

#define TEST_FAILED(fmt, ...) \
	TEST_INFO(COLOR_RED, fmt, ##__VA_ARGS__);

#ifdef SHOW_TEST_CASE
#define DEFINE_TEST_GROUP(name) \
	static auto TestCase##name(int &iStep, const char *topic = #name)

#define TEST_CASE(fmt, ...) \
	TEST_INFO(COLOR_CYAN, "%s[%02d]: " fmt, topic, ++iStep, ##__VA_ARGS__);

#else /* !SHOW_TEST_CASE */

#define DEFINE_TEST_GROUP(name) static auto TestCase##name(int &iStep)
#define TEST_CASE(desc)			++iStep;

#endif /* SHOW_TEST_CASE */

#define START_TEST() int iTestCases = 0;
#define RUN_TEST_GROUP(name) \
	do { \
		int i = 0; \
		TestCase##name(i); \
		iTestCases += i; \
	} while (0)

#define STOP_TEST() \
	TEST_PASSED("%d test cases passed", iTestCases) \

#define RUN_TEST(func, ...) \
	do { \
		TEST_INFO(COLOR_YELLOW, "================= Start testing " #func " ================="); \
		func(##__VA_ARGS__); \
	} while (0)

#define __CHECK(cond, func, line, fmt, ...) \
	do { \
		if (!(cond)) { \
			TEST_ERROR(func, line, ">>> " #cond " <<< failed. " fmt, ##__VA_ARGS__); \
			throw ES("Check fail"); \
		} \
	} while (0)

#define CHECK(cond, fmt, ...) \
	__CHECK(cond, __func__, __LINE__, fmt, ##__VA_ARGS__)

#define CHECK_THROW(...) \
	do { \
		try { \
			__VA_ARGS__; \
		} catch (...) { \
			break; \
		} \
		TEST_ERROR(__func__, __LINE__, "\"" #__VA_ARGS__ "\" does not throw error"); \
		throw ES("Check throw fail"); \
	} while (0)

#endif /* __EASYCPP_TEST_HPP__ */

