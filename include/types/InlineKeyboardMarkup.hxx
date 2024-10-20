#pragma once

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <types/InlineKeyboardButton.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class InlineKeyboardMarkup {
            public:
                typedef std::shared_ptr<bot::types::InlineKeyboardMarkup> Ptr;

                std::vector<std::vector<bot::types::InlineKeyboardButton::Ptr>> inlineKeyboard;
            private:
            };
        }
    }
}
