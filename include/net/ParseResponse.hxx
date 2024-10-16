#pragma once

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include <types/Birthdate.hxx>
#include <types/BusinessIntro.hxx>
#include <types/Chat.hxx>
#include <types/ChatFullInfo.hxx>
#include <types/ChatPhoto.hxx>
#include <types/ReplyParameters.hxx>
#include <types/Message.hxx>
#include <types/User.hxx>

namespace telegram {
    namespace internal {
        bot::types::Birthdate parseBirthdate(const std::string& birthdateJSON);
        bot::types::BusinessIntro parseBusinessIntro(const std::string& businessIntroJSON);
        bot::types::ChatPhoto parseChatPhoto(const std::string& chatPhotoJSON);
        bot::types::Chat parseChat(const std::string& chatJSON);
        bot::types::ChatFullInfo parseChatFullInfo(const std::string& chatFullInfoJSON);
        bot::types::Message parseMessage(const std::string& messageJSON);
        bot::types::User parseUser(const std::string& userJSON);
    }
}
