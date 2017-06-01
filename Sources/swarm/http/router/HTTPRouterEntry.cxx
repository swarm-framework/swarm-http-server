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

#include "HTTPRouterEntry.hxx"

#include "HTTPRouterChoice.hxx"

namespace swarm {
    namespace http {


        // Constructor with parent
        HTTPRouterEntry::HTTPRouterEntry(HTTPRouterEntry * parent) : parent_(parent) {

        }


        // Add next char choice
        std::shared_ptr<HTTPRouterEntry> HTTPRouterEntry::add(char c) {

            // Find if exists
            auto it = subChoices_.find(c);
            if (it == subChoices_.end()) {
                // Add sub choice
                std::shared_ptr<HTTPRouterEntry> entry;
                if (c == '*') {
                    entry = std::shared_ptr<HTTPRouterEntry>(new HTTPRouterWildCardEntry{this});
                } else {
                    entry = std::shared_ptr<HTTPRouterEntry>(new HTTPRouterCharEntry{c, this});
                }
                subChoices_[c] = entry;
                return entry;
            } else {
                // Return previously added choice
                return it->second;
            }
        }


        // Add next char choice
        void HTTPRouterEntry::add(char c, std::shared_ptr<HTTPRouterEntry> entry) {

            // Find if exists
            auto it = subChoices_.find(c);
            if (it == subChoices_.end()) {
                subChoices_[c] = entry;
            } else {
                // Return previously added choice
                // FIXME LOG
            }
        }

        // Default constructor for root entry
        HTTPRouterCharEntry::HTTPRouterCharEntry(HTTPRouterEntry * parent) : HTTPRouterEntry(parent), c_('\0') {

        }

        // Constructor whith char entry
        HTTPRouterCharEntry::HTTPRouterCharEntry(char c, HTTPRouterEntry * parent) : HTTPRouterEntry(parent), c_(c) {

        }

        // Find next choices for a character
        std::vector<std::shared_ptr<HTTPRouterEntry>> HTTPRouterCharEntry::next(char c) {

            std::vector<std::shared_ptr<HTTPRouterEntry>> chooses{};
            auto it = subChoices_.find(c);
            if (it != subChoices_.end()) {
                chooses.push_back(it->second);
            }
            it = subChoices_.find('*');
            if (it != subChoices_.end()) {
                chooses.push_back(it->second);
            }
            return chooses;
        }

        // constructor with process
        HTTPRouterWildCardEntry::HTTPRouterWildCardEntry(HTTPRouterEntry * parent) : HTTPRouterEntry(parent) {

        }

        // Find next choices for a character
        std::vector<std::shared_ptr<HTTPRouterEntry>> HTTPRouterWildCardEntry::next(char c) {
            std::vector<std::shared_ptr<HTTPRouterEntry>> chooses{};
            auto it = subChoices_.find(c);
            if (it != subChoices_.end()) {
                chooses.push_back(it->second);
            }

            // Add curent at other choice
            chooses.push_back(shared_from_this());
            return chooses;
        }

        // Add next char choice
        std::shared_ptr<HTTPRouterEntry> HTTPRouterWildCardEntry::add(char c) {
            auto entry = HTTPRouterEntry::add(c);

            // If as parent
            if (parent_ != nullptr) {
                
                // Add choice to parent
                parent_->add(c, entry);
            }

            return entry;
        }

        // Set process
        void HTTPRouterWildCardEntry::process(std::shared_ptr<HTTPProcess> process) {

            // Call mother process
            HTTPRouterEntry::process(process);

            // Test as parent
            if (parent_ != nullptr) {

                // Test if parent hasn't process
                if (!parent_->final()) {
                    parent_->process(process_);
                }
            }
        }
    }
}
