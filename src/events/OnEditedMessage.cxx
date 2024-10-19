#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onEditedMessage(std::uint16_t handlerId, MessageListener editedMessageHandler) {
    if (this->editedMessageHandlers_.count(handlerId) > 0) {

        if (!editedMessageHandler) {
            this->editedMessageHandlers_.erase(handlerId);
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " was removed");
        } else {
            this->editedMessageHandlers_.at(handlerId) = editedMessageHandler;
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " was overwrited");
        }
    } else {
        if (!editedMessageHandler) {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler with id ", handlerId, " cannon be created: handler is nullptr");
        } else {
            this->anyMessageHandlers_[handlerId] = editedMessageHandler;
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Info: Added the new handler with id ", handlerId);
        }
    }
}
