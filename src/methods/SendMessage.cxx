#include <BotWrapper.hxx>

telegram::bot::types::Message::Ptr telegram::bot::BotWrapper::sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text, bot::types::ReplyParameters::Ptr reply_parameters) {
    std::regex pattern(" ");
    std::string strBuf = std::regex_replace(text, pattern, "%20");

    if (std::holds_alternative<std::string>(identificator)) {
        std::string response;

        if (reply_parameters) {
            response = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"reply_parameters", internal::makeReplyParameters(reply_parameters)}, {"chat_id", std::get<std::string>(identificator)}, {"text", strBuf}}, nullptr);
        } else {
            response = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::get<std::string>(identificator)}, {"text", strBuf}}, nullptr);
        }
        if (response.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to prepare request 'sendMessage': response is empty" << std::endl;
#endif
            return nullptr;
        } else
            return std::make_shared<bot::types::Message>(internal::parseMessage(response));
    } else {
        std::string response;

        if (reply_parameters) {
            response = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"text", strBuf}, {"reply_parameters", internal::makeReplyParameters(reply_parameters)}}, nullptr);
        } else {
            response = this->curlInterface_->makeRequest(this->token_, "sendMessage", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"text", strBuf}, {"reply_parameters", internal::makeReplyParameters(reply_parameters)}}, nullptr);
        }
        if (response.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to prepare request 'sendMessage': response is empty" << std::endl;
#endif
            return nullptr;
        }
        return std::make_shared<bot::types::Message>(internal::parseMessage(response));
    }
}
