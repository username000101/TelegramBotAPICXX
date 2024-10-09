#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class Chat {
            public:
                typedef std::shared_ptr<Chat> Ptr;

                enum class ChatType { PRIAVATE, GROUP, SUPERGROUP, CHANNEL };

                std::int64_t id;
                ChatType type;
                std::string title;
                std::string username;
                std::string firstName;
                std::string lastName;
                bool isForum;
            };
        }
    }
}
