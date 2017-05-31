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

#ifndef SWARM_HTTP_HTTPROUTERCHOICE_HXX
#define SWARM_HTTP_HTTPROUTERCHOICE_HXX

#include <memory>

namespace swarm {
    namespace http {

        class HTTPRouterEntry;

        /// \brief Define a router choice
        class HTTPRouterChoice {

        private:

            /// \brief Las entry
            std::shared_ptr<HTTPRouterEntry> entry_;

            /// \brief DEfine choice weight
            int weight_;

        public:

            std::shared_ptr<HTTPRouterEntry> entry() {
                return entry_;
            }

            int weight() const {
                return weight_;
            }

        public:

            /// \brief Create choice with entry
            /// \param entry HTTPRouter entry
            /// \param weight Choice weight
            HTTPRouterChoice(std::shared_ptr<HTTPRouterEntry> entry, int weight);
        };
    }
}


#endif //SWARM_HTTP_HTTPROUTERCHOICE_HXX
