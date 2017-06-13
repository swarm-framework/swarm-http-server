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
#include "HTTPServiceProcessWrapper.hxx"
#endif

#include <swarm/http/message/response/HTTPResponseBuilder.hxx>
#include <swarm/mapping/provider/json/JSonEncoder.hxx>

namespace swarm {
    namespace http {
        
        
        // Process
        template<typename Result, typename Body>
        HTTPResponse HTTPServiceProcessWrapper<Result,Body>::process(HTTPContext &context) {
            // FXIME Implement me
            throw "plop";
        }
        
        /// \brief Class HTTPServiceProcessWrapper
        template<typename Result>
        class HTTPServiceProcessWrapper<Result, void> : public HTTPServiceWrapper {
            
        private:
            std::function<Result()> function_;
            
        public:
            
            HTTPServiceProcessWrapper(HTTPMethod method, const std::string & pattern, std::function<Result()> function) : HTTPServiceWrapper(method, pattern), function_(function) {
                
            }
            
        public:
            
            
            /// \brief Process
            /// A process is a treatment which process an HTTPContext containing the HTTP request and  return an
            /// HTTPResponse
            /// \param context HTTP context containing request information
            /// \return an HTTP response
            virtual HTTPResponse process(HTTPContext &context) override {
                // FXIME Implement me
                throw "plop";
            }
        };
        
        /// \brief Class HTTPServiceProcessWrapper
        template<typename Body>
        class HTTPServiceProcessWrapper<void, Body> : public HTTPServiceWrapper {
            
        private:
            std::function<void(const Body &)> function_;
            
        public:
            
            HTTPServiceProcessWrapper(HTTPMethod method, const std::string & pattern, std::function<void(const Body &)> function) : HTTPServiceWrapper(method, pattern), function_(function) {
                
            }
            
        public:
            
            
            /// \brief Process
            /// A process is a treatment which process an HTTPContext containing the HTTP request and  return an
            /// HTTPResponse
            /// \param context HTTP context containing request information
            /// \return an HTTP response
            virtual HTTPResponse process(HTTPContext &context) override {
                
                // Create stream decoder
                
                // FXIME Implement me
                
                return HTTPResponseBuilder{}.status(HTTPResponseStatus::NO_CONTENT).build();
            }
        };

        /// \brief Class HTTPServiceProcessWrapper
        template<>
        class HTTPServiceProcessWrapper<void, void> : public HTTPServiceWrapper {
            
        private:
            std::function<void()> function_;
            
        public:
            
            HTTPServiceProcessWrapper(HTTPMethod method, const std::string & pattern, std::function<void()> function) : HTTPServiceWrapper(method, pattern), function_(function) {
                
            }
            
        public:
            
            
            /// \brief Process
            /// A process is a treatment which process an HTTPContext containing the HTTP request and  return an
            /// HTTPResponse
            /// \param context HTTP context containing request information
            /// \return an HTTP response
            virtual HTTPResponse process(HTTPContext &context) override {
                
                // Launch funtion
                function_();
                
                return HTTPResponseBuilder{}.status(HTTPResponseStatus::NO_CONTENT).build();
            }
        };
    }
}
