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

#ifndef SWARM_HTTP_HTTPSERVICEHANDLERBUILDER_HXX
#include "HTTPServiceHandlerBuilder.hxx"
#endif

#include "HTTPService.hxx"
#include "HTTPServiceProcessWrapper.hxx"

#include <memory>

namespace swarm {
    namespace http {
        
        // --- Result -> Body ---
        
        // Create servie builder with an HTTP method
        template <typename Result, typename Body>
        HTTPServiceHandlerBuilder<Result, Body>::HTTPServiceHandlerBuilder(HTTPMethod method, const std::string & pattern) : method_(method), pattern_(pattern) {
            
        }
        
        // Create process handler using a lambda
        template <typename Result, typename Body>
        std::shared_ptr<HTTPService> HTTPServiceHandlerBuilder<Result, Body>::handler(std::function<Result(const Body &)> function) {
            return  std::shared_ptr<HTTPService>{
                new HTTPServiceProcessWrapper<Result,Body>{method_, pattern_, function}
            }; 
        }
        
        // --- Result -> nobody ---
        
        // Create servie builder with an HTTP method
        template <typename Result>
        HTTPServiceHandlerBuilder<Result, void>::HTTPServiceHandlerBuilder(HTTPMethod method, const std::string & pattern) : method_(method), pattern_(pattern) {
            
        }
        
        // Create process handler using a lambda
        template <typename Result>
        std::shared_ptr<HTTPService> HTTPServiceHandlerBuilder<Result, void>::handler(std::function<Result()> function) {
            return  std::shared_ptr<HTTPService>{
                new HTTPServiceProcessWrapper<Result,void>{method_, pattern_, function}
            }; 
        }
    }
}
