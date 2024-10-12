#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include <types/Birthdate.hxx>
#include <types/BusinessIntro.hxx>
#include <types/ChatPhoto.hxx>
#include <types/Chat.hxx>
#include <types/ChatLocation.hxx>
#include <types/ChatPermissions.hxx>
#include <types/GenericReactionType.hxx>
#include <types/Message.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class ChatFullInfo {
            public:
                typedef std::shared_ptr<ChatFullInfo> Ptr;

                enum ChatType { PRIVATE, GROUP, SUPERGROUP, CHANNEL, };

                std::int64_t linkedChatId;
                std::int64_t id; 
                std::uint32_t slowModeDelay;
                std::uint32_t unrestrictBoostCount;
                std::uint32_t messageAutoDeleteTime;
                std::uint32_t profileAccentColorId;
                std::uint32_t accentColorId;
                std::uint16_t maxReactionsCount;
                ChatType type;
                std::string title;
                std::string username;
                std::string firstName;
                std::string lastName;
                std::string bio;
                bool isForum;
                bool hasPrivateForwards;
                std::vector<std::string> activeUsernames;
                ChatPhoto::Ptr photo;
                Birthdate::Ptr birthdate;
                Chat::Ptr personalChat;
                BusinessIntro::Ptr businessIntro;
                ChatLocation::Ptr chatLocation;
                ChatPermissions::Ptr permissions;
                std::vector<GenericReactionType::Ptr> availableReactions;
                std::string backgroundCustomEmojiId;
                std::string profileBackgroundCustomEmojiId;
                bool hasRestrictedVoiceAndVideoMessages;
                bool joinToSendMessages;
                bool joinByRequest;
                std::string description;
                std::string inviteLink;
                Message::Ptr pinnedMessage;
                bool canSendPaidMedia;
                bool hasAgressiveAniSpamEnabled;
                bool hasHiddenMembers;
                bool hasProtectContent;
                bool hasVisibleHistory;
                std::string strickerSetName;
                bool canSetStickerSet;
                std::string customEmojiSetName;

            };
        }
    }
}
