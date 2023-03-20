# Usage:
# FIND_PACKAGE(jsoncpp REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name jsoncpp)

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

if (NOT jsoncpp_FOUND)
    INCLUDE(FetchContent)

    FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
        GIT_TAG master
        )
    FetchContent_GetProperties(jsoncpp)
    if (NOT jsoncpp_POPULATED)
        FetchContent_Populate(jsoncpp)
        ADD_SUBDIRECTORY(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR})
        message(${jsoncpp_SOURCE_DIR})
        message(${jsoncpp_BINARY_DIR})
        SET(jsoncpp_FOUND TRUE)
    endif()
endif()
