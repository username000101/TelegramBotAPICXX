#pragma once

#include <string>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class BusinessIntro {
            public:
                typedef std::shared_ptr<BusinessIntro> Ptr;

                std::string title;
                std::string message;
            };
        }
    }
}
