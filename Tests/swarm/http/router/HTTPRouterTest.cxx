//
// Created by Dami on 28/05/2017.
//

#include <catch/catch.hxx>

#include "swarm/http/router/HTTPRouter.hxx"
#include "swarm/http/router/HTTPRouterBuilder.hxx"
#include "swarm/http/process/HTTPProcess.hxx"
#include "swarm/http/process/HTTPContext.hxx"
#include <swarm/http/message/request/HTTPRequestBuilder.hxx>
#include <swarm/http/message/response/HTTPResponseBuilder.hxx>

using namespace swarm::http;

namespace swarm::http::test {
    struct NamedHTTPProcess : public HTTPProcess {
        std::string path_;
        NamedHTTPProcess(std::string path) : path_(path) {

        }
        virtual HTTPResponse process(HTTPContext &context) {
            return HTTPResponseBuilder{}.build();
        }
    };

    void test_router(HTTPRouter& router, const std::string & path, const std::string & result) {


        // Create request
        auto request = HTTPRequestBuilder{}.path(path).build();

        // Create context
        HTTPContext context{*request};

        // Find process
        auto process = router.find(context);
        REQUIRE(process);

        REQUIRE(reinterpret_cast<test::NamedHTTPProcess*>(process.get())->path_ == result);
    }
}

TEST_CASE("HTTP router", "[router]") {

    HTTPRouterBuilder buider{};

    buider.add(HTTPMethod::GET, "/ws/v1/test1", std::make_shared<test::NamedHTTPProcess>("test1"));
    buider.add(HTTPMethod::GET, "/ws/v1/test2", std::make_shared<test::NamedHTTPProcess>("test2"));
    buider.add(HTTPMethod::GET, "/ws/v1/test*", std::make_shared<test::NamedHTTPProcess>("test*"));
    buider.add(HTTPMethod::GET, "/ws/v1/test*/test", std::make_shared<test::NamedHTTPProcess>("test*/test"));

    auto router = buider.build();

    test::test_router(*router, "/ws/v1/test1", "test1");
    test::test_router(*router, "/ws/v1/test2", "test2");
    test::test_router(*router, "/ws/v1/test3", "test*");
    test::test_router(*router, "/ws/v1/test*", "test*");
    test::test_router(*router, "/ws/v1/test", "test*");
    test::test_router(*router, "/ws/v1/test3/test", "test*/test");
    test::test_router(*router, "/ws/v1/test33", "test*");
    test::test_router(*router, "/ws/v1/test/test", "test*/test");
    test::test_router(*router, "/ws/v1/test44/test", "test*/test");
}

TEST_CASE("HTTP complex results", "[router]") {

    HTTPRouterBuilder buider{};

    buider.add(HTTPMethod::GET, "/a*b*", std::make_shared<test::NamedHTTPProcess>("b"));
    buider.add(HTTPMethod::GET, "/a*c*", std::make_shared<test::NamedHTTPProcess>("c"));
    buider.add(HTTPMethod::GET, "/a*d*", std::make_shared<test::NamedHTTPProcess>("d"));

    auto router = buider.build();

    test::test_router(*router, "/aabb", "b");
    test::test_router(*router, "/aabcb", "b");
    test::test_router(*router, "/aacbb", "c");
    test::test_router(*router, "/aadcbb", "d");
}
