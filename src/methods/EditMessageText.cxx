#include <BotWrapper.hxx>

telegram::bot::types::Message::Ptr telegram::bot::BotWrapper::editMessageText(std::variant<std::string, std::int64_t> identificator, std::int64_t messageId, const std::string& newText, telegram::bot::types::ReplyParameters::Ptr replyParameters) {
    if (std::holds_alternative<std::string>(identificator)) {
        std::string response;

        if (replyParameters)
            response = this->curlInterface_->makeRequest(this->token_, "editMessageText", {{"chat_id", std::get<std::string>(identificator)}, {"message_id", std::to_string(messageId)}, {"text", newText}, {"reply_parameters", internal::makeReplyParameters(replyParameters)}}, nullptr);
        else
            response = this->curlInterface_->makeRequest(this->token_, "editMessageText", {{"chat_id", std::get<std::string>(identificator)}, {"message_id", std::to_string(messageId)}, {"text", newText}}, nullptr);

        if (response.empty()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'editMessageText': response is empty");
            return nullptr;
        }

        nlohmann::json jresp = nlohmann::json::parse(response);
        if (!jresp["ok"].get<bool>()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'editMessageText': ok != true");
            return nullptr;
        }

        return std::make_shared<types::Message>(internal::parseMessage(jresp["message"].dump()));
    } else {
        auto response = this->curlInterface_->makeRequest(this->token_, "editMessageText", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"message_id", std::to_string(messageId)}, {"text", newText}}, nullptr);

        if (replyParameters)
            response = this->curlInterface_->makeRequest(this->token_, "editMessageText", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"message_id", std::to_string(messageId)}, {"text", newText}, {"reply_parameters", internal::makeReplyParameters(replyParameters)}}, nullptr);
        else
            response = this->curlInterface_->makeRequest(this->token_, "editMessageText", {{"chat_id", std::to_string(std::get<std::int64_t>(identificator))}, {"message_id", std::to_string(messageId)}, {"text", newText}}, nullptr);

        if (response.empty()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'editMessageText': response is empty");
            return nullptr;
        }

        nlohmann::json jresp = nlohmann::json::parse(response);
        if (!jresp["ok"].get<bool>()) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process request 'editMessageText': ok != true");
            return nullptr;
        }

        return std::make_shared<types::Message>(internal::parseMessage(jresp["message"].dump()));
    }
}
