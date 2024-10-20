#include <BotWrapper.hxx>

telegram::bot::types::Message::Ptr telegram::bot::BotWrapper::sendMessage(std::variant<std::string, std::int64_t> identificator, const std::string& text, bot::types::ReplyParameters::Ptr replyParameters, bot::types::InlineKeyboardMarkup::Ptr keyboard) {
    std::regex pattern(" ");
    std::string strBuf = std::regex_replace(text, pattern, "%20");
    nlohmann::json jresp;

    if (std::holds_alternative<std::string>(identificator)) {
        std::vector<std::pair<std::string, std::string>> args;
        args.emplace_back("text", strBuf);
        args.emplace_back("chat_id", std::get<std::string>(identificator));

        if (replyParameters) {
            auto fixedJSON = std::regex_replace(internal::makeReplyParameters(replyParameters), pattern, "%20");
            args.emplace_back("reply_parameters", fixedJSON);
        }

        if (keyboard) {
            auto fixedJSON = std::regex_replace(internal::makeInlineKeyboardMarkup(keyboard), pattern, "%20");
            args.emplace_back("reply_markup", fixedJSON);
        }

        std::string response = this->curlInterface_->makeRequest(this->token_, "sendMessage", args, nullptr);

        if (response.empty()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'sendMessage': response is empty");
            return nullptr;
        }

        jresp = nlohmann::json::parse(response);
        if (!jresp["ok"].get<bool>()) {
            auto errorCode = jresp["error_code"].get<std::int32_t>();
            auto description = jresp["description"].get<std::string>();
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'sendMessage':\nerror_code: ", errorCode, "\ndescription: ", description);
            return nullptr;
        }

        return std::make_shared<bot::types::Message>(internal::parseMessage(response));
    } else {
        std::vector<std::pair<std::string, std::string>> args;
        args.emplace_back("text", strBuf);
        args.emplace_back("chat_id", std::to_string(std::get<std::int64_t>(identificator)));

        if (replyParameters) {
            auto fixedJSON = std::regex_replace(internal::makeReplyParameters(replyParameters), pattern, "%20");
            args.emplace_back("reply_parameters", fixedJSON);
        }

        if (keyboard) {
            auto fixedJSON = std::regex_replace(internal::makeInlineKeyboardMarkup(keyboard), pattern, "%20");
            args.emplace_back("reply_markup", fixedJSON);
        }

        std::string response = this->curlInterface_->makeRequest(this->token_, "sendMessage", args, nullptr);

        if (response.empty()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'sendMessage': response is empty");
            return nullptr;
        }

        jresp = nlohmann::json::parse(response);
        if (!jresp["ok"].get<bool>()) {
            auto errorCode = jresp["error_code"].get<std::int32_t>();
            auto description = jresp["description"].get<std::string>();
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'sendMessage':\nerror_code: ", errorCode, "\ndescription: ", description);
            return nullptr;
        }

        return std::make_shared<bot::types::Message>(internal::parseMessage(jresp["result"].dump()));
    }
}
