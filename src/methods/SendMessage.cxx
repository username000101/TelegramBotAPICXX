#include <BotWrapper.hxx>

telegram::bot::types::Message::Ptr telegram::bot::BotWrapper::sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text) {
    if (std::holds_alternative<std::string>(identificator)) {
        auto responce = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::get<std::string>(identificator)}, {"text", text}}, nullptr);
        if (responce.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: Failed to prepare request 'sendMessage': responce is empty" << std::endl;
#endif
            return nullptr;
        } else
            return std::make_shared<bot::types::Message>(internal::parseMessage(responce));
    } else {
        auto responce = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"text", text}}, nullptr);
        if (responce.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: Failed to prepare request 'sendMessage': responce is empty" << std::endl;
#endif
            return nullptr;
        }
        return std::make_shared<bot::types::Message>(internal::parseMessage(responce));
    }
}
