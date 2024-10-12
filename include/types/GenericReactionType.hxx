#pragma once

#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            enum ReactionType {
                GENERIC_REACTION_TYPE,
                REACTION_TYPE_EMOJI,
                REACTION_TYPE_CUSTOM_EMOJI,
                REACTION_TYPE_PAID,
            };

            class GenericReactionType {
            public:
                typedef std::shared_ptr<GenericReactionType> Ptr;

                virtual ~GenericReactionType() {};

                virtual const ReactionType getType() const { return ReactionType::GENERIC_REACTION_TYPE; }
            };
        }
    }
}
