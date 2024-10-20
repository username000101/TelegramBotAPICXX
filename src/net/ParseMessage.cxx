#include <net/ParseResponse.hxx>

telegram::bot::types::Message telegram::internal::parseMessage(const std::string& messageJSON) {
    nlohmann::json j = nlohmann::json::parse(messageJSON);
    bot::types::Message msg;

    if (!j.contains("message_id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'Message': response does not contains 'message_id'");
        return msg;
    }
    msg.id = j["message_id"].get<std::uint64_t>();

    if (!j.contains("from")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response does not contains 'from'");
        return msg;
    }

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
    if (j.contains("from"))
        msg.from = std::make_shared<bot::types::User>(parseUser(j["from"].dump()));
    if (j.contains("chat"))
        msg.chat = std::make_shared<bot::types::Chat>(parseChat(j["chat"].dump()));

    return msg;
}
