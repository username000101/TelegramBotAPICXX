#include <BotWrapper.hxx>

telegram::bot::types::ChatFullInfo::Ptr telegram::bot::BotWrapper::getChat(std::variant<std::string, std::int64_t> identificator) {
    if (std::holds_alternative<std::string>(identificator)) {
        auto responce = this->curlInterface_->makeRequest(this->token_, "getChat", {{"chat_id", std::get<std::string>(identificator)}}, nullptr);
        if (responce.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: Failed to prepare request 'getChat': responce is empty" << std::endl;
#endif
            return nullptr;
        } else
            return std::make_shared<types::ChatFullInfo>(internal::parseChatFullInfo(responce));
    } else {
        auto responce = this->curlInterface_->makeRequest(this->token_, "getChat", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}}, nullptr);
        if (responce.empty()) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
            std::cout << "TelegramBotAPI: Failed to prepare request 'getChat': responce is empty" << std::endl;
#endif
            return nullptr;
        } else
            return std::make_shared<types::ChatFullInfo>(internal::parseChatFullInfo(responce));
    }
}
