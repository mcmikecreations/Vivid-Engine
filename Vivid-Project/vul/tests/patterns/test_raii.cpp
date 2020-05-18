#include "catch.h"

#include "patterns/raii.h"
#include "patterns/managed_singleton.h"

using namespace vul;
using namespace vul::patterns;

struct dummy
{
    int* value;
    int init()
    {
        value = new int;
        return (int)error::success;
    }
    int init(int val)
    {
        value = new int(val);
        return 1;
    }
    int term()
    {
        delete value;
        return (int)error::success;
    }
};

TEST_CASE("RAII runs", "[patterns][memory]") {
    SECTION("constructing raii") {
        raii<dummy> a(dummy{});
        REQUIRE(a.is_init() == error::failure);
    }
    SECTION("constructing raii with init") {
        raii<dummy> a(dummy{}, 5);
        REQUIRE(a.is_init() == error::success);
    }
    SECTION("constructing raii with parameter-less init") {
        raii<dummy> a(dummy{}, raii_dummy{});
        REQUIRE(a.is_init() == error::success);
    }
    SECTION("getting value from raii") {
        int i = 5;
        raii<dummy> a(dummy{});
        REQUIRE(a.init(i) == error::success);
        REQUIRE(*(a.get().value) == i);
        REQUIRE(*(a->value) == i);
        REQUIRE(a.term() == error::success);
    }
    SECTION("testing function returns") {
        int i = 5;
        raii<dummy> a(dummy{});
        REQUIRE(a.term() == error::failure);
        REQUIRE(a.init(i) == error::success);
        REQUIRE(a.init(i + 1) == error::failure);
        REQUIRE(a.term() == error::success);
        REQUIRE(a.term() == error::failure);
    }
}