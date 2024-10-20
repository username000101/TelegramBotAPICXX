#include <net/CURLInteraction.hxx>

std::string telegram::internal::TelegramBotAPICURLInteractionLibrary::makeRequest(const std::string& token, const std::string& requestName, std::vector<std::pair<std::string, std::string>>& args, std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*), bot::types::File::Ptr file) {
    if (!this->_curl) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make request: CURL is nullptr");
        return "";
    }
    std::string buffer;
    std::string url = this->_defaultUrl + "/bot" + token + "/" + requestName;
    curl_easy_setopt(this->_curl, CURLOPT_WRITEDATA, &buffer);
    if (!writeFunction) {
        if (!this->_writeFunction) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make request: not found someone write function");
        } else {
            curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, this->_writeFunction);
        }
    } else {
        curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, writeFunction);
    }

    if (!args.empty()) {
        url += "?";
        url += "&";
        for (auto& i : args) {
            url+= i.first + "=" + i.second;
        }
    }

    if (file) {
        if (!std::filesystem::exists(file->file)) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make request '", requestName, "': file \"", file->file, "\" does not exists");
            return "";
        }

        curl_mime* mime = curl_mime_init(this->_curl);
        curl_mimepart* part = curl_mime_addpart(mime);

        curl_mime_name(part, "document");
        curl_mime_data(part, file->file.c_str(), CURL_ZERO_TERMINATED);

        curl_mime_filename(part, file->file.stem().c_str());

        curl_easy_setopt(this->_curl, CURLOPT_MIMEPOST, mime);

        this->_resources.emplace_back(mime, CURL_MIME);
    }

    curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());


    CURLcode res;
    res = curl_easy_perform(this->_curl);
    this->cleanup();
    if (res != CURLE_OK) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to prepare request: ", curl_easy_strerror(res), "(URL: ", url, ")");
        return "";
    }

    return buffer;
}

std::string telegram::internal::TelegramBotAPICURLInteractionLibrary::makeRequest(const std::string& token, const std::string& requestName, std::vector<std::pair<std::string, std::string>>&& args, std::size_t(*writeFunction)(void*, std::size_t, size_t, std::string*), bot::types::File::Ptr file) {
    return this->makeRequest(token, requestName, args, writeFunction, file);
}
