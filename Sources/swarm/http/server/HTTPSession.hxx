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

#ifndef SWARM_HTTP_HTTPSESSION_HXX
#define SWARM_HTTP_HTTPSESSION_HXX

#include <swarm/http/message/request/HTTPRequest.hxx>

namespace swarm {
    namespace http {

        /// \brief Class defining an HTTP session.
        /// Subclassed by the server implemntation
        struct HTTPSession {
            
            /// \return Retrieve session request
            virtual HTTPRequest & request() = 0;
            
            // Virtual destructor for sub classing
            virtual ~HTTPSession() {}
        };
    }
}

#endif // SWARM_HTTP_HTTPSESSION_HXX
