#pragma once

#include <cstdint>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class Location {
            public:
                typedef std::shared_ptr<Location> Ptr;

                std::uint32_t livePeriod;
                std::uint32_t proximityAlertRadius;
                std::uint16_t heading;
                float latitude;
                float lontitude;
                float horizontalAccuracy;
            };
        }
    }
}
