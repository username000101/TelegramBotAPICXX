#pragma once

#include <string>
#include <memory>

#include <types/GenericReactionType.hxx>

namespace telegram {
    namespace bot {
        namespace types {
            class ReactionTypeEmoji : public GenericReactionType {
            public:
                typedef std::shared_ptr<GenericReactionType> Ptr;

                const ReactionType getType() const override { return ReactionType::REACTION_TYPE_EMOJI; }

                std::string type;
                std::string emoji;
            };
        }
    }
}
