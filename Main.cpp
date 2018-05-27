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

#include <stdlib.h>

#include <EasyCpp.hpp>

extern void SharedPtrTest(void);
extern void StringTest(void);
extern void SocketTest(void);
extern void DataStructTest(void);
extern void FileSystemTest(const CConstStringPtr &);

#define DO_TEST(name, ...) \
	if (0 == strcmp(argv[1], #name)) { \
		name##Test(__VA_ARGS__); \
	}

int main(int argc, char *argv[])
{
	InitSymbolPath(argv[0]);

	try {
		if (2 != argc) {
			SharedPtrTest();
			StringTest();
	//		SocketTest();
			DataStructTest();
			FileSystemTest(argv[0]);
		} else {
			DO_TEST(SharedPtr);
			DO_TEST(String);
			DO_TEST(Socket);
			DO_TEST(DataStruct);
			DO_TEST(FileSystem, argv[0]);
		}
	} catch (const IException &e) {
		e.Show();
	} catch (...) {
		TRACE_ERROR("Unknown error!!!");
	}

	return 0;
}

