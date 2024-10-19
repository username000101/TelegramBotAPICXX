#include <net/ParseResponse.hxx>

telegram::bot::types::Birthdate telegram::internal::parseBirthdate(const std::string& birthdateJSON) {
    nlohmann::json j = nlohmann::json::parse(birthdateJSON);
    bot::types::Birthdate bd;
    if (!j.contains("day")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse birthdate: json response does not contains 'day'");
        return bd;
    }
    bd.day = j["day"].get<std::uint16_t>();

    if (!j.contains("month")) {
        bd.month = 0;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to parse birthdate: json response does not contains 'month'");
        return bd;
    }
    bd.month = j["month"].get<std::uint16_t>();

    if (!j.contains("year")) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: Failed to parse birthdate: json response does not contains 'year' ==> !! this is not an error !! <==");
        bd.year = 0;
        return bd;
    }
    bd.year = j["year"].get<std::uint32_t>();
    return bd;
}
