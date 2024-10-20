#pragma once

#include <string>
#include <vector>

#include <curl/curl.h>

#include <types/File.hxx>
#include <Logger.hxx>

using telegram::internal::logger::log;
using telegram::internal::logger::backgroundColors;
using telegram::internal::logger::foregroundColors;

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
                    log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to init CURL");
                else
                    log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: The CURL object was created");
            }

            ~TelegramBotAPICURLInteractionLibrary() {
                curl_easy_cleanup(this->_curl);
                log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: The CURL object was deleted");
            }

            std::string makeRequest(const std::string& token, const std::string& rquestName, std::vector<std::pair<std::string, std::string>>& args, std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*), bot::types::File::Ptr file = nullptr);
            std::string makeRequest(const std::string& token, const std::string& requestName, std::vector<std::pair<std::string, std::string>>&& args, std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*), bot::types::File::Ptr file = nullptr);

        private:
            enum ResourcesType { CURL_MIME, CURL_CURL, };
            std::vector<std::pair<void*, ResourcesType>> _resources;
            inline void cleanup() {
                for (auto iter = this->_resources.begin(); iter != this->_resources.end(); *iter++) {
                    if (!iter->first)
                        continue;
                    else {
                        switch (iter->second) {
                            case CURL_MIME: {
                            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: Deleted allocated memory chunk(CURL_MIME)(address: ", iter->first, ")");
                                curl_mime_free((curl_mime*)iter->first);
                                break;
                            }

                            case CURL_CURL: {
                                log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: Deleted allocated memory chunk(CURL_CURL)(address: ", iter->first, ")");
                                curl_easy_cleanup((CURL*)iter->first);
                                break;
                            }
                        }

                        this->_resources.erase(iter);
                    }
                }
            }

            std::size_t(*_writeFunction)(void*, std::size_t, size_t, std::string*);
            std::string _defaultUrl;
            CURL* _curl;
        };
    }
}
