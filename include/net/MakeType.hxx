#pragma once

#include <nlohmann/json.hpp>

#include <types/InlineKeyboardMarkup.hxx>
#include <types/ReplyParameters.hxx>
#include <Logger.hxx>
#include <types/Message.hxx>

using telegram::internal::logger::log;
using telegram::internal::logger::backgroundColors;
using telegram::internal::logger::foregroundColors;

namespace telegram {
    namespace internal {
        std::string makeInlineKeyboardMarkup(bot::types::InlineKeyboardMarkup::Ptr keyboard);
        std::string makeMessage(bot::types::Message::Ptr message);
        std::string makeReplyParameters(bot::types::ReplyParameters::Ptr rp);
    }
}
