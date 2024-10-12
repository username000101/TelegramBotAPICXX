#pragma once

#include <string>
#include <memory>

#include <types/Location.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class BusinessLocation {
            public:
                typedef std::shared_ptr<BusinessLocation> Ptr;

                Location::Ptr location;
                std::string address;
            };
        }
    }
}
