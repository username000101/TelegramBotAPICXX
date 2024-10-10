#include <BotWrapper.hxx>

telegram::bot::types::Message::Ptr telegram::bot::BotWrapper::sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text) {
    std::regex pattern(" ");
    std::string strBuf = std::regex_replace(text, pattern, "%20");

    if (std::holds_alternative<std::string>(identificator)) {
        auto response = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::get<std::string>(identificator)}, {"text", strBuf}}, nullptr);
        if (response.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to prepare request 'sendMessage': response is empty" << std::endl;
#endif
            return nullptr;
        } else
            return std::make_shared<bot::types::Message>(internal::parseMessage(response));
    } else {
        auto response = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"text", strBuf}}, nullptr);
        if (response.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: " << __FILE << ":" << __LINE__ << ": Error: Failed to prepare request 'sendMessage': response is empty" << std::endl;
#endif
            return nullptr;
        }
        return std::make_shared<bot::types::Message>(internal::parseMessage(response));
    }
}
