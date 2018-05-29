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

#include "SharedPtrTest.hpp"

void SharedPtrTest(void)
{
	RUN_TEST(Constructor);
	RUN_TEST(Equal);
	RUN_TEST(IsEqual);
	RUN_TEST(AddEqual);
	RUN_TEST(SubEqual);
	RUN_TEST(Compare);
	RUN_TEST(Token);
	RUN_TEST(OtherOperators);
	RUN_TEST(Others);
}

