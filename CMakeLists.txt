cmake_minimum_required(VERSION 3.10)

project(nextclientapi_amxx)

include(cmake/Dependencies.cmake)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    set(NAPI_TARGET_PROPS
            SUFFIX "_i386.so"
            COMPILE_FLAGS "-m32"
            LINK_FLAGS "-m32 -static-libstdc++ -static-libgcc -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/version.version"
            LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/version.version
    )

    set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
endif ()

find_package(Threads REQUIRED)
add_subdirectory(deps/cssdk)
add_subdirectory(deps/metamod)
add_subdirectory(deps/openssl)
add_subdirectory(deps/rsa_keygen)
add_subdirectory(deps/easyloggingpp)

add_library(${PROJECT_NAME} SHARED
        src/main.cpp
        src/rehlds_api_provider.h
        src/rehlds_api_provider.cpp
        src/elpplog.h
        src/elpplog.cpp
        src/AmxContextGuard.cpp
        src/AmxContextGuard.h
        src/api_access.h
        src/module_types.h

        src/utils/SizeBufWriter.h
        src/utils/SizeBufWriter.cpp
        src/utils/utilfuncs.h
        src/utils/utilfuncs.cpp
        src/utils/string_utils.h

        src/amxxmodule/moduleconfig.h
        src/amxxmodule/amxxmodule.h
        src/amxxmodule/amxxmodule.cpp

        src/natives/cvar_sandbox.cpp
        src/natives/death_notice_wpn_icon.cpp
        src/natives/hud_sprite.cpp
        src/natives/miscellaneous.cpp
        src/natives/private_precache.cpp
        src/natives/viewmodelfx.cpp
        src/natives/nextclient.cpp
        src/natives/natives.h
        src/natives/natives.cpp

        src/services/game_events/GameEventsManager.h
        src/services/game_events/GameEventsManager.cpp
        src/services/game_events/game_events.h
        src/services/game_events/game_events.cpp
        src/services/game_events/events.h
        src/services/nclm_protocol/NclmProtocol.h
        src/services/nclm_protocol/NclmProtocol.cpp
        src/services/nclm_protocol/NclmSizeBufWriter.h
        src/services/nclm_protocol/NclmSizeBufWriter.cpp
        src/services/nclm_protocol/Verifier.h
        src/services/nclm_protocol/Verifier.cpp
        src/services/nclm_protocol/rehlds_events.h
        src/services/nclm_protocol/rehlds_events.cpp
        src/services/nclm_protocol/nclm_proto.h
        src/services/nclm_protocol/events.h
        src/services/CvarSandbox.h
        src/services/CvarSandbox.cpp
        src/services/PrivatePrecache.h
        src/services/PrivatePrecache.cpp
        src/services/ViewmodelFX.h
        src/services/ViewmodelFX.cpp
        src/services/HealthNext.h
        src/services/HealthNext.cpp
        src/services/NextClientApi.h
        src/services/NextClientApi.cpp
        src/services/NextClientVersion.cpp
        src/services/DeathMsgWpnIcon.h
        src/services/DeathMsgWpnIcon.cpp
        src/services/HudSprite.h
        src/services/HudSprite.cpp
        src/services/Miscellaneous.h
        src/services/Miscellaneous.cpp
        src/services/INextClientInfo.h
        src/services/INextClientAPI.h
        src/services/IDeprecatedAPI.h
        src/services/NextClientVersion.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
        #amxx options
        HAVE_STDINT_H
        NO_MSVC8_AUTO_COMPAT
        #easyloggingpp options
        ELPP_THREAD_SAFE
        ELPP_DISABLE_DEFAULT_CRASH_HANDLING
)

target_include_directories(${PROJECT_NAME} PUBLIC
        src/amxxmodule
        src
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        ${NAPI_TARGET_PROPS}
)

target_link_libraries(${PROJECT_NAME}
        metamod_sdk::metamod_sdk
        openssl::openssl
        cssdk::cssdk
        Pal::Sigslot
        kangaru::kangaru
        easyloggingpp::easyloggingpp
        magic_enum::magic_enum
)

# custom build targets
add_custom_target(BUILD_ALL ALL)
add_dependencies(BUILD_ALL nextclientapi_amxx)

if(DEFINED ENV{nextclientapi_amxx_COPY_TO_PATH})
    add_custom_target(INSTALL_ALL
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:nextclientapi_amxx> $ENV{nextclientapi_amxx_COPY_TO_PATH})
else()
    add_custom_target(INSTALL_ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Warning: nextclientapi_amxx_COPY_TO_PATH environment variable is not set, skipping copy")
endif()

add_custom_target(BUILD_AND_INSTALL_ALL ALL)
add_dependencies(BUILD_AND_INSTALL_ALL BUILD_ALL)
add_dependencies(BUILD_AND_INSTALL_ALL INSTALL_ALL)
