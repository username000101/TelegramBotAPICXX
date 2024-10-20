#include <net/ParseResponse.hxx>

telegram::bot::types::User telegram::internal::parseUser(const std::string& userJSON) {
    bot::types::User user;
    nlohmann::json j = nlohmann::json::parse(userJSON);

    if (!j.contains("id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'id'");
        return user;
    }
    user.id = j["id"].get<std::int64_t>();

    if (!j.contains("is_bot")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'is_bot'");
        return user;
    }
    user.isBot = j["is_bot"].get<bool>();

    if (!j.contains("first_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'first_name'");
        return user;
    }
    user.firstName = j["first_name"].get<std::string>();

    if (!j.contains("last_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: In parse 'Message': response::from does not contains 'last_name' ==> !! this is not an error !! <==");
    } else {
        user.lastName = j["last_name"].get<std::string>();
    }

    if (!j.contains("username")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response::from does not contains 'username'");
        return user;
    }
    user.username = j["username"].get<std::string>();

    if (!j.contains("chat")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: failed to parse 'Message': response does not contains 'chat'");
        return user;
    }

    return user;
}
