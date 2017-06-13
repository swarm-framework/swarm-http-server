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

#ifndef SWARM_HTTP_HTTPSERVICEPROCESSWRAPPER_HXX
#define SWARM_HTTP_HTTPSERVICEPROCESSWRAPPER_HXX

#include "HTTPService.hxx"
#include <swarm/http/message/request/HTTPMethod.hxx>

namespace swarm {
    namespace http {

        class HTTPServiceWrapper : public HTTPService {
            
        private:
            
            /// \brief HTTP method
            HTTPMethod method_;
            
            /// \brief Service pattern
            std::string pattern_;
            
            
        public:
            
            HTTPServiceWrapper(HTTPMethod method, const std::string & pattern) : method_(method), pattern_(pattern) {
                
            }
            
        public:
            
            /// \return Service HTTP method
            virtual const HTTPMethod & method() const override {
                return method_;
            }
            
            /// \return Service HTTP method
            virtual const std::string & pattern() const override {
                return pattern_;
            }
        };
        
        /// \brief Class HTTPServiceProcessWrapper
        template<typename Result, typename Body>
        class HTTPServiceProcessWrapper : public HTTPServiceWrapper {
            
        private:
            std::function<Result(const Body &)> function_;
            
        public:
            
            HTTPServiceProcessWrapper(HTTPMethod method, const std::string & pattern, std::function<Result(const Body &)> function) : HTTPServiceWrapper(method, pattern), function_(function) {
                
            }
            
        public:
            
            
            /// \brief Process
            /// A process is a treatment which process an HTTPContext containing the HTTP request and  return an
            /// HTTPResponse
            /// \param context HTTP context containing request information
            /// \return an HTTP response
            virtual HTTPResponse process(HTTPContext &context) override;
        };
    }
}

#endif // SWARM_HTTP_HTTPSERVICEPROCESSWRAPPER_HXX

#include "HTTPServiceProcessWrapper.txx"
