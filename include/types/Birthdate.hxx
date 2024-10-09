#pragma once

#include <cstdint>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class Birthdate {
            public:
                typedef std::shared_ptr<Birthdate> Ptr;

                std::uint8_t day;
                std::uint8_t month;
                std::uint32_t year;
            };
        }
    }
}
