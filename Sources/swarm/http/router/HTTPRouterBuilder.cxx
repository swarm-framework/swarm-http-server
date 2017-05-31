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

#include "HTTPRouterBuilder.hxx"

#include "HTTPRouter.hxx"
#include "HTTPRouterEntry.hxx"

namespace swarm {
    namespace http {
        
        // Register an HTTP process for an URL pattern and method
        HTTPRouterBuilder & HTTPRouterBuilder::add(const HTTPMethod & method, const std::string & pattern, std::shared_ptr<HTTPProcess> process) {

            if (process) {
                // FIXME log existsing pattern
                patterns_[pattern] = process;
            }

            return *this;
        }
        
        // Create router
        std::shared_ptr<HTTPRouter> HTTPRouterBuilder::build() {


            std::shared_ptr<HTTPRouterEntry> rootEntry = std::shared_ptr<HTTPRouterEntry>(new HTTPRouterCharEntry{});

            for (auto entry : patterns_) {
                std::shared_ptr<HTTPRouterEntry> current = rootEntry;
                for (auto c : entry.first) {
                    current = current->add(c);
                }
                current->process(entry.second);
            }

            return std::shared_ptr<HTTPRouter>{
                new HTTPRouter{rootEntry}
            };
        }
    }
}
