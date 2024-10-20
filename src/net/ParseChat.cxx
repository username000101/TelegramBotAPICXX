#include <net/ParseResponse.hxx>

telegram::bot::types::Chat telegram::internal::parseChat(const std::string& chatJSON) {
    bot::types::Chat chat;

    nlohmann::json j = nlohmann::json::parse(chatJSON);

    if (!j.contains("id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'id'");
        return chat;
    }
    chat.id = j["id"].get<std::int64_t>();

    if (!j.contains("first_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'first_name'");
        return chat;
    }
    chat.firstName = j["first_name"].get<std::string>();

    if (!j.contains("username")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'username'");
        return chat;
    }
    chat.username = j["username"].get<std::string>();

    if (!j.contains("type")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::chat does not contains 'type'");
        return chat;
    }
    chat.type = j["type"].get<std::string>();

    return chat;
}
