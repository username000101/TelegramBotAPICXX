#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

#include <net/CURLInteraction.hxx>
#include <types/Birthdate.hxx>
#include <types/BusinessIntro.hxx>
#include <types/Chat.hxx>
#include <types/ChatFullInfo.hxx>
#include <types/ChatPhoto.hxx>
#include <types/Message.hxx>
#include <net/ParseResponce.hxx>
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
            types::Message::Ptr sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text);
        private:
            std::string token_;
            std::shared_ptr<telegram::internal::TelegramBotAPICURLInteractionLibrary> curlInterface_;
        };
    }
}
