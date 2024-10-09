#pragma once

#include <string>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class ChatPhoto {
            public:
                typedef std::shared_ptr<ChatPhoto> Ptr;

                std::string smallFileID;
                std::string smallFileUniqueID;
                std::string bigFileID;
                std::string bigFileUniqueID;
            };
        }
    }
}
