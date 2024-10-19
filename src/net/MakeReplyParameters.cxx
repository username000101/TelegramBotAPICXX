#include <net/MakeType.hxx>

std::string telegram::internal::makeReplyParameters(bot::types::ReplyParameters::Ptr rp) {
    if (!rp) {
        log(__FILE__, ":", __FUNCTION__, ":", __LINE__, ": Error: Failed to make ReplyParameters: rp ptr is invalid");
        return "";
    }

    nlohmann::json j;
    j["message_id"] = rp->messageId;
    j["chat_id"] = rp->chatId;

    return j.dump();
}
