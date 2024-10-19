#pragma once

#include <cstdint>

#include <BotWrapper.hxx>
#include <net/CURLInteraction.hxx>
#include <Logger.hxx>

using telegram::internal::logger::log;
using telegram::internal::logger::backgroundColors;
using telegram::internal::logger::foregroundColors;

namespace telegram {
    namespace bot {
        class LongPoll {
        public:
            LongPoll(BotWrapper& bot, std::uint64_t initialOffset = 0, double timeout = 10.0, unsigned short limit = 100) : bot_(bot), lastUpdateId_(initialOffset), timeout_(timeout), limit_(limit) {
                if (timeout == 0.0)
                    log(__FILE__, ":", __LINE__, ": Warning: use the zero timeout don't recommended(use it only for testing)");
            }

            void longPollStart();
        private:
            unsigned short limit_;
            double timeout_;
            std::uint64_t lastUpdateId_;
            BotWrapper& bot_;
        };
    }
}
