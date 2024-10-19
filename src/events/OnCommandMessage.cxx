#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onCommand(const std::string& command, MessageListener commandHandler) {
    if (!commandHandler) {
        this->commandMessageHandlers_.erase(command);
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler for command \"", command, "\" was removed");
    } else {
        this->commandMessageHandlers_[command] = commandHandler;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler for command \"", command, "\" was overwrited");
    }
}
