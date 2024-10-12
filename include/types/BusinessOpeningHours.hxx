#pragma once

#include <string>
#include <memory>
#include <vector>

#include <types/BusinessOpeningHoursInterval.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class BusinessOpeningHours {
            public:
                typedef std::shared_ptr<BusinessOpeningHours> Ptr;

                std::string timeZoneName;
                std::vector<BusinessOpeningHoursInteval::Ptr> openingHours;
            };
        }
    }
}
