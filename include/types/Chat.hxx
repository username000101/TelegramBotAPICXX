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


                std::int64_t id;
                std::string type;
                std::string title;
                std::string username;
                std::string firstName;
                std::string lastName;
                bool isForum;
            };
        }
    }
}
