/*
 * Copyright 2017 Dami <contact@damiengiron.me>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <catch/catch.hxx>

#include "swarm/http/service/HTTPServiceBuilder.hxx"
#include "swarm/http/router/HTTPRouterBuilder.hxx"

using namespace swarm::http;

namespace test {

    struct BodyOne {};
}

TEST_CASE("HTTP Service builder", "[service], [router]") {

    HTTPRouterBuilder routerBuilder{};
    HTTPServiceBuilder builder{};

    // Create treatment allways returning ok
    auto service = builder.service<void>(HTTPMethod::GET, "/ws/treatment").handler([]() {

    });
    // Register service
    routerBuilder.add(service);
    
    // Create treatment always returning ok and reading an object Body1 as HTTP body
    service = builder.service<void, test::BodyOne>(HTTPMethod::POST, "/ws/treatment").handler([](const test::BodyOne & body) {
        
    });
    
    // Register service
    routerBuilder.add(service);
    
    // Create service return object BodyOne
    service = builder.service<test::BodyOne>(HTTPMethod::GET, "/ws/BodyOne").handler([]() {
        return test::BodyOne{};
    });
    
    // Register service
    routerBuilder.add(service);
    
    // Create service reading a BodyOne and returning it
    service = builder.service<test::BodyOne, test::BodyOne>(HTTPMethod::POST, "/ws/BodyOne").handler([](const test::BodyOne & body) {
        return body;
    });
    
    // Register service
    routerBuilder.add(service);
}

