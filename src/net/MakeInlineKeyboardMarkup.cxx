#include <net/MakeType.hxx>

std::string telegram::internal::makeInlineKeyboardMarkup(telegram::bot::types::InlineKeyboardMarkup::Ptr keyboardMarkup) {
    if (!keyboardMarkup) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make ReplyParameters: keyboardMarkup ptr is invalid");
        return "";
    }

    nlohmann::json inlineKeyboard;
    inlineKeyboard["inline_keyboard"] = nlohmann::json::array();
    std::uint16_t arrayIndex = 0;
    std::uint16_t buttonIndex = 0;
    for (auto& buttons : keyboardMarkup->inlineKeyboard) {
        inlineKeyboard["inline_keyboard"].push_back(nlohmann::json::array());
        for (auto& lineButton : buttons) {
            if (!lineButton) {
                log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make InlineKeyboardButton: lineButton ptr is invalid");
                continue;
            }
            nlohmann::json button;
            button["text"] = lineButton->text;
            button["callback_data"] = lineButton->callbackData;
            button["pay"] = lineButton->pay;
            button["url"] = lineButton->url;

            inlineKeyboard["inline_keyboard"][arrayIndex].push_back(button);

        }
        ++arrayIndex;
    }
    return inlineKeyboard.dump();
}
