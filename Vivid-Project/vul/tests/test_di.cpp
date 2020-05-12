#include "catch.h"

#include "ioc/di.h"

using namespace vul::ioc;

TEST_CASE("IoC Container runs", "[ioc]") {
    SECTION("constructing di") {
        di d;
        REQUIRE(d.init() == 1);
        REQUIRE(d.term() == 1);
    }
}