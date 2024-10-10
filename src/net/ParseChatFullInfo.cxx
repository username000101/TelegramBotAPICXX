#include <net/ParseResponse.hxx>

telegram::bot::types::ChatFullInfo::ChatType getChatType(const std::string& type) {
    if (type == "private")
        return telegram::bot::types::ChatFullInfo::PRIVATE;
    else if (type == "group")
        return telegram::bot::types::ChatFullInfo::GROUP;
    else if (type == "supergroup")
        return telegram::bot::types::ChatFullInfo::SUPERGROUP;
    else if (type == "channel")
        return telegram::bot::types::ChatFullInfo::CHANNEL;
    else {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to get chat type: invalid input(\"" << type << "\")" << std::endl;
#endif
        return telegram::bot::types::ChatFullInfo::PRIVATE;
    }
}

telegram::bot::types::ChatFullInfo telegram::internal::parseChatFullInfo(const std::string& chatFullInfoJSON) {
    nlohmann::json j = nlohmann::json::parse(chatFullInfoJSON);
    bot::types::ChatFullInfo cfi;
    if (!j.contains("ok")) {
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'ok'" << std::endl;
        return cfi;
    }
    if (!j["ok"].get<bool>()) {
        auto errorDescription = j["description"].get<std::string>();
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': returned error: " << errorDescription << std::endl;
        return cfi;
    }

    j = j["result"];

    if (!j.contains("id")) {
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'id'" << std::endl;
        return cfi;
    }
    cfi.id = j["id"].get<std::int64_t>();

    if (!j.contains("first_name")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'first_name'" << std::endl;
#endif
        return cfi;
    }
    cfi.firstName = j["first_name"].get<std::string>();

    if (!j.contains("last_name")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'last_name' ==> !! this is not an error !! <==" << std::endl;
#endif
    } else {
        cfi.lastName = j["last_name"].get<std::string>();
    }

    if (!j.contains("username")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'username'" << std::endl;
#endif
        return cfi;
    }
    cfi.username = j["username"].get<std::string>();

    if (!j.contains("title")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'title' ==> !! this is not an error !! <==" << std::endl;
#endif
    } else {
        cfi.title = j["title"].get<std::string>();
    }

    if (!j.contains("is_forum")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'is_forum' ==> !! this is not an error !! <==" << std::endl;
#endif
    } else {
        cfi.isForum = j["is_forum"].get<bool>();
    }

    if (!j.contains("type")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'type'" << std::endl;
#endif
        return cfi;
    }
    cfi.type = getChatType(j["type"].get<std::string>());

    if (!j.contains("active_usernames")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'active_usernames'" << std::endl;
#endif
        return cfi;
    }
    auto au = j["active_usernames"];
    for (auto& iter : au) {
        cfi.activeUsernames.emplace_back(iter.get<std::string>());
    }

    if (!j.contains("bio")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: Failed to parse 'ChatFullInfo': response does not contains 'bio' ==> !! this is not an error !! <==" << std::endl;
#endif
    } else {
        cfi.bio = j["bio"].get<std::string>();
    }

    if (!j.contains("has_private_forwards")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'has_private_forwards'" << std::endl;
#endif
        return cfi;
    }
    cfi.hasPrivateForwards = j["has_private_forwards"].get<bool>();

    if (!j.contains("birthdate")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse 'ChatFullInfo': response does not contains 'birthdate'" << std::endl;
#endif
        return cfi;
    }
    auto birthdateField = j["birthdate"];
    cfi.birthdate = std::make_shared<bot::types::Birthdate>(internal::parseBirthdate(birthdateField.dump()));

    return cfi;
}
