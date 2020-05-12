#include <iostream>
#include <string>
#include "catch.h"

#include "ioc/di.h"
#include "patterns/raii.h"
#include "patterns/managed_singleton.h"

using namespace vul::ioc;
using namespace vul::patterns;

class Repo
{
public: virtual int get() = 0;
};

class const_repo : public Repo
{
public: virtual int get() override { return 5; }
};

class Logger
{
public: virtual std::string log() = 0;
};

class cout_logger : public Logger
{
    Repo* _repo;
public:
    cout_logger(Repo* repo) : _repo(repo) {}
    virtual std::string log() override { return std::to_string(_repo->get()); }
};

TEST_CASE("IoC Container runs", "[ioc]") {
    SECTION("constructing di") {
        di d;
        REQUIRE(d.init() == 1);
        REQUIRE(d.term() == 1);
    }
    SECTION("clearing di") {
        di d;
        REQUIRE(d.init() == 1);
        REQUIRE(d.clear() == 1);
        REQUIRE(d.term() == 1);
    }
    SECTION("scope verification") {
        di d;
        REQUIRE(d.add_transient<Repo, const_repo>() == 1);
        auto scope = d.get<Repo>();
        REQUIRE(scope != nullptr);
        REQUIRE(scope->is_scope() == true);
        REQUIRE(scope->di() == (void*)&d);
        REQUIRE(scope->get() != nullptr);
        REQUIRE(scope->ptr() != nullptr);
        REQUIRE((void*)scope->get() == scope->ptr());
        REQUIRE(scope->get()->get() == 5);
        //Other functions are unused for now
    }
    SECTION("transient ioc injection") {
        di d;
        REQUIRE(d.add_transient<Repo, const_repo>() == 1);
        {
            auto scope = d.get<Repo>();
            REQUIRE(scope != nullptr);
            auto value = scope->get();
            REQUIRE(value != nullptr);
            REQUIRE(value->get() == 5);
            REQUIRE(d.free(scope) == 1);
        }
        {
            auto scope = d.get<Logger>();
            REQUIRE(scope == nullptr);
        }
        {
            auto repo1 = d.get<Repo>()->get();
            auto repo2 = d.get<Repo>()->get();
            REQUIRE(repo1 != repo2);
            REQUIRE(d.free(repo1) == 1);
            REQUIRE(d.free(repo2) == 1);
        }
        REQUIRE(d.term() == 1);
    }
    SECTION("singleton ioc injection") {
        di d;
        REQUIRE(d.add_singleton<Repo, const_repo>() == 1);
        {
            auto scope = d.get<Repo>();
            REQUIRE(scope != nullptr);
            auto value = scope->get();
            REQUIRE(value != nullptr);
            REQUIRE(value->get() == 5);
            REQUIRE(d.free(scope) == 0);
        }
        {
            auto scope = d.get<Logger>();
            REQUIRE(scope == nullptr);
        }
        {
            auto repo1 = d.get<Repo>()->get();
            auto repo2 = d.get<Repo>()->get();
            REQUIRE(repo1 == repo2);
            REQUIRE(d.free(repo1) == 0);
            REQUIRE(d.free(repo2) == 0);
        }
        REQUIRE(d.term() == 1);
    }
    SECTION("immediate cleaning") {
        {
            di d;
            REQUIRE(d.add_transient<Repo, const_repo>() == 1);
            auto scope = d.get<Repo>();
            REQUIRE(scope != nullptr);
            REQUIRE(d.free(scope, true) == 1);
            REQUIRE(d.clear() == 1);
        }
        {
            di d;
            REQUIRE(d.add_transient<Repo, const_repo>() == 1);
            auto scope = d.get<Repo>();
            REQUIRE(scope != nullptr);
            REQUIRE(d.free(scope, false) == 1);
            REQUIRE(d.clear() == 1);
        }
    }
    SECTION("raii") {
        {
            di d;
            raii<di> r(std::move(d), raii_dummy{});
            REQUIRE(r->add_transient<Repo, const_repo>() == 1);
            auto scope = r->get<Repo>();
            REQUIRE(scope != nullptr);
            REQUIRE(scope->get() != nullptr);
            REQUIRE(scope->get()->get() == 5);
        }
    }
    SECTION("managed singleton") {
        {
            using t = managed_singleton<di>;
            t m;
            raii<t> r(std::move(m), raii_dummy{});
            REQUIRE(t::ptr()->add_transient<Repo, const_repo>() == 1);
            auto scope = t::ptr()->get<Repo>();
            REQUIRE(scope != nullptr);
            REQUIRE(scope->get() != nullptr);
            REQUIRE(scope->get()->get() == 5);
        }
    }
}