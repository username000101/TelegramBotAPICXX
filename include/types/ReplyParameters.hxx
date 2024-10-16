#pragma once

#include <cstdint>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class ReplyParameters {
            public:
                typedef std::shared_ptr<ReplyParameters> Ptr;

                std::int64_t chatId;
                std::int64_t messageId;
            };
        }
    }
}
