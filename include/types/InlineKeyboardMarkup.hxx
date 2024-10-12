#pragma once

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <types/GenericMarkup.hxx>
#include <types/InlineKeyboardButton.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class InlineKeyboardMarkup : public GenericMarkup {
            public:
                typedef std::shared_ptr<bot::types::GenericMarkup> Ptr;

                const bot::types::MarkupType getType() const override { return bot::types::MarkupType::INLINE_KEYBOARD_MARKUP; }

                std::vector<std::vector<bot::types::InlineKeyboardButton::Ptr>> inlineKeyboard;
            private:
            };
        }
    }
}
