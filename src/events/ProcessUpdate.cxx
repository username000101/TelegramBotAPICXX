#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::processUpdate(const std::string& json) {
    std::cout << "Process update: " << json << std::endl;
}
