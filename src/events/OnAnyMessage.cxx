#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onAnyMessage(MessageListener anyHandler) {

    if (!anyHandler) {
        this->anyMessageHandler_ = nullptr;
        log(__FILE__, ":", __FUNCTION__, ":",  __LINE__, ": Warning: The handler was removed");
    } else {
        this->anyMessageHandler_ = anyHandler;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler was overwrited");
    }
}
