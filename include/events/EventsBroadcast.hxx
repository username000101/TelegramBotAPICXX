#pragma once

#include <functional>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include <types/CallbackQuery.hxx>
#include <net/ParseResponse.hxx>
#include <types/Message.hxx>
#include <Logger.hxx>

using telegram::internal::logger::log;
using telegram::internal::logger::backgroundColors;
using telegram::internal::logger::foregroundColors;

namespace telegram {
    namespace bot {
        namespace events {
            typedef std::function<void(types::Message::Ptr)> MessageListener;
            typedef std::function<void(types::CallbackQuery::Ptr)> CallbackQueryListener;

            class EventsManager {
            public:
                void onAnyMessage(MessageListener anyMessageHandler);
                void onCommand(const std::string& command, MessageListener commandMessageHandler);
                void onEditedMessage(MessageListener editedMessageHandler);
                void onCallbackQuery(CallbackQueryListener callbackQueryHandler);

                void processUpdate(const std::string& jsonResponse);
            protected:
                MessageListener anyMessageHandler_;
                std::unordered_map<std::string, MessageListener> commandMessageHandlers_;
                MessageListener editedMessageHandler_;
                CallbackQueryListener callbackQueryHandler_;

                friend class BotWrapper;
            };
        }
    }
}
