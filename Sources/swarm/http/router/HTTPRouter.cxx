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

#include "HTTPRouter.hxx"

#include "../process/HTTPContext.hxx"
#include "HTTPRouterChoice.hxx"
#include "HTTPRouterEntry.hxx"
#include <swarm/http/message/request/HTTPRequest.hxx>

#include <cxxlog/Level.hxx>

#define DEBUG 0

namespace swarm {
    namespace http {

        // Init logger
        cxxlog::Logger HTTPRouter::logger_ = LOGGER(HTTPRouter);

        // Find all choices
        void HTTPRouter::find(std::vector<std::shared_ptr<HTTPRouterChoice>> &choices,
                              std::shared_ptr<HTTPRouterChoice> choice, std::string::const_iterator it,
                              std::string::const_iterator end) {

#if DEBUG > 0
            logger_.log(cxxlog::Level::INFO, "char: %1%", choice->entry()->info());
#endif
            std::shared_ptr<HTTPRouterEntry> entry = choice->entry();

            if (it == end) {

                // If entry is final add it to choices
                if (entry->final()) {
                    // Add new choice with weight
                    choices.push_back(choice);
                }

                return;

            } else {

                auto others = entry->next(*it);
                auto next = it + 1;

                for (auto nextChoice : others) {
                    // FInd next with new weight
                    find(choices,
                         std::make_shared<HTTPRouterChoice>(nextChoice, choice->weight() + nextChoice->weight()), next,
                         end);
                }
            }
        }

        // Find HTTP process using context
        std::shared_ptr<HTTPProcess> HTTPRouter::find(HTTPContext &context) {

            // Find path
            auto path = context.request().path();

            std::vector<std::shared_ptr<HTTPRouterChoice>> chooses_;

            // Find all choices
            find(chooses_, std::make_shared<HTTPRouterChoice>(rootEntry_, 0), path.begin(), path.end());

            if (chooses_.empty()) {
                // No choice -> not found
                return std::shared_ptr<HTTPProcess>{};
            }

            // One choice -> the right, more sort by weight
            if (chooses_.size() > 1) {

                // Sort choices using weight
                std::sort(chooses_.begin(), chooses_.end(),
                          [](const std::shared_ptr<HTTPRouterChoice> &first,
                             const std::shared_ptr<HTTPRouterChoice> &second) -> bool {
                              return first->weight() > second->weight();
                          });
            }

#if DEBUG > 0
            for (auto choice : chooses_) {
                logger_.log(cxxlog::Level::INFO, "%1% ", choice->weight());
            }
#endif

            return chooses_[0]->entry()->process();
        }
    }
}
