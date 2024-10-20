#pragma once

#include <filesystem>
#include <memory>

namespace telegram {
    namespace bot {
        namespace types {
            class File {
            public:
                typedef std::shared_ptr<File> Ptr;

                std::filesystem::path file;
                std::string mimeType;
            };
        }
    }
}
