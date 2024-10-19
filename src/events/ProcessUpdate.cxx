#include <events/EventsBroadcast.hxx>

void telegram::bot::events::EventsManager::processUpdate(const std::string& json) {
    if (json.empty()) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process update: json is empty");
        return;
    }

    nlohmann::json j = nlohmann::json::parse(json);
    if (!j["ok"].get<bool>()) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to process update: ok != true");
        return;
    }

    j = j["result"];
    for (auto& resultField : j) {
        if (resultField.contains("message")) {
            auto message = std::make_shared<types::Message>(internal::parseMessage(resultField["message"].dump()));
            if (message->text.starts_with('/')) /* Command */ {
                for (auto& handler : this->commandMessageHandlers_) {
                    if (message->text == handler.first) {
                        handler.second(message);
                        return;
                    }
                }
                log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: The handler for command '", message->text, "' does not exists");
                return;
            } else /* Any message */ {
                this->anyMessageHandler_(message);
            }
        } else {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: TelegramBotAPICXX does not support handle the non-message updates yet");
            return;
        }
    }

}
