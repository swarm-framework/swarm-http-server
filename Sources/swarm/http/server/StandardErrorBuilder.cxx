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

#include "StandardErrorBuilder.hxx"

#include <sstream>
#include <swarm/http/message/body/HTTPBody.hxx>
#include <swarm/http/message/response/HTTPResponse.hxx>
#include <swarm/http/message/response/HTTPResponseBuilder.hxx>
#include <swarm/http/stream/HTTPStringStream.hxx>

namespace swarm {
    namespace http {

        // Set status code
        StandardErrorBuilder &StandardErrorBuilder::error(HTTPResponseStatus status) {
            this->status_ = status;
            return *this;
        }

        // Set message
        StandardErrorBuilder &StandardErrorBuilder::message(const std::string &msg) {
            message_.reset(new std::string{msg});
            return *this;
        }

        // Create error body response
        HTTPResponse StandardErrorBuilder::build() {

            std::stringstream ss;

            ss << "<html>";
            ss << "<head></head>";
            ss << "<body>"
               << "<h1>Error HTTP " << status_.code() << "</h1>"
               << "<hr />"
               << "<p>" << status_.reason() << "</p>";

            if (message_) {
                ss << "<p>" << *message_ << "<p>";
            }

            ss << "<div>Powered by Swarm</div>"
               << "</body>";
            ss << "</html>";

            return HTTPResponseBuilder{}
                .status(status_)
                .body(std::make_shared<HTTPBody>(MediaType::TEXT_HTML, std::make_shared<HTTPStringStream>(ss.str())))
                .build();
        }
    }
}
