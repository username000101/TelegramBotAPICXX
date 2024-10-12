#pragma once

#include <cstdint>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class BusinessOpeningHoursInteval {
            public:
                typedef std::shared_ptr<BusinessOpeningHoursInteval> Ptr;

                std::uint32_t openingMinute;
                std::uint32_t closingMinute;
            };
        }
    }
}
