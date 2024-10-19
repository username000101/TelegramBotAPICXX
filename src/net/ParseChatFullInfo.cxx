#include <net/ParseResponse.hxx>

telegram::bot::types::ChatFullInfo telegram::internal::parseChatFullInfo(const std::string& chatFullInfoJSON) {
    nlohmann::json j = nlohmann::json::parse(chatFullInfoJSON);
    bot::types::ChatFullInfo cfi;
    if (!j.contains("ok")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'ok'");
        return cfi;
    }
    if (!j["ok"].get<bool>()) {
        auto errorDescription = j["description"].get<std::string>();
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': returned error: " , errorDescription);
        return cfi;
    }

    j = j["result"];

    if (!j.contains("id")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'id'");
        return cfi;
    }
    cfi.id = j["id"].get<std::int64_t>();

    if (!j.contains("first_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'first_name'");
        return cfi;
    }
    cfi.firstName = j["first_name"].get<std::string>();

    if (!j.contains("last_name")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'last_name' ==> !! this is not an error !! <==");
    } else {
        cfi.lastName = j["last_name"].get<std::string>();
    }

    if (!j.contains("username")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'username'");
        return cfi;
    }
    cfi.username = j["username"].get<std::string>();

    if (!j.contains("title")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'title' ==> !! this is not an error !! <==");
    } else {
        cfi.title = j["title"].get<std::string>();
    }

    if (!j.contains("is_forum")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'is_forum' ==> !! this is not an error !! <==");
    } else {
        cfi.isForum = j["is_forum"].get<bool>();
    }

    if (!j.contains("type")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'type'");
        return cfi;
    }
    cfi.type = j["type"].get<std::string>();

    if (!j.contains("active_usernames")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'active_usernames'");
        return cfi;
    }
    auto au = j["active_usernames"];
    for (auto& iter : au) {
        cfi.activeUsernames.emplace_back(iter.get<std::string>());
    }

    if (!j.contains("bio")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'bio' ==> !! this is not an error !! <==");
    } else {
        cfi.bio = j["bio"].get<std::string>();
    }

    if (!j.contains("has_private_forwards")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'has_private_forwards'");
        return cfi;
    }
    cfi.hasPrivateForwards = j["has_private_forwards"].get<bool>();

    if (!j.contains("birthdate")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse 'ChatFullInfo': response does not contains 'birthdate'");
        return cfi;
    }
    auto birthdateField = j["birthdate"];
    cfi.birthdate = std::make_shared<bot::types::Birthdate>(internal::parseBirthdate(birthdateField.dump()));

    return cfi;
}
