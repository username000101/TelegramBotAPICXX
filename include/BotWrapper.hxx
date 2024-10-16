#pragma once

#include <cstdint>
#include <iostream>
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
#include <types/Message.hxx>
#include <net/MakeType.hxx>
#include <net/ParseResponse.hxx>
#include <types/User.hxx>

namespace telegram {
    namespace bot {
        class BotWrapper {
        public:
            BotWrapper(const std::string& token) {
                this->token_ = token;
                this->curlInterface_ = std::make_shared<telegram::internal::TelegramBotAPICURLInteractionLibrary>();
            }

            const std::string& getToken() { return this->token_; }

            types::ChatFullInfo::Ptr getChat(std::variant<std::string, std::int64_t> identificator);
            types::Message::Ptr sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text, bot::types::ReplyParameters::Ptr reply_parameters = nullptr);
        private:
            std::string token_;
            std::shared_ptr<telegram::internal::TelegramBotAPICURLInteractionLibrary> curlInterface_;
        };
    }
}
