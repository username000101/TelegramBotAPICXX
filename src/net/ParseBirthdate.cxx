#include <net/ParseResponse.hxx>

telegram::bot::types::Birthdate telegram::internal::parseBirthdate(const std::string& birthdateJSON) {
    nlohmann::json j = nlohmann::json::parse(birthdateJSON);
    bot::types::Birthdate bd;
    if (!j.contains("day")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse birthdate: json response does not contains 'day'" << std::endl;
#endif
        return bd;
    }
    bd.day = j["day"].get<std::uint16_t>();

    if (!j.contains("month")) {
        bd.month = 0;
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to parse birthdate: json response does not contains 'month'" << std::endl;
#endif
        return bd;
    }
    bd.month = j["month"].get<std::uint16_t>();

    if (!j.contains("year")) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Warning: Failed to parse birthdate: json response does not contains 'year' ==> !! this is not an error !! <==" << std::endl;
#endif
        bd.year = 0;
        return bd;
    }
    bd.year = j["year"].get<std::uint32_t>();
    return bd;
}
