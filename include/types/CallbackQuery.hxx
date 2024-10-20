#pragma once

#include <string>
#include <memory>

#include <types/User.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class CallbackQuery {
            public:
                typedef std::shared_ptr<CallbackQuery> Ptr;

                std::string id;
                types::User::Ptr from;
                std::string inlineMessageId;
                std::string chatInstance;
                std::string data;
                std::string gameShortName;
            };
        }
    }
}
