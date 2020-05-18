#include "catch.h"

#include "helpers/trick_has_mfunction.h"

struct Hello
{
    int helloworld() { return 0; }
};

struct Generic {};

DECL_HAS_MEMBER_FUNCTION(helloworld)

using namespace vul;
using namespace vul::helpers;

TEST_CASE("Function member check runs", "[tricks]") {
    SECTION("Check for helloworld") {
        REQUIRE((int)has_helloworld<Hello>::value == 1);
        REQUIRE((int)has_helloworld<Generic>::value == 0);
    }
}