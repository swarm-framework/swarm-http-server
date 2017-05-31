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

#include "HTTPServer.hxx"

#include "HTTPServerDelegate.hxx"
#include "StandardErrorBuilder.hxx"
#include "swarm/http/process/HTTPProcess.hxx"
#include "swarm/http/router/HTTPRouter.hxx"
#include "swarm/http/server/HTTPSession.hxx"
#include <swarm/http/message/request/HTTPRequest.hxx>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp> 

namespace swarm {
    namespace http {

        // Constructor with delegate ,port and router
        HTTPServer::HTTPServer(std::shared_ptr<HTTPServerDelegate> delegate, int port,
                               std::shared_ptr<HTTPRouter> router)
            : port_(port), delegate_(delegate), router_(router) {}

        // Method to ens internal error
        void HTTPServer::sendError(std::shared_ptr<HTTPSession> session, const std::string &message) {

            // Create standard error
            auto response =
                StandardErrorBuilder{}.error(HTTPResponseStatus::INTERNAL_SERVER_ERROR).message(message).build();

            // Send response
            delegate_->send(*this, session, response);
        }

        // Process requests
        void HTTPServer::process() {

            // Init delegate
            delegate_->init(*this);

            do {
                // Find session
                std::shared_ptr<HTTPSession> session = delegate_->listening(*this);

                // Create context
                HTTPContext context{session->request()};

                try {
                    // Find process form router
                    std::shared_ptr<HTTPProcess> process = router_->find(context);
                    if (process) {

                        // Process request
                        HTTPResponse response = process->process(context);

                        // Send response
                        delegate_->send(*this, session, response);
                    } else {

                        // Create standard error
                        auto response = StandardErrorBuilder{}
                                            .error(HTTPResponseStatus::NOT_FOUND)
                                            .message(context.request().uri())
                                            .build();

                        // Send response
                        delegate_->send(*this, session, response);
                    }
                    
                }  catch (std::exception ex) {

                    // Create standard error
                    sendError(session, boost::diagnostic_information(ex, true));
                } catch (...) {

                    // Create standard error
                    sendError(session, "Unknown error");
                }

            } while (true);
        }
    }
}
