#pragma once

#include <string>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class InlineKeyboardButton {
            public:
                typedef std::shared_ptr<InlineKeyboardButton> Ptr;

                std::string text;
                std::string url;
                std::string callbackData;
                std::string switchInlineQuery;
                std::string switchInlineQueryCurrentChat;
                bool pay;
            };
        }
    }
}
