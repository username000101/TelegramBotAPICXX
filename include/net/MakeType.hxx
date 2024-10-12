#pragma once

#include <iostream>

#include <types/InlineKeyboardMarkup.hxx>
#include <types/Message.hxx>

namespace telegram {
    namespace internal {
        std::string makeInlineKeyboardMarkup(bot::types::InlineKeyboardMarkup::Ptr keyboard);
        std::string makeMessage(bot::types::Message::Ptr message);
    }
}
