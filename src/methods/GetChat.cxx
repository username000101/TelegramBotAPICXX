#include <BotWrapper.hxx>

telegram::bot::types::ChatFullInfo::Ptr telegram::bot::BotWrapper::getChat(std::variant<std::string, std::int64_t> identificator) {
    if (std::holds_alternative<std::string>(identificator)) {
        auto response = this->curlInterface_->makeRequest(this->token_, "getChat", {{"chat_id", std::get<std::string>(identificator)}}, nullptr);
        if (response.empty()) {
            log(__FILE__, ":", __LINE__, ": Error: Failed to prepare request 'getChat': response is empty");
            return nullptr;
        } else
            return std::make_shared<types::ChatFullInfo>(internal::parseChatFullInfo(response));
    } else {
        auto response = this->curlInterface_->makeRequest(this->token_, "getChat", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}}, nullptr);
        if (response.empty()) {
            log(__FILE__, ":", __LINE__, ": Error: Failed to prepare request 'getChat': response is empty");
            return nullptr;
        } else
            return std::make_shared<types::ChatFullInfo>(internal::parseChatFullInfo(response));
    }
}
