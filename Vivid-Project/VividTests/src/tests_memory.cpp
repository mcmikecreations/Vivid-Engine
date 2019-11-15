#include "catch.h"

#include "vivid_core/memory/memory_tracker.h"

class P
{
public:
	int _a, _b, _c;
	P(int a, int b, int c) : _a(a), _b(b), _c(c) {}
};

TEST_CASE("Memory tracker works", "[memory]") {
	SECTION("Check standard type creation") {
		vivid_core::memory::memory_tracker m;
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());

		int *myInt = nullptr;
		REQUIRE_NOTHROW((myInt = m.allocate<int>(5)) != 0);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myInt != nullptr);

		m.free(myInt);
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());
	}
	SECTION("Check custom class creation") {
		vivid_core::memory::memory_tracker m;
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());

		P *myP = nullptr;
		REQUIRE_NOTHROW((myP = m.allocate<P>(1,2,3)) != 0);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myP != nullptr);

		m.free(myP);
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());
	}
	SECTION("Check type array") {
		vivid_core::memory::memory_tracker m;
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());

		int *myIntArray = nullptr;
		REQUIRE_NOTHROW((myIntArray = m.allocate_array<int>(5)) != 0);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myIntArray != nullptr);

		m.free(myIntArray);
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());
	}
	SECTION("Check multiple creates") {
		vivid_core::memory::memory_tracker m;
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());

		int *myIntArray = nullptr;
		REQUIRE_NOTHROW((myIntArray = m.allocate_array<int>(5)) != 0);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myIntArray != nullptr);

		P *myP = nullptr;
		REQUIRE_NOTHROW((myP = m.allocate<P>(1, 2, 3)) != 0);
		REQUIRE(m.size() == 2);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myP != nullptr);

		m.free(myIntArray);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());

		m.free(myP);
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());
	}
	SECTION("Check error") {
		vivid_core::memory::memory_tracker m;
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());

		int *myIntArray = nullptr;
		REQUIRE_NOTHROW((myIntArray = m.allocate_array<int>(5)) != 0);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myIntArray != nullptr);

		P *myP = nullptr;
		REQUIRE_NOTHROW((myP = m.allocate<P>(1, 2, 3)) != 0);
		REQUIRE(m.size() == 2);
		REQUIRE_FALSE(m.empty());
		REQUIRE(myP != nullptr);

		REQUIRE(m.free<int>(nullptr) == (int)vivid_core::utility::errors::MEMORY_CORRUPT);
		REQUIRE(m.free(myIntArray + 1) == (int)vivid_core::utility::errors::OBJECT_NOT_FOUND);

		m.free(myIntArray);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());

		m.free(myP);
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());
	}
}