#include <net/ParseResponse.hxx>

telegram::bot::types::CallbackQuery telegram::internal::parseCallbackQuery(const std::string& cqueryJSON) {
    nlohmann::json j = nlohmann::json::parse(cqueryJSON);
    bot::types::CallbackQuery cq;

    if (!j.contains("id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'CallbackQuery': response does not contains 'id'");
        return cq;
    }
    cq.id = j["id"].get<std::string>();

    if (!j.contains("message"))
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'CallbackQuery': response does not contains 'message' ==> !! this is not an error !! <==");
    else
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Warning: we can't parse 'message' yet, it will be skipped");

    if (!j.contains("inline_message_id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'CallbackQuery': response does not contains 'inline_message_id' ==> !! this is not an error !! <==");
    } else
        cq.inlineMessageId = j["inline_message_id"].get<std::string>();

    if (!j.contains("chat_instance")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'CallbackQuery': response does not contains 'chat_instance'");
        return cq;
    }
    cq.chatInstance = j["chat_instance"].get<std::string>();

    if (!j.contains("data")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'CallbackQuery': response does not contains 'data' ==> !! this is not an error !! <==");
    } else
        cq.data = j["data"].get<std::string>();

    if (!j.contains("game_short_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'CallbackQuery': response does not contains 'game_short_name' ==> !! this is not an error !! <==");
    } else
        cq.gameShortName = j["game_short_name"].get<std::string>();

    if (j.contains("from"))
        cq.from = std::make_shared<bot::types::User>(internal::parseUser(j["from"].dump()));

    return cq;
}
