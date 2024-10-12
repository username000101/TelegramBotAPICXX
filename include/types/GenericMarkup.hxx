#pragma once

#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            enum MarkupType {
                INLINE_KEYBOARD_MARKUP,
                REPLY_KEYBOARD_MARKUP,
                REPLY_KEYBOARD_REMOVE,
                FORCE_REPLY,
                GENERIC_REPLY,
            };

            class GenericMarkup {
            public:
                typedef std::shared_ptr<GenericMarkup> Ptr;

                virtual ~GenericMarkup() {};

                virtual const MarkupType getType() const { return MarkupType::GENERIC_REPLY; };
            };
        }
    }
}
