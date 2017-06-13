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

#ifndef SWARM_HTTP_HTTPSERVICEBUILDER_HXX
#include "HTTPServiceBuilder.hxx"
#endif

namespace swarm {
    namespace http {
        
        // Create a service handler builder
        template<class Result>
        HTTPServiceHandlerBuilder<Result, void> HTTPServiceBuilder::service(HTTPMethod method, const std::string & pattern) {
            return HTTPServiceHandlerBuilder<Result, void>{method, pattern};
        }
        
        // Create a service handler builder
        template<class Result, class Body>
        HTTPServiceHandlerBuilder<Result, Body> HTTPServiceBuilder::service(HTTPMethod method, const std::string & pattern) {
            return HTTPServiceHandlerBuilder<Result, Body>{method, pattern};
        }
    }
}
