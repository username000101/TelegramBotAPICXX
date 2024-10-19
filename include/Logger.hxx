#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

namespace telegram {
    namespace internal {
        namespace logger {
            const std::unordered_map<std::string, std::string> foregroundColors = {
                {"red", "\033[31m"},
                {"RED", "\033[31m"},

                {"green", "\033[32m"},
                {"GREEN", "\033[32m"},

                {"reset", "\033[0m"},
                {"RESET", "\033[0m"},
            };

            const std::unordered_map<std::string, std::string> backgroundColors = {
                {"red", "\033[41m"},
                {"RED", "\033[41m"},

                {"green", "\033[42m"},
                {"GREEN", "\033[42m"},

                {"reset", "\033[0m"},
                {"RESET", "\033[0m"},
            };

            template <typename... Args> void log(Args... arguments) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
                std::cout << "TelegramBotAPI: ";
                (std::cout << ... << arguments) << std::endl;
#endif
            }
        }
    }
}
