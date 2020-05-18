#include "catch.h"

#include "patterns/managed_singleton.h"

using namespace vul;
using namespace vul::patterns;

TEST_CASE("Singleton runs", "[patterns][memory]") {
    SECTION("constructing singleton") {
        managed_singleton<std::byte> a;
    }
    SECTION("getting value from singleton") {
        managed_singleton<int> a;
        int i = 5;
        REQUIRE(a.init(i) == error::success);
        REQUIRE(managed_singleton<int>::get() == i);
        REQUIRE(a.term() == error::success);
    }
    SECTION("testing function returns") {
        managed_singleton<std::uint16_t> a;
        std::uint16_t i(6);
        REQUIRE(a.term() == error::failure);
        REQUIRE(a.init(i) == error::success);
        REQUIRE(managed_singleton<std::uint16_t>::get() == i);
        REQUIRE(a.init(i + 1) == error::failure);
        REQUIRE(managed_singleton<std::uint16_t>::get() == i);
        REQUIRE(managed_singleton<std::uint16_t>::ptr()
            == managed_singleton<std::uint16_t>::ptr());
        REQUIRE(a.term() == error::success);
    }
}