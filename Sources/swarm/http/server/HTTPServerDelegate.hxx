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

#ifndef SWARM_HTTP_HTTPSERVERDELEGATE_HXX
#define SWARM_HTTP_HTTPSERVERDELEGATE_HXX

#include <memory>

namespace swarm {
    namespace http {

        class HTTPServer;
        struct HTTPSession;
        class HTTPResponse;

        /// \brief Server delegate for real implementation
        struct HTTPServerDelegate {

            /// \brief Init and start the HTTP server
            /// \param server Server containing informations
            virtual void init(HTTPServer &server) = 0;

            /// \brief Stop the server
            /// \param server HTTP server
            virtual void stop(HTTPServer &server) = 0;

            /// \brief Listen a connection
            /// \param server Server object
            virtual std::shared_ptr<HTTPSession> listening(HTTPServer &server) = 0;

            /// \brief Send response
            /// \param server Server object
            /// \param session Session previously accepted
            /// \param response Response to send
            virtual void send(HTTPServer &server, std::shared_ptr<HTTPSession> session, HTTPResponse &response) = 0;

            // Virtual destructor for sub classing
            virtual ~HTTPServerDelegate() {}
        };
    }
}

#endif // SWARM_HTTP_HTTPSERVERDELEGATE_HXX
