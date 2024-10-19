#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace telegram {
    namespace bot {
        namespace types {
            class User {
            public:
                typedef std::shared_ptr<User> Ptr;

                std::int64_t id;
                bool isBot;
                std::string firstName;
                std::string lastName;
                std::string username;
                std::string languageCode;
                bool isPremium;
                bool addedToAttachmentMenu;
                bool canJoinGroups;
                bool canReadAllGroupMessages;
                bool supportsInlineQueries;
                bool canConnectToBuisness;
                bool hasMainWebApp;

            };
        }
    }
}
