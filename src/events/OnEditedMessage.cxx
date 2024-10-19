#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onEditedMessage(MessageListener editedMessageHandler) {
    if (!editedMessageHandler) {
        this->editedMessageHandler_ = nullptr;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler was removed");
    } else {
        this->editedMessageHandler_ = editedMessageHandler;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler was overwrited");
    }
}
