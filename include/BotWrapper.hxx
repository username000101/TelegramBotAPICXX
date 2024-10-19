#pragma once

#include <cstdint>
#include <regex>
#include <memory>
#include <variant>

#include <types/Birthdate.hxx>
#include <types/BusinessIntro.hxx>
#include <net/CURLInteraction.hxx>
#include <types/Chat.hxx>
#include <types/ChatFullInfo.hxx>
#include <types/ChatPhoto.hxx>
#include <events/EventsBroadcast.hxx>
#include <types/ReplyParameters.hxx>
#include <Logger.hxx>
#include <types/Message.hxx>
#include <net/MakeType.hxx>
#include <net/ParseResponse.hxx>
#include <types/User.hxx>

using telegram::internal::logger::log;
using telegram::internal::logger::backgroundColors;
using telegram::internal::logger::foregroundColors;

namespace telegram {
    namespace bot {
        class BotWrapper {
        public:
            BotWrapper(const std::string& token) : curlInterface_(std::make_shared<internal::TelegramBotAPICURLInteractionLibrary>()) {
                if (token.empty()) {
                    log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make BotWrapper object: token must be non empty");
                } else {
                    this->token_ = token;
                }
            }

            const std::string& getToken() { return this->token_; }
            types::ChatFullInfo::Ptr getChat(std::variant<std::string, std::int64_t> identificator);
            types::Message::Ptr sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text, bot::types::ReplyParameters::Ptr reply_parameters = nullptr);

            events::EventsManager& getEvents() { return this->eventsManager_; }
        private:
            events::EventsManager eventsManager_;

            std::string token_;
            std::shared_ptr<internal::TelegramBotAPICURLInteractionLibrary> curlInterface_;

            friend class LongPoll;
        };
    }
}
