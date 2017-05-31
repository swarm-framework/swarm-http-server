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

#ifndef SWARM_HTTP_HTTPSERVER_HXX
#define SWARM_HTTP_HTTPSERVER_HXX

#include <memory>

namespace swarm {
    namespace http {

        struct HTTPServerDelegate;
        class HTTPRouter;
        struct HTTPSession;
        
        /// \brief Class HTTPServer
        class HTTPServer {
            
        private:
            
            /// \brief define listening port
            int port_;
            
            /// \brief define delegate to use
            std::shared_ptr<HTTPServerDelegate> delegate_;
            
            /// \brief HTTP router
            std::shared_ptr<HTTPRouter> router_;
            
        public:
            
            /// \brief Constructor with delegate ,port and router
            /// \param delegate Backend delegate
            /// \param port Listeining port
            /// \param router Endpoint router
            HTTPServer(std::shared_ptr<HTTPServerDelegate> delegate, int port, std::shared_ptr<HTTPRouter> router);
            
            /// \return server port
            int port() const {
                return port_;
            }
            
        private:
            
            /// \brief Send error
            /// \param message Message to display
            void sendError(std::shared_ptr<HTTPSession> session, const std::string & message);
            
        public:
            
            /// \brief Process requests
            void process();
        };
    }
}

#endif // SWARM_HTTP_HTTPSERVER_HXX
