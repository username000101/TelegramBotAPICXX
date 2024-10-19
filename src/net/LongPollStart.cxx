#include <net/LongPoll.hxx>

void telegram::bot::LongPoll::longPollStart() {
    auto response = this->bot_.curlInterface_->makeRequest(this->bot_.token_, "getUpdates", {{"offset", std::to_string(this->lastUpdateId_)}, {"limit", std::to_string(this->limit_)}, {"timeout", std::to_string(this->timeout_)}}, nullptr);
    if (response.empty()) {
        log(__FILE__, ":", __LINE__, ": Error: Failed to get updates: response is empty");
        return;
    }
    this->bot_.eventsManager_.processUpdate(response);

    nlohmann::json j = nlohmann::json::parse(response);
    if (!j["ok"].get<bool>()) {
        log(__FILE__, ":", __LINE__, ": Error: Failed to get updates: TelegramBotAPI error");
        return;
    }
    auto lastUpdate = j["result"].back();
    log("Last update id is: ", lastUpdate["update_id"].get<std::uint64_t>());
    this->lastUpdateId_ = lastUpdate["update_id"].get<std::uint64_t>();
}
