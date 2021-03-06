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

#ifndef SWARM_HTTP_HTTPCONTEXT_HXX
#define SWARM_HTTP_HTTPCONTEXT_HXX

#include <memory>

namespace swarm {
    namespace http {

        class HTTPRequest;
        
        /// \brief HTTP context containing all informations access for HTTP process
        class HTTPContext {
            
        private:
            
            /// \brief HTTP request
            HTTPRequest & request_;
            
        public:
            
            /// \brief Constructor
            /// \param request HTTP request
            HTTPContext(HTTPRequest & request);
            
        public:
            
            /// \return HTTP request
            HTTPRequest & request() {
                return request_;
            }
        };
    }
}

#endif // SWARM_HTTP_HTTPCONTEXT_HXX
