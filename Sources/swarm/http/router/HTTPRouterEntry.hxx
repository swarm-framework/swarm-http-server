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

#ifndef SWARM_HTTP_HTTPROUTERENTRY_HXX
#define SWARM_HTTP_HTTPROUTERENTRY_HXX

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace swarm {
    namespace http {

        struct HTTPProcess;
        class HTTPRouterChoice;

        /// \brief Define a router entry
        class HTTPRouterEntry {

        protected:

            /// \brief Parent entry
            HTTPRouterEntry * parent_;

            /// \brief All sub choices
            std::map<char, std::shared_ptr<HTTPRouterEntry>> subChoices_;

            /// \brief Final process
            std::shared_ptr<HTTPProcess> process_;

        public:

            /// \brief Constructor with parent
            /// \param parent Parent entry or nullptr
            HTTPRouterEntry(HTTPRouterEntry * parent = nullptr);

            /// \brief Add a char at next choice
            /// \param c Next char choice
            /// \return Pointer to next entry
            virtual std::shared_ptr<HTTPRouterEntry> add(char c);

            /// \brief Add a char at next choice
            /// \param c Next char choice
            /// \param entry Pointer to next entry
            void add(char c, std::shared_ptr<HTTPRouterEntry> entry);

            /// \return Entry weight (0 for wild card, 1 for char)
            virtual int weight() const = 0;

            /// \return Get info about entry
            virtual std::string info() const = 0;

            /// \brief Is can be a final entry
            /// \return true If entry has process attached
            virtual bool final() {
                return static_cast<bool>(process_);
            }

            /// \return Final process
            virtual std::shared_ptr<HTTPProcess> process() {
                return process_;
            }

            /// \brief Set process
            /// \param process New process
            void process(std::shared_ptr<HTTPProcess> process) {
                this->process_ = process;
            }

            /// \brief Find next entries for a character
            /// \param c Next caracter
            /// \result List of entries
            virtual std::vector<std::shared_ptr<HTTPRouterEntry>> next(char c) = 0;

            // Virtual destructor for sub classing
            virtual ~HTTPRouterEntry() {}
        };

        /// \brief HTTP router entry
        class HTTPRouterCharEntry : public HTTPRouterEntry {

        private:

            /// \brief Current char entry
            char c_;


        public:

            /// \brief Default constructor for root entry
            /// \param parent Parent entry or nullptr
            HTTPRouterCharEntry(HTTPRouterEntry * parent = nullptr);

            /// \brief Constructor whith char entry
            /// \param c current char
            /// \param parent Parent entry or nullptr
            HTTPRouterCharEntry(char c, HTTPRouterEntry * parent);

            /// \brief Find next entry for a character
            /// \param c Next caracter
            /// \result List of entries
            virtual std::vector<std::shared_ptr<HTTPRouterEntry>> next(char c) override;

            /// \return Get info about entry
            virtual std::string info() const override {
                return std::string{c_};
            }

            /// \return Entry weight
            virtual int weight() const override {
                return 1;
            }
        };

        /// \brief HTTP router entry
        class HTTPRouterWildCardEntry : public HTTPRouterEntry, public std::enable_shared_from_this<HTTPRouterWildCardEntry> {

        public:

            /// \brief constructor with process
            /// \param parent Parent entry or nullptr
            HTTPRouterWildCardEntry(HTTPRouterEntry * parent = nullptr);

            /// \brief Find next entry for a character
            /// \param c Next caracter
            /// \result List of entries
            virtual std::vector<std::shared_ptr<HTTPRouterEntry>> next(char c) override;

            /// \return Get info about entry
            virtual std::string info() const override {
                return "*";
            }

            /// \return Entry weight
            virtual int weight() const override {
                return 0;
            }

            /// \brief Add a char at next choice
            /// \param c Next char choice
            /// \return Pointer to next entry
            virtual std::shared_ptr<HTTPRouterEntry> add(char c) override;
        };
    }
}

#endif //SWARM_HTTP_HTTPROUTERENTRY_HXX
