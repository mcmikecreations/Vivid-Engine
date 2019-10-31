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
		VividCore::Memory::memory_tracker m;
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
		VividCore::Memory::memory_tracker m;
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
		VividCore::Memory::memory_tracker m;
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
		VividCore::Memory::memory_tracker m;
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
		VividCore::Memory::memory_tracker m;
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

		REQUIRE(m.free<int>(nullptr) == (int)VividCore::Utility::Errors::MEMORY_CORRUPT);
		REQUIRE(m.free(myIntArray + 1) == (int)VividCore::Utility::Errors::OBJECT_NOT_FOUND);

		m.free(myIntArray);
		REQUIRE(m.size() == 1);
		REQUIRE_FALSE(m.empty());

		m.free(myP);
		REQUIRE(m.size() == 0);
		REQUIRE(m.empty());
	}
}