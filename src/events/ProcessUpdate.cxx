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
        if (resultField.contains("message")) /* New message*/ {
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
                if (this->anyMessageHandler_)
                    this->anyMessageHandler_(message);
                return;
            }
        } else if (resultField.contains("edited_message")) /* Edited message */ {
            auto message = std::make_shared<types::Message>(internal::parseMessage(resultField["edited_message"].dump()));
            if (this->editedMessageHandler_)
                this->editedMessageHandler_(message);

            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: TelegramBotAPICXX does not support handle the edited_message updates yet");
            return;
        } else if (resultField.contains("channel_post")) /* Channel post */ {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: TelegramBotAPICXX does not support handle the channel_post updates yet");
            return;
        } else if (resultField.contains("edited_channel_post")) /* Edited channel post */ {
            log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Warning: TelegramBotAPICXX does not support handle the edited_channel_post updates yet");
            return;
        }
        // ...
    }

}
