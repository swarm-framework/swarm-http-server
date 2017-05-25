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

#ifndef SWARM_HTTP_STANDARDERRORBUILDER_HXX
#define SWARM_HTTP_STANDARDERRORBUILDER_HXX

#include <memory>
#include <swarm/http/message/response/HTTPResponseStatus.hxx>

namespace swarm {
    namespace http {

        class HTTPResponse;
        
        /// \brief Class StandardErrorBuilder
        class StandardErrorBuilder {
            
        private:
            
            /// \brief Error status
            HTTPResponseStatus status_ = HTTPResponseStatus::NOT_FOUND;
            
        public:
            
            /// \brief Set status code
            /// \param status Error status
            /// \return Current builder
            StandardErrorBuilder & error(HTTPResponseStatus status);
            
            /// \brief Create error body response
            /// \return Smart pointer on body
            HTTPResponse build();
        };
    }
}

#endif // SWARM_HTTP_STANDARDERRORBUILDER_HXX
