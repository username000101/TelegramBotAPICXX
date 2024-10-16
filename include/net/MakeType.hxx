#pragma once

#include <iostream>

#include <nlohmann/json.hpp>

#include <types/InlineKeyboardMarkup.hxx>
#include <types/Message.hxx>
#include <types/ReplyParameters.hxx>

namespace telegram {
    namespace internal {
        std::string makeInlineKeyboardMarkup(bot::types::InlineKeyboardMarkup::Ptr keyboard);
        std::string makeMessage(bot::types::Message::Ptr message);
        std::string makeReplyParameters(bot::types::ReplyParameters::Ptr rp);
    }
}
