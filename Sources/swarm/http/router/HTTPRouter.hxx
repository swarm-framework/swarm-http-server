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

#ifndef SWARM_HTTP_HTTPROUTER_HXX
#define SWARM_HTTP_HTTPROUTER_HXX

#include <memory>
#include <string>
#include <vector>

#include "HTTPRouterChoice.hxx"
#include <cxx-log/Logger.hxx>

namespace swarm {
    namespace http {

        struct HTTPProcess;
        class HTTPContext;
        class HTTPRouterEntry;

        /// \brief Class HTTPRouter
        class HTTPRouter {

            friend class HTTPRouterBuilder;

        private:

            /// \brief internal logger
            static cxxlog::Logger logger_;

            /// /brief Define root entry
            std::shared_ptr<HTTPRouterEntry> rootEntry_;

          private:
            /// \brief COnstructor with root entry
            /// \param rootEntry Initial entry
            HTTPRouter(std::shared_ptr<HTTPRouterEntry> rootEntry) : rootEntry_(rootEntry) {}

            /// \brief Find all choices for a path using an entry
            /// \param choices All choices
            /// \param choice Current choice
            /// \param it Current string iterator
            /// \param end End iterator
            void find(std::vector<std::shared_ptr<HTTPRouterChoice>> & choices,
                      std::shared_ptr<HTTPRouterChoice> choice,
                      std::string::const_iterator it,
                      std::string::const_iterator end);

          public:
            /// \brief Find HTTP process using context
            /// \param context HTTP context used to retrieve request and security info
            /// \return Process or invalid pointer
            std::shared_ptr<HTTPProcess> find(HTTPContext &context);
        };
    }
}

#endif // SWARM_HTTP_HTTPROUTER_HXX
