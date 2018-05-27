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
#include <String/Json.hpp>

#include "TestCommon.hpp"

static void StringInit(void)
{
	TEST_STEP(1, 1, "Initialize empty string",
			  "An empty string has size 0, offset 0.") {
		CConstStringPtr test;
		CHECK(0 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
	}

	TEST_STEP(1, 2, "Initialize string with DEC",
			  "The number should be converted to string") {
		CConstStringPtr test(DEC(-100));
		CHECK(4 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
		CHECK(test == "-100", "String: %s", test->ToCStr());
	}

	TEST_STEP(1, 3, "Initialize string with HEX",
			  "The number should be converted to string") {
		CConstStringPtr test(HEX(-100));
		CHECK(8 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
		CHECK(test == "FFFFFF9C", "String: %s", test->ToCStr());
	}

	TEST_STEP(1, 4, "Initialize string with CHAR",
			  "The char should be converted to string") {
		CConstStringPtr test(CHAR('c'));
		CHECK(1 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
		CHECK(test == "c", "String: %s", test->ToCStr());
	}

	TEST_STEP(1, 5, "Initialize string with multiple string",
			  "The multiple string should be combined into one string") {
		CConstStringPtr a("a1234");
		CConstStringPtr b("b6789");
		CConstStringPtr c("c0987");
		CConstStringPtr d("d5432");
		CConstStringPtr test(a, b, c, d);
		CHECK(20 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
		CHECK(test == "a1234b6789c0987d5432", "String: %s", test->ToCStr());
	}
}

static void StringSplit(void)
{
	TEST_STEP(2, 1, "Key > Source",
			  "Should find only 1 split") {
		CConstStringPtr key("abcdefg");
		CConstStringPtr fsrc("12345abcdef54321");
		CConstStringPtr src(fsrc->Slice(5, 11));

		src->Split(key)->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == src, "str is: %s", str->ToCStr());
		});
	}

	TEST_STEP(2, 2, "Split by char",
			  "Should find all splits") {
		CConstStringPtr ftest("12/45/aaa/bbb//ccc/ddd/54/21");
		CConstStringPtr test(ftest->Slice(5, 23));
		const char *ref[] = {
			"",
			"aaa",
			"bbb",
			"",
			"ccc",
			"ddd",
			"",
		};

		uint32_t i = 0;
		test->Split("/")->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 3, "Reverse split by char",
			  "Should find all splits") {
		CConstStringPtr ftest("12/45/aaa/bbb//ccc/ddd/54/21");
		CConstStringPtr test(ftest->Slice(5, 23));
		const char *ref[] = {
			"",
			"ddd",
			"ccc",
			"",
			"bbb",
			"aaa",
			"",
		};

		uint32_t i = 0;
		test->Split("/")->Reverse()->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 4, "Split by token",
			  "Should find all splits") {
		CConstStringPtr ftest("12 45 aaa	bbb  \r\n ccc ddd  54 21");
		CConstStringPtr test(ftest->Slice(5, 27));
		const char *ref[] = {
			"aaa",
			"bbb",
			"ccc",
			"ddd",
		};

		uint32_t i = 0;
		test->SplitByToken()->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 5, "Reverse split by token",
			  "Should find all splits") {
		CConstStringPtr ftest("12 45 aaa	bbb  \r\n ccc ddd  54 21");
		CConstStringPtr test(ftest->Slice(5, 27));
		const char *ref[] = {
			"ddd",
			"ccc",
			"bbb",
			"aaa",
		};

		uint32_t i = 0;
		test->SplitByToken()->Reverse()->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 6, "Split by line",
			  "Should find all splits") {
		CConstStringPtr ftest("12\n45aaa\r\nbbb\r\rccc\n\rddd\n54\n21");
		CConstStringPtr test(ftest->Slice(5, 24));
		const char *ref[] = {
			"aaa",
			"bbb\r\rccc",
			"ddd",
			"",
		};

		uint32_t i = 0;
		test->SplitByLine()->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 7, "Reverse split by line",
			  "Should find all splits") {
		CConstStringPtr ftest("12\n45aaa\r\nbbb\r\rccc\n\rddd\n54\n21");
		CConstStringPtr test(ftest->Slice(5, 24));
		const char *ref[] = {
			"",
			"ddd",
			"bbb\r\rccc",
			"aaa",
		};

		uint32_t i = 0;
		test->SplitByLine()->Reverse()->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 8, "Split by string",
			  "Should find all splits") {
		CConstStringPtr ftest("1is45This is a string, string is a test5is21");
		CConstStringPtr test(ftest->Slice(5, 39));
		const char *ref[] = {
			"Th",
			" ",
			" a string, string ",
			" a test",
		};

		uint32_t i = 0;
		test->Split("is")->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}

	TEST_STEP(2, 9, "Reverse split by string",
			  "Should find all splits") {
		CConstStringPtr ftest("1is45This is a string, string is a test5is21");
		CConstStringPtr test(ftest->Slice(5, 39));
		const char *ref[] = {
			" a test",
			" a string, string ",
			" ",
			"Th",
		};

		uint32_t i = 0;
		test->Split("is")->Reverse()->ForEach([&](const CConstStringPtr &str) {
			CHECK(str == ref[i], "Fail at %d, str: %s, ref: %s",
							i, str->ToCStr(), ref[i]);
			++i;
		});

		CHECK(i == ARRAY_SIZE(ref),
				   "Not all reference are found: i: %d, sizeof(ref): %d",
				   i, ARRAY_SIZE(ref));
	}
}

static void StringFunc(void)
{
	TEST_STEP(3, 1, "Sprintf", "Should work") {
		CStringPtr test;
		test->Sprintf("Test: %d", 100);
		CHECK(9 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
		CHECK(test == "Test: 100", "String: >>> %s <<<", test->ToCStr());
	}

	TEST_STEP(3, 2, "Reverse", "Should work") {
		CConstStringPtr ftest("12345Test54321");
		CConstStringPtr test(ftest->Slice(5, 9));
		test = test->Reverse();
		CHECK(4 == test->GetSize(), "Size is: %d", test->GetSize());
		CHECK(0 == test->GetOffset(), "Offset is: %d", test->GetOffset());
		CHECK(test == "tseT", "String: >>> %s <<<", test->ToCStr());
	}

	TEST_STEP(3, 3, "Strip", "Should work") {
		CConstStringPtr ftest("12345  0xa  bbb  ccc  ddd  eee  fff  54321");
		CConstStringPtr test(ftest->Slice(5, 37));

		CConstStringPtr t1(test->Strip());
		CHECK(t1 == "0xa  bbb  ccc  ddd  eee  fff",
				   "Strip to: >>> %s <<<", t1->ToCStr());

		CConstStringPtr t2(test->LStrip());
		CHECK(t2 == "0xa  bbb  ccc  ddd  eee  fff  ",
				   "Strip to: >>> %s <<<", t2->ToCStr());

		CConstStringPtr t3(test->RStrip());
		CHECK(t3 == "  0xa  bbb  ccc  ddd  eee  fff",
				   "Strip to: >>> %s <<<", t3->ToCStr());
	}

	TEST_STEP(3, 4, "Find", "Should work") {
		CConstStringPtr ftest("12ccc  ddd45  0xa  bbb  ccc  ddd  eee  fff  54ccc  ddd21");
		CConstStringPtr test(ftest->Slice(12, 45));

		int i = test->Find("ccc  ddd");
		CHECK(12 == i, "Find at: %d", i);

		i = test->Find(" ", CString::REVERSE);
		CHECK(31 == i, "Find at: %d", i);
	}

	TEST_STEP(3, 5, "FindToken", "Should work") {
		CConstStringPtr ftest("12 450xa  bbb  ccc  ddd  eee  fff  54 21");
		CConstStringPtr test(ftest->Slice(5, 35));

		int i = test->FindToken();
		CHECK(i == 3, "Find token at : %d", i);
	}
}

static void Json(void)
{
/* Demo Json:
{
	"test1": 33,
	"test2": "tt",
	"group":
	{
		"test3": 3,
		"array": [1, 2, 3, 4, 5, 6]
	}
}*/
	CConstStringPtr demo("{\"test1\": \r\n33,\r\n	\"test2\"	: \"tt\",\r\n"
						 "\"group\":{ \"test3\"	:3,\"array\":\n\r"
						 "[1,2,3,4,5,6]	\n}\n}");

	TEST_STEP(4, 1, "Json to string", "Should work") {
		CJsonPtr arr("array");
		arr->AddChild(nullptr, "1", CJson::ARRAY)
			->AddChild(nullptr, "2", CJson::ARRAY)
			->AddChild(nullptr, "3", CJson::ARRAY)
			->AddChild(nullptr, "4", CJson::ARRAY)
			->AddChild(nullptr, "5", CJson::ARRAY)
			->AddChild(nullptr, "6", CJson::ARRAY);

		CJsonPtr root;
		root->AddChild("test1", "1")
			->AddChild("test2", "2")
			->AddChild("test3", "3")
			->AddChild(arr)
			->AddChild("test4", "4");

		auto jsonstr(root->ToString());
		CHECK(jsonstr == "{\"test1\":1,\"test2\":2,\"test3\":3,\"array\":[1,2,3,4,5,6],\"test4\":4}",
				   "Json: %s", jsonstr->ToCStr());
	}

	TEST_STEP(4, 2, "String to json", "Should work") {
		CRecord record;
		auto json(demo->ToJson());
		CHECK(json, "json is null");

		json->GetChildren()->First([&](const CJsonPtr &json) {
			/* Check 1st child: "test1":33 */
			CHECK(json, "1st child is null");

			json->GetKey([&](const CConstStringPtr &key) {
				record.Save(0);
				CHECK(key == "test1", "key: %s", key->ToCStr());
			})->GetVal([&](const CConstStringPtr &val) {
				record.Save(1);
				CHECK(val == "33", "val: %s", val->ToCStr());
			})->GetType([&](CJson::Type type) {
				record.Save(2);
				CHECK(type == CJson::OBJECT, "type: %d", type);
			});

		})->Next([&](const CJsonPtr &json) {
			/* Check 2nd child: "test2":"tt" */
			CHECK(json, "2nd child is null");

			record.Save(3);

			CHECK(json->GetKey() == "test2", "key: %s",
							json->GetKey()->ToCStr());
			CHECK(json->GetVal() == "tt", "val: %s",
							json->GetVal()->ToCStr());
			CHECK(json->GetType() == CJson::OBJECT, "type: %d",
							json->GetType());

		})->Next([&](const CJsonPtr &json) {
			/* Check 3rd child: "group: {}"*/
			json->GetKey([&](const CConstStringPtr &key) {
				record.Save(4);
				CHECK(key == "group", "key: %s", key->ToCStr());
			})->GetVal([&](const CConstStringPtr &val) {
				record.Save(5);
				CHECK(!val, "val is not null");
			})->GetType([&](CJson::Type type) {
				record.Save(6);
				CHECK(type == CJson::OBJECT, "type: %d", type);
			});

			json->GetChildren()->First([&](const CJsonPtr &json) {
				/* Check 1st grandchild: "test3": 3 */
				json->GetKey([&](const CConstStringPtr &key) {
					record.Save(7);
					CHECK(key == "test3", "key: %s", key->ToCStr());
				})->GetVal([&](const CConstStringPtr &val) {
					record.Save(8);
					CHECK(val == "3", "val: %s", val->ToCStr());
				})->GetType([&](CJson::Type type) {
					record.Save(9);
					CHECK(type == CJson::OBJECT, "type: %d", type);
				});
			})->Next([&](const CJsonPtr &json) {
				/* Check 2nd grandchild: "array": [] */
				json->GetKey([&](const CConstStringPtr &key) {
					record.Save(10);
					CHECK(key == "array", "key: %s", key->ToCStr());
				})->GetVal([&](const CConstStringPtr &val) {
					record.Save(11);
					CHECK(!val, "val is not null");
				})->GetType([&](CJson::Type type) {
					record.Save(12);
					CHECK(type == CJson::OBJECT, "type: %d", type);
				});

				int idx = 3;
				json->GetChildren()->ForEach([&](const CJsonPtr &json) {
					json->GetVal([&](const CConstStringPtr &val) {
						CHECK(val == DEC(idx / 3), "val: %s", val->ToCStr());
						++idx;
					})->GetKey([&](const CConstStringPtr &key) {
						CHECK(!key, "key is not null");
						++idx;
					})->GetType([&](CJson::Type type) {
						CHECK(type == CJson::ARRAY, "type: %d", type);
						++idx;
					});
				});

				CHECK(idx == 21, "Invalid children number: %d", idx);
			})->Next([&](const CJsonPtr &) {
				/* No more other child */
				CHECK(false, "Unknown child");
			});

		})->Next([&](const CJsonPtr &) {
			/* No more other child */
			CHECK(false, "Unknown child");
		});

		record.Check();
	}

	TEST_STEP(4, 3, "Find in Json", "Should work") {
		CRecord record;
		auto json(demo->ToJson());
		CHECK(json, "json is null");
		auto iter(json->GetChildren());
		CHECK(iter, "iter is null");

		CHECK(iter->Find("test1"), "Cannot find key: test1");
		CHECK(iter->Find("tt", CJson::Iterator::VAL), "Cannot find val: tt");
		CHECK(!iter->Find("tt"), "Find key: tt");
		CHECK(!iter->Find("test1", CJson::Iterator::VAL), "Find val: test1");

		iter->Find("test2", [&](const CJsonPtr &json) {
			record.Save(0);

			auto key(json->GetKey());
			CHECK(key, "key is null");
			CHECK(key == "test2", "key is: %s", key->ToCStr());

			auto val(json->GetVal());
			CHECK(val, "val is null");
			CHECK(val == "tt", "val is: %s", val->ToCStr());
		});

		record.Check();
	}

	TEST_STEP(4, 4, "Erase in Json", "Should work") {
		auto json(demo->ToJson());
		CHECK(json, "json is null");
		auto iter(json->GetChildren());
		CHECK(iter, "iter is null");

		CHECK(iter->Find("test2"), "Cannot find key: test2");
		iter->Erase();
		CHECK(!iter->Find("test2"), "Test2 is not erased");
	}

	TEST_STEP(4, 5, "Insert in Json", "Should work") {
		auto json(demo->ToJson());
		CHECK(json, "json is null");
		auto iter(json->GetChildren());
		CHECK(iter, "iter is null");
		const char *out = "{\"test1\":33,\"insert\":\"abc\",\"test2\":\"tt\"}";

		iter->Erase("group");
		CHECK(iter->Find("test2"), "Cannot find key: test2");
		iter->Insert(CJsonPtr("insert", "abc"));
		CHECK(json->ToString() == out, "Insert fail: %s",
			  json->ToString()->ToCStr());
	}

	TEST_STEP(4, 6, "Sort in Json", "Should work") {
		CConstStringPtr str("{"
							"\"aest\":1,"
							"\"tbst\":7,"
							"\"tect\":3,"
							"\"tesd\":4,"
							"\"teet\":8,"
							"\"fest\":5"
							"}");
		CConstStringPtr strSortByKey("{"
									 "\"aest\":1,"
									 "\"fest\":5,"
									 "\"tbst\":7,"
									 "\"tect\":3,"
									 "\"teet\":8,"
									 "\"tesd\":4"
									 "}");
		CConstStringPtr strSortByVal("{"
									 "\"aest\":1,"
									 "\"tect\":3,"
									 "\"tesd\":4,"
									 "\"fest\":5,"
									 "\"tbst\":7,"
									 "\"teet\":8"
									 "}");
		auto json(str->ToJson());
		CHECK(json, "json is null");
		auto iter(json->GetChildren());
		CHECK(iter, "iter is null");

		iter->Sort(CJson::Iterator::KEY);
		CHECK(json->ToString() == strSortByKey,
			  "After sort by key: %s",
			  json->ToString()->ToCStr());

		iter->Sort(CJson::Iterator::VAL);
		CHECK(json->ToString() == strSortByVal,
			  "After sort by val: %s",
			  json->ToString()->ToCStr());
	}
}

void StringTest(void)
{
	DO_TEST(StringInit);
	DO_TEST(StringSplit);
	DO_TEST(StringFunc);
	DO_TEST(Json);

	TEST_INFO(COLOR_GREEN, "============== String Test done ==============");
}

