#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include <types/User.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class Message {
            public:
                typedef std::shared_ptr<Message> Ptr;

                std::int64_t id;
                std::int64_t threadId;
                User::Ptr from;

                std::uint64_t senderBoostCount;
                User::Ptr senderBuisnessBot;
                std::uint64_t date;
                std::string businessConnectionId;
                bool isTopicMessage;
                bool isAutomaticForward;
                Message::Ptr replyToMessage;

            };
        }
    }
}
