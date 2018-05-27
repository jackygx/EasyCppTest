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

typedef CList<int> IntList;

void Test1(const IntList &list)
{
	list.GetSize();

	printf("Start iterator6: ");
	list.ForEach([&](int val) {
		printf("%d ", val);
		return -3 != val;
	});
	printf("\n");
}

void TestCList(void)
{
	IntList list;

	CHECK_PARAM(list.Empty());

	list.PushBack(1);
	list.PushBack(2, 3, 4);
	list.PushFront(-1);
	list.PushFront(-2, -3, -4);

	printf("List size: %d\n", list.GetSize());
	printf("First element: %d\n", list.PopFront());
	printf("Last elememt: %d\n", list.PopBack());

	printf("Start iterator1: ");
	for (auto it = list.Begin(); it != list.End(); ++it) {
		printf("%d ", *it);
	}
	printf("\n");

	printf("Start iterator2: ");
	for (auto it : list) {
		printf("%d ", it);
	}
	printf("\n");

	printf("Start iterator3: ");
	list.ForEach([](int it) {
		printf("%d ", it);
	});
	printf("\n");

	printf("Start iterator4: ");
	list.ForEach([&](int val, IntList::Iterator it) {
		printf("%d ", val);
		if (val == 1) {
			printf("(deleted) ");
			list.Erase(it);
		}
	});
	printf("\n");

	printf("Start iterator5: ");
	list.ForEach([](int val) {
		printf("%d ", val);
		return val != -1;
	});
	printf("\n");

	printf("Start iterator6: ");
	list.ForEach([&](int val, IntList::Iterator it) {
		printf("%d ", val);
		if (val == -2) {
			printf("(deleted) ");
			list.Erase(it);
			return false;
		}

		return true;
	});
	printf("\n");

	Test1(list);
}
