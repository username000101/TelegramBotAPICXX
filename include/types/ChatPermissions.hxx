#pragma once

#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class ChatPermissions {
            public:
                typedef std::shared_ptr<ChatPermissions> Ptr;

                bool canSendMessages;
                bool canSendAudios;
                bool canSendDocuments;
                bool canSendPhotos;
                bool canSendVideos;
                bool canSendVideoNotes;
                bool canSendPolls;
                bool canSendOtherMessages;
                bool canAddWebPagePreviews;
                bool canChangeInfo;
                bool canInviteUsers;
                bool canPinMessages;
                bool canManageTopics;
            };
        }
    }
}
