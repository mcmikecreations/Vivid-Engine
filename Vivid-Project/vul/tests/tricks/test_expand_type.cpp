#include "catch.h"

#include "helpers/trick_expand_type.h"
#include <tuple>

using namespace vul;
using namespace vul::helpers;

TEST_CASE("Expand type runs", "[tricks]") {
    SECTION("Expand first") {
        REQUIRE(typeid(first_type<int, char, bool>::type) == typeid(int));
    }
    SECTION("Expand nth") {
        using nth = nth_type<int, char, bool>;
        REQUIRE(typeid(nth::type<0>) == typeid(int));
        REQUIRE(typeid(nth::type<1>) == typeid(char));
        REQUIRE(typeid(nth::type<2>) == typeid(bool));
    }
}