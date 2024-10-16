#include <net/MakeType.hxx>

std::string telegram::internal::makeReplyParameters(bot::types::ReplyParameters::Ptr rp) {
    if (!rp) {
#ifdef MEETX_TELEGRAM_API_ENABLE_LOGGING
        std::cout << "TelegramBotAPI: " << __FILE__ << ":" << __LINE__ << ": Error: Failed to make ReplyParameters: rp ptr is invalid" << std::endl;
#endif
        return "";
    }

    nlohmann::json j;
    j["message_id"] = rp->messageId;
    j["chat_id"] = rp->chatId;

    return j.dump();
}
