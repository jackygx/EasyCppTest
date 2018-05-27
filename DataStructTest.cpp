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

#include "TestCommon.hpp"

static void map(void)
{
	typedef CMap<CConstStringPtr, CConstStringPtr> StringMap;
	typedef CSharedPtr<StringMap> StringMapPtr;

	StringMapPtr map;

	TEST_STEP(1, 1, "Map set get and []", "Should work") {
		map["key1"] = "val1";
		map["key2"] = "val2";
		map["key3"] = "val3";
		map->Set("key4", "val4");
		map->Set("key5", "val5");
		map->Set("key6", "val6");

		CHECK("val1" == map->Get("key1"), "val for key1: %s", map->Get("key1")->ToCStr());
		CHECK("val2" == map->Get("key2"), "val for key2: %s", map->Get("key2")->ToCStr());
		CHECK("val3" == map->Get("key3"), "val for key3: %s", map->Get("key3")->ToCStr());

		CHECK("val4" == map["key4"], "val for key4: %s", map["key4"]->ToCStr());
		CHECK("val5" == map["key5"], "val for key5: %s", map["key5"]->ToCStr());
		CHECK("val6" == map["key6"], "val for key6: %s", map["key6"]->ToCStr());

		CHECK("" == map->Get("key7"), "key7 is not null: %d", map->Get("key7")->GetSize());
		CHECK("" == map["key8"], "key8 is not null: %d", map->Get("key8")->GetSize());
	}

	TEST_STEP(1, 2, "Map GetSize", "Should work") {
		CHECK(8 == map->GetSize(), "map size: %d", map->GetSize());
	}

	TEST_STEP(1, 3, "Map iterator", "Should work") {
		const char *keys[] = {
			"key1",
			"key2",
			"key3",
			"key4",
			"key5",
			"key6",
			"key7",
			"key8",
		};

		const char *vals[] = {
			"val1",
			"val2",
			"val3",
			"val4",
			"val5",
			"val6",
			"",
			"",
		};

		int i = 0;
		map->Iter()->ForEach([&](const CConstStringPtr &key, const CConstStringPtr &val) {
			CHECK(key == keys[i], "[%d]: key: %s", i, key->ToCStr());
			CHECK(val == vals[i], "[%d]: val: %s", i, val->ToCStr());
			++i;
		});

		CHECK(i == ARRAY_SIZE(vals), "i: %d", i);
	}
}

DEFINE_CLASS(TestFunc);
class CTestFunc
{
public:
	CTestFunc(void)
	{
		++sInstCnt;
	}

	~CTestFunc(void)
	{
		--sInstCnt;
	}

	int Get(void) const
	{
		return 10;
	}

public:
	static int sInstCnt;
};

int CTestFunc::sInstCnt = 0;

DEFINE_FUNC(FuncTest, int(void));

static void FuncTest(const FuncTestFn &fn)
{
	auto val(fn());
	CHECK(40 == val, "Invalid val: %d", val);
}

static void func(void)
{
	TEST_STEP(1, 1, "Func", "Func")  {
		{
			FuncTestFn fn(nullptr);
			{
				CTestFuncPtr a;
				CTestFuncPtr b;
				CTestFuncPtr c;
				CTestFuncPtr d;

				fn = [a, b, c, d](void) {
					return a->Get() + b->Get() + c->Get() + d->Get();
				};
			}

			FuncTest(fn);
		}

		CHECK(CTestFunc::sInstCnt == 0, "Inst: %d", CTestFunc::sInstCnt);
	}
}

void DataStructTest(void)
{
	DO_TEST(map);
	DO_TEST(func);

	TEST_INFO(COLOR_GREEN, "DataStruct Test done");
}

