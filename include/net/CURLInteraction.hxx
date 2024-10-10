#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <curl/curl.h>

namespace telegram {
    namespace internal {
    inline std::size_t curlWriteString(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    s->resize(oldLength + newLength);
    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
    return newLength;
}


class TelegramBotAPICURLInteractionLibrary {
        public:
            TelegramBotAPICURLInteractionLibrary(const std::string& defaultUrl = "https://api.telegram.org",
                                                 std::size_t(*defaultWritedataFunction)(void*, std::size_t, size_t, std::string*) = curlWriteString) {
                if (!defaultWritedataFunction)
                    this->_writeFunction = curlWriteString;
                else
                    this->_writeFunction = defaultWritedataFunction;

                this->_defaultUrl = defaultUrl;
                this->_curl = curl_easy_init();
                if (!this->_curl)
                    std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to init CURL" << std::endl;
                else
                    std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: The CURL object has been created" << std::endl;
            }

            ~TelegramBotAPICURLInteractionLibrary() {
                curl_easy_cleanup(this->_curl);
                std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: The CURL object has been deleted" << std::endl;
            }

            std::string makeRequest(const std::string& token, const std::string& rquestName, std::vector<std::pair<std::string, std::string>>& args, std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*));
            std::string makeRequest(const std::string& token, const std::string& requestName, std::vector<std::pair<std::string, std::string>>&& args, std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*));

        private:
            std::size_t(*_writeFunction)(void*, std::size_t, size_t, std::string*);
            std::string _defaultUrl;
            CURL* _curl;
        };
    }
}
