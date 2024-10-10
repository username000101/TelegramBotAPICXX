#pragma once

#include <iostream>

#include <types/InlineKeyboardMarkup.hxx>

namespace telegram {
    namespace internal {
        std::string makeInlineKeyboardMarkup(bot::types::InlineKeyboardMarkup::Ptr keyboard);
    }
}
