#include <net/LongPoll.hxx>

void telegram::bot::LongPoll::longPollStart() {
    auto response = this->bot_.curlInterface_->makeRequest(this->bot_.token_, "getUpdates", {{"offset", std::to_string(this->lastUpdateId_)}, {"limit", std::to_string(this->limit_)}, {"timeout", std::to_string(this->timeout_)}}, nullptr);
    if (response.empty()) {
        log(__FILE__, ":", __LINE__, ": Error: Failed to get update: response is empty");
        return;
    }
    this->bot_.eventsManager_.processUpdate(response);
}
