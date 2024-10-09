#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include <types/Birthdate.hxx>
#include <types/ChatPhoto.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class ChatFullInfo {
            public:
                typedef std::shared_ptr<ChatFullInfo> Ptr;

                enum ChatType { PRIVATE, GROUP, SUPERGROUP, CHANNEL, };

                std::int64_t id;
                ChatType type;
                std::string title;
                std::string username;
                std::string firstName;
                std::string lastName;
                std::string bio;
                bool isForum;
                bool hasPrivateForwards;
                std::uint32_t accentColorId;
                std::uint8_t maxReactionsCount;
                std::vector<std::string> activeUsernames;
                ChatPhoto::Ptr photo;
                Birthdate::Ptr birthdate;

            };
        }
    }
}
