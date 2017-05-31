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

#ifndef SWARM_HTTP_HTTPROUTERBUILDER_HXX
#define SWARM_HTTP_HTTPROUTERBUILDER_HXX

#include <memory>
#include <map>
#include <swarm/http/message/request/HTTPMethod.hxx>

namespace swarm {
    namespace http {

        class HTTPRouter;
        struct HTTPProcess;

        /// \brief Class HTTPRouterBuilder
        class HTTPRouterBuilder {

          private:

            /// \brief Map containing all process by patterns
            std::map<std::string, std::shared_ptr<HTTPProcess>> patterns_;
            
          public:
            /// \brief Register an HTTP process for an URL pattern and method
            /// \param method HTTP method
            /// \param pattern URL pattern
            /// \param process HTTP process
            /// \return Current builder
            HTTPRouterBuilder &add(const HTTPMethod & method, const std::string &pattern, std::shared_ptr<HTTPProcess> process);

          public:
            /// \brief Create router
            /// \return Builder or invlaid pointer
            std::shared_ptr<HTTPRouter> build();
        };
    }
}

#endif // SWARM_HTTP_HTTPROUTERBUILDER_HXX
