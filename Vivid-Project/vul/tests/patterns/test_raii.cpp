#include "catch.h"

#include "patterns/raii.h"
#include "patterns/managed_singleton.h"

using namespace vul::patterns;

struct dummy
{
    int* value;
    int init()
    {
        value = new int;
        return 1;
    }
    int init(int val)
    {
        value = new int(val);
        return 1;
    }
    int term()
    {
        delete value;
        return 1;
    }
};

TEST_CASE("RAII runs", "[patterns][memory]") {
    SECTION("constructing raii") {
        raii<dummy> a(dummy{});
        REQUIRE(a.is_init() == 0);
    }
    SECTION("constructing raii with init") {
        raii<dummy> a(dummy{}, 5);
        REQUIRE(a.is_init() == 1);
    }
    SECTION("constructing raii with parameter-less init") {
        raii<dummy> a(dummy{}, raii_dummy{});
        REQUIRE(a.is_init() == 1);
    }
    SECTION("getting value from raii") {
        int i = 5;
        raii<dummy> a(dummy{});
        REQUIRE(a.init(i) == 1);
        REQUIRE(*(a.get().value) == i);
        REQUIRE(*(a->value) == i);
        REQUIRE(a.term() == 1);
    }
    SECTION("testing function returns") {
        int i = 5;
        raii<dummy> a(dummy{});
        REQUIRE(a.term() == 0);
        REQUIRE(a.init(i) == 1);
        REQUIRE(a.init(i + 1) == 0);
        REQUIRE(a.term() == 1);
        REQUIRE(a.term() == 0);
    }
}