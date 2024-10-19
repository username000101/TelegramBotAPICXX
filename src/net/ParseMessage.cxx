#include <net/ParseResponse.hxx>

telegram::bot::types::Message telegram::internal::parseMessage(const std::string& messageJSON) {
    nlohmann::json j = nlohmann::json::parse(messageJSON);
    bot::types::Message msg;
    bot::types::Chat chat;
    bot::types::User user;

    if (!j.contains("ok")) {
        log(__FILE__,":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'Message': response does not contains 'ok'");
        return msg;
    }
    if (!j["ok"].get<bool>()) {
        auto errorDescription = j["description"].get<std::string>();
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'Message': returned error: ", errorDescription);
        return msg;
    }

    j = j["result"];

    if (!j.contains("message_id")) {
        log(__FILE__, ":", __LINE__, ": Error: Failed to parse 'Message': response does not contains 'message_id'");
        return msg;
    }
    msg.id = j["message_id"].get<std::uint64_t>();

    if (!j.contains("from")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response does not contains 'from'");
        return msg;
    }
    auto fromField = j["from"];

    if (!fromField.contains("id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'id'");
        return msg;
    }
    user.id = fromField["id"].get<std::int64_t>();

    if (!fromField.contains("is_bot")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'is_bot'");
        return msg;
    }
    user.isBot = fromField["is_bot"].get<bool>();

    if (!fromField.contains("first_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'first_name'");
        return msg;
    }
    user.firstName = fromField["first_name"].get<std::string>();

    if (!fromField.contains("last_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: In parse 'Message': response::from does not contains 'last_name' ==> !! this is not an error !! <==");
    } else {
        user.lastName = fromField["last_name"].get<std::string>();
    }

    if (!fromField.contains("username")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'username'");
        return msg;
    }
    user.username = fromField["username"].get<std::string>();

    if (!j.contains("chat")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response does not contains 'chat'");
        return msg;
    }
    auto chatField = j["chat"];

    if (!chatField.contains("id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'id'");
        return msg;
    }
    chat.id = chatField["id"].get<std::int64_t>();

    if (!chatField.contains("first_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'first_name'");
        return msg;
    }
    chat.firstName = chatField["first_name"].get<std::string>();

    if (!chatField.contains("username")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'username'");
        return msg;
    }
    chat.username = chatField["username"].get<std::string>();

    if (!chatField.contains("type")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'type'");
        return msg;
    }
    chat.type = chatField["type"].get<std::string>();

    if (!j.contains("date")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response does not contains 'date'");
        return msg;
    }
    msg.date = j["date"].get<std::uint64_t>();

    if (!j.contains("text")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response does not contains 'text'");
        return msg;
    }
    msg.text = j["text"].get<std::string>();
    msg.from = std::make_shared<bot::types::User>(user);
    msg.chat = std::make_shared<bot::types::Chat>(chat);

    return msg;
}
