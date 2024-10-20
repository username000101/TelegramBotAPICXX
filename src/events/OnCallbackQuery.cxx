#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::onCallbackQuery(telegram::bot::events::CallbackQueryListener callbackQueryHandler) {
    if (!callbackQueryHandler) {
        this->editedMessageHandler_ = nullptr;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler was removed");
    } else {
        this->callbackQueryHandler_ = callbackQueryHandler;
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler was overwrited");
    }
}
