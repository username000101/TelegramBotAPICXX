#include <net/CURLInteraction.hxx>

std::string telegram::internal::TelegramBotAPICURLInteractionLibrary::makeRequest(const std::string& token, const std::string& requestName, std::vector<std::pair<std::string, std::string>>& args,
                                                                                  std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*)) {
    if (!this->_curl) {
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to make request: CURL is nullptr" << std::endl;
        return "";
    }
    std::string buffer;
    std::string url = this->_defaultUrl + "/bot" + token + "/" + requestName;
    curl_easy_setopt(this->_curl, CURLOPT_WRITEDATA, &buffer);
    if (!writeFunction) {
        if (!this->_writeFunction) {
            std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to make request: not found someone write function" << std::endl;
        } else {
            curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, this->_writeFunction);
        }
    } else {
        curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, writeFunction);
    }

    if (!args.empty()) {
        url += "?";
        for (auto& i : args) {
            url+= i.first + "=" + i.second + "&";
        }
    }
    curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());


    CURLcode res;
    res = curl_easy_perform(this->_curl);
    if (res != CURLE_OK) {
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to prepare request: " << curl_easy_strerror(res) << "(URL: " << url << ")" << std::endl;
        return "";
    }

    return buffer;
}

std::string telegram::internal::TelegramBotAPICURLInteractionLibrary::makeRequest(const std::string& token, const std::string& requestName, std::vector<std::pair<std::string, std::string>>&& args,
                                                                                  std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*)) {
    return this->makeRequest(token, requestName, args, writeFunction);
}

#include <BotWrapper.hxx>

int main() {
    telegram::bot::BotWrapper bot("7205719382:AAFNGy3VAiG0Vsx5il_dCIILxDK1DwSBhOI");
    auto chatInfo = bot.getChat(6627530378);
    std::cout << chatInfo->firstName << "\n\n" << chatInfo->username << "\n\n" << chatInfo->bio << "\n\n" << chatInfo->birthdate->day << "." << chatInfo->birthdate->month << std::endl;
}
