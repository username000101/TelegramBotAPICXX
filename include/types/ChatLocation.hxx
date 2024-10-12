#pragma once

#include <string>
#include <memory>

#include <types/Location.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class ChatLocation {
            public:
                typedef std::shared_ptr<ChatLocation> Ptr;

                Location::Ptr location;
                std::string address;
            };
        }
    }
}
