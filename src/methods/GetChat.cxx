#include <BotWrapper.hxx>

telegram::bot::types::ChatFullInfo::Ptr telegram::bot::BotWrapper::getChat(std::variant<std::string, std::int64_t> identificator) {
    if (std::holds_alternative<std::string>(identificator)) {
        auto response = this->curlInterface_->makeRequest(this->token_, "getChat", {{"chat_id", std::get<std::string>(identificator)}}, nullptr);
        if (response.empty()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'getChat': response is empty");
            return nullptr;
        } else {
            nlohmann::json jresp = nlohmann::json::parse(response);
            if (!jresp["ok"].get<bool>()) {
                log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'getChat': ok != true");
                return nullptr;
            }
            return std::make_shared<types::ChatFullInfo>(internal::parseChatFullInfo(jresp["result"].dump()));
        }
    } else {
        auto response = this->curlInterface_->makeRequest(this->token_, "getChat", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}}, nullptr);
        if (response.empty()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'getChat': response is empty");
            return nullptr;
        }

        nlohmann::json jresp = nlohmann::json::parse(response);
        if (!jresp["ok"].get<bool>()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'getChat': ok != true");
            return nullptr;
        }

        return std::make_shared<types::ChatFullInfo>(internal::parseChatFullInfo(response));
    }
}
