#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onAnyMessage(std::uint16_t handlerId, MessageListener anyHandler) {
    if (this->anyMessageHandlers_.count(handlerId) > 0) {

        if (!anyHandler) {
            this->anyMessageHandlers_.erase(handlerId);
            log(__FILE__, ":", __FUNCTION__, ":",  __LINE__, ": Warning: The handler with id ", handlerId, " was removed");
        } else {
            this->anyMessageHandlers_.at(handlerId) = anyHandler;
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " was overwrited");
        }
    } else {
        if (!anyHandler) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " cannon be created: handler is nullptr");
        } else {
            this->anyMessageHandlers_[handlerId] = anyHandler;
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: Added the new handler with id ", handlerId);
        }
    }
}
