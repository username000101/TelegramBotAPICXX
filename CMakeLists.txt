cmake_minimum_required(VERSION 3.14)

project(MeetXTelegramAPI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(CURL REQUIRED)

include_directories(include)
include_directories(thirdParty/json/include)

add_subdirectory(thirdParty/json)

add_executable(MeetXTelegramAPI
    include/net/CURLInteraction.hxx
    src/net/CURLInteraction.cxx

    include/types/ChatPhoto.hxx

    include/types/User.hxx

    include/types/Message.hxx

    include/types/Chat.hxx

    include/types/ChatFullInfo.hxx

    include/types/Birthdate.hxx

    include/types/BusinessIntro.hxx
    include/net/ParseResponse.hxx
    src/net/ParseBirthdate.cxx
    src/net/ParseChatFullInfo.cxx
    include/BotWrapper.hxx
    src/methods/GetChat.cxx
    src/methods/SendMessage.cxx
    src/net/ParseMessage.cxx
    include/types/GenericMarkup.hxx
    include/types/InlineKeyboardMarkup.hxx
    include/types/InlineKeyboardButton.hxx
    src/net/MakeInlineKeyboardMarkup.cxx
    include/net/MakeType.hxx
    include/types/ChatLocation.hxx
    include/types/Location.hxx
    include/types/GenericReactionType.hxx
    include/types/ReactionTypeEmoji.hxx
    include/types/ChatPermissions.hxx
    include/types/BusinessLocation.hxx
    include/types/BusinessOpeningHoursInterval.hxx
    include/types/BusinessOpeningHours.hxx
)

if (DEFINED logging OR DEFINED LOGGING)
    message("Logging for MeetxTelegramAPI enabled")
    target_compile_definitions(MeetXTelegramAPI PUBLIC
        MEETX_TELEGRAM_API_ENABLE_LOGGING
    )
endif()

target_compile_definitions(MeetXTelegramAPI PUBLIC
    MEETX_TELEGRAM_API_PROVIDED_VERSION=0
    MEETX_TELEGRAM_API_LIBRARY_VERSION_MAJOR=1
    MEETX_TELEGRAM_API_LIBRARY_VERSION_MINOR=0
)

target_link_libraries(MeetXTelegramAPI PRIVATE ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)
