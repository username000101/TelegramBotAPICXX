#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include <variant>

#include <types/Message.hxx>

#include <Logger.hxx>

using telegram::internal::logger::log;
using telegram::internal::logger::backgroundColors;
using telegram::internal::logger::foregroundColors;

namespace telegram {
    namespace bot {
        namespace events {
            typedef std::function<void(types::Message::Ptr)> MessageListener;

            class EventsManager {
            public:
                void onAnyMessage(std::uint16_t handlerId, MessageListener anyMessageHandler);
                void onCommand(std::uint16_t handlerId, const std::string& command, MessageListener commandMessageHandler);
                void onEditedMessage(std::uint16_t handlerId, MessageListener editedMessageHandler);

                void processUpdate(const std::string& jsonResponse);
            private:
                enum class NotifyModificator { ANY, COMMAND, EDIT, CALLBACKQ, INLINEQ, SHIPPINGQ, CMEMBER, CJOINGREQ, CBOOST, CBOOSTRM, };


                void notify(NotifyModificator whoNotify, std::variant<MessageListener, int> notify);

                void notify__any(MessageListener message);
                void notify__command(MessageListener message);
                void notify__edit(MessageListener message);

                [[deprecated("Not implemented now!")]] void notify__callbackq(...);

                std::unordered_map<std::uint16_t, MessageListener> anyMessageHandlers_;
                std::unordered_map<std::uint16_t, std::pair<std::string, MessageListener>> commandMessageHandlers_;
                std::unordered_map<std::uint16_t, MessageListener> editedMessageHandlers_;
            };
        }
    }
}
