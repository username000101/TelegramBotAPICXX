#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::processUpdate(const std::string& json) {
    if (json.empty()) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process update: json is empty");
        return;
    }

    nlohmann::json j = nlohmann::json::parse(json);
    j = j["result"];
    for (auto& resultField : j) {
        if (resultField.contains("message")) {
            auto message = std::make_shared<types::Message>(internal::parseMessage(resultField["message"].dump()));
            if (message->text.starts_with('/')) {
                for (auto& handler : this->commandMessageHandlers_) {
                    if (message->text == handler.second.first) {
                        handler.second.second(message);
                        return;
                    }
                }
                log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler for command '", message->text, "' does not exists");
                return;
            } else {
                for (auto& handler : this->anyMessageHandlers_) {
                    handler.second(message);
                    return;
                }
            }
        } else {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: TelegramBotAPICXX does not support handle the non-message updates yet");
            return;
        }
    }

}
