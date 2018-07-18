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

#include <EasyCpp.hpp>
#include "EasyCppTest.hpp"

extern void SharedPtrTest(void);
extern void WeakPtrTest(void);
extern void PromiseTest(void);

int main(int, char *argv[])
{
	/* To show the pretty call stack */
	InitSymbolPath(argv[0]);

	try {
		CPoolStastics<>::ResetPool();

		RUN_TEST(SharedPtrTest);
		RUN_TEST(WeakPtrTest);
		RUN_TEST(PromiseTest);

//		CPoolStastics<>::ShowPoolUsage();

	} catch (const IException *e) {
		e->Show();
		delete e;
	} catch (...) {
		TRACE_ERROR("Unknown error!!!");
	}

	return 0;
}

