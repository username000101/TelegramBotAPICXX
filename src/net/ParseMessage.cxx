#include <net/ParseResponse.hxx>

telegram::bot::types::Message telegram::internal::parseMessage(const std::string& messageJSON) {
    nlohmann::json j = nlohmann::json::parse(messageJSON);
    bot::types::Message msg;
    bot::types::Chat chat;
    bot::types::User user;

    if (!j.contains("ok")) {
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'Message': response does not contains 'ok'" << std::endl;
        return msg;
    }
    if (!j["ok"].get<bool>()) {
        auto errorDescription = j["description"].get<std::string>();
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'Message': returned error: " << errorDescription << std::endl;
        return msg;
    }

    j = j["result"];

    if (!j.contains("message_id")) {
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'Message': response does not contains 'message_id'" << std::endl;
        return msg;
    }
    msg.id = j["message_id"].get<std::uint64_t>();

    if (!j.contains("from")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response does not contains 'from'" << std::endl;
        return msg;
    }
    auto fromField = j["from"];

    if (!fromField.contains("id")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::from does not contains 'id'" << std::endl;
        return msg;
    }
    user.id = fromField["id"].get<std::int64_t>();

    if (!fromField.contains("is_bot")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::from does not contains 'is_bot'" << std::endl;
        return msg;
    }
    user.isBot = fromField["is_bot"].get<bool>();

    if (!fromField.contains("first_name")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::from does not contains 'first_name'" << std::endl;
        return msg;
    }
    user.firstName = fromField["first_name"].get<std::string>();

    if (!fromField.contains("last_name")) {
        std::cout << "TelegramBotAPI: Warning: In parse 'Message': response::from does not contains 'last_name' ==> !! this is not an error !! <==" << std::endl;
    } else {
        user.lastName = fromField["last_name"].get<std::string>();
    }

    if (!fromField.contains("username")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::from does not contains 'username'" << std::endl;
        return msg;
    }
    user.username = fromField["username"].get<std::string>();

    if (!j.contains("chat")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response does not contains 'chat'" << std::endl;
        return msg;
    }
    auto chatField = j["chat"];

    if (!chatField.contains("id")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::chat does not contains 'id'" << std::endl;
        return msg;
    }
    chat.id = chatField["id"].get<std::int64_t>();

    if (!chatField.contains("first_name")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::chat does not contains 'first_name'" << std::endl;
        return msg;
    }
    chat.firstName = chatField["first_name"].get<std::string>();

    if (!chatField.contains("username")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::chat does not contains 'username'" << std::endl;
        return msg;
    }
    chat.username = chatField["username"].get<std::string>();

    if (!chatField.contains("type")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response::chat does not contains 'type'" << std::endl;
        return msg;
    }
    chat.type = chatField["type"].get<std::string>();

    if (!j.contains("date")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response does not contains 'date'" << std::endl;
        return msg;
    }
    msg.date = j["date"].get<std::uint64_t>();

    if (!j.contains("text")) {
        std::cout << "TelegramBotAPI: Error: failed to parse 'Message': response does not contains 'text'" << std::endl;
        return msg;
    }
    msg.text = j["text"].get<std::string>();
    msg.from = std::make_shared<bot::types::User>(user);
    msg.chat = std::make_shared<bot::types::Chat>(chat);

    return msg;
}
