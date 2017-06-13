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
#define SWARM_HTTP_HTTPSERVICEHANDLERBUILDER_HXX

#include <swarm/http/message/request/HTTPMethod.hxx>
#include <memory>
#include <functional>

namespace swarm {
    namespace http {

        struct HTTPService;
        
        /// \brief Class HTTPServiceHandlerBuilder
        template <typename Result, typename Body>
        class HTTPServiceHandlerBuilder {
            
            friend struct HTTPServiceBuilder;
            
        private:
            
            /// \brief Service method
            HTTPMethod method_;
            
            /// \brief Service pattern
            std::string pattern_;
            
        private:
            
            /// \brief Create servie builder with an HTTP method
            /// \param method HTTP method
            /// \param pattern Service path pattern
            HTTPServiceHandlerBuilder(HTTPMethod method, const std::string & pattern);
            
        public:
            
            /// \brief Create process handler using a lambda
            /// \param function Lambda used as process
            std::shared_ptr<HTTPService> handler(std::function<Result(const Body &)> function);
        };
        
        /// \brief Class HTTPServiceHandlerBuilder
        template <typename Result>
        class HTTPServiceHandlerBuilder<Result, void> {
            
            friend struct HTTPServiceBuilder;
            
        private:
            
            /// \brief Service method
            HTTPMethod method_;
            
            /// \brief Service pattern
            std::string pattern_;
            
        private:
            
            /// \brief Create servie builder with an HTTP method
            /// \param method HTTP method
            /// \param pattern Service path pattern
            HTTPServiceHandlerBuilder(HTTPMethod method, const std::string & pattern);
            
        public:
            
            /// \brief Create process handler using a lambda
            /// \param function Lambda used as process
            std::shared_ptr<HTTPService> handler(std::function<Result()> function);
        };
    }
}

#endif // SWARM_HTTP_HTTPSERVICEHANDLERBUILDER_HXX

#include "HTTPServiceHandlerBuilder.txx"
