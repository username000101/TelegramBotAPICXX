#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::processUpdate(const std::string& json) {
    if (json.empty()) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process update: json is empty");
        return;
    }
}
