#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onCommand(std::uint16_t handlerId, const std::string& command, MessageListener commandHandler) {
    if (this->commandMessageHandlers_.count(handlerId) > 0) {
        if (!commandHandler) {
            this->commandMessageHandlers_.erase(handlerId);
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " was removed");
        } else {
            this->commandMessageHandlers_[handlerId] = std::make_pair(command, commandHandler);
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " was overwrited");
        }
    } else {
        if (!commandHandler) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: cannon be created: handler is nullptr");
        } else {
            this->commandMessageHandlers_[handlerId] = std::make_pair(command, commandHandler);
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: Added the new handler with id ", handlerId);
        }
    }
}
