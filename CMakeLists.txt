cmake_minimum_required(VERSION 3.16)

project(nextclientapi_amxx VERSION 1.6.0)

include(cmake/Dependencies.cmake)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    set(NAPI_TARGET_PROPS
            SUFFIX "_i386.so"
            COMPILE_FLAGS "-m32 -Wa,--noexecstack"
            LINK_FLAGS "-m32 -static-libstdc++ -static-libgcc -Wl,-z,noexecstack -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/version.version"
            LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/version.version
    )

    set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
endif ()

###
### AMXX module info
###

set(AMXX_MODULE_NAME       "Next Client API")
set(AMXX_MODULE_VERSION    "${PROJECT_VERSION}")
set(AMXX_MODULE_AUTHOR     "Next21 Team")
set(AMXX_MODULE_URL        "https://github.com/CS-NextClient/NextClientServerApi")
set(AMXX_MODULE_LIBRARY    "nextclientapi")
set(AMXX_MODULE_LOG_TAG    "nclapi")

# Use Metamod SDK (ON/OFF)
set(AMXX_USE_METAMOD ON)

# Reload module on map change (AMXX_USE_METAMOD should be OFF) "true" / "false"
set(AMXX_MODULE_RELOAD_ON_MAP_CHANGE "false")

# Compatibility with AMXX v1.8.2 (ON/OFF)
set(AMXX_182_COMPATIBILITY OFF)

# Uncomment the functions you want to use in your code and specify the desired function names
set(AMXX_QUERY "Main")                                 # void OnAmxxQuery();
set(AMXX_ATTACH "OnAmxxAttach")                        # AmxxStatus OnAmxxAttach();
set(AMXX_DETACH "OnAmxxDetach")                        # void OnAmxxDetach();
set(AMXX_PLUGINS_LOADED "OnAmxxPluginsLoaded")         # void OnAmxxPluginsLoaded();

###
### Metamod module info
###

set(META_PLUGIN_NAME "${AMXX_MODULE_NAME}")
set(META_PLUGIN_VERSION "${AMXX_MODULE_VERSION}")
set(META_PLUGIN_AUTHOR "${AMXX_MODULE_AUTHOR}")
set(META_PLUGIN_LOG_TAG "${AMXX_MODULE_LOG_TAG}")
set(META_PLUGIN_URL "${AMXX_MODULE_URL}")

# Flags for plug-in to indicate when it can be loaded/unloaded
#   "Never"
#   "Startup"     - Should only be loaded/unloaded at initial HLDS execution
#   "ChangeLevel" - Can be loaded/unloaded between maps
#   "AnyPause"    - Can be loaded/unloaded at any time, and can be "paused" during a map.
#   "AnyTime"     - Can be loaded/unloaded at any time
set(META_PLUGIN_LOADABLE "AnyTime")
set(META_PLUGIN_UNLOADABLE "AnyTime")

set(META_DETACH "OnMetaDetach")    # void OnMetaDetach();

find_package(Threads REQUIRED)
add_subdirectory(deps/goldsrc/metamod)
add_subdirectory(deps/goldsrc/cssdk)
add_subdirectory(deps/goldsrc/amxmodx)
add_subdirectory(deps/goldsrc/core)
add_subdirectory(deps/goldsrc/mhooks)
add_subdirectory(deps/openssl)
add_subdirectory(deps/rsa_keygen)
add_subdirectory(deps/easyloggingpp)

add_library(${PROJECT_NAME} SHARED
        src/main.cpp
        src/elpplog.h
        src/elpplog.cpp
        src/AmxContextGuard.cpp
        src/AmxContextGuard.h
        src/api_access.h
        src/module_types.h

        src/utils/UserMessageLimits.h
        src/utils/SizeBufWriter.h
        src/utils/SizeBufWriter.cpp
        src/utils/utilfuncs.h
        src/utils/utilfuncs.cpp
        src/utils/msg_ex.h
        src/utils/msg_ex.cpp
        src/utils/string_utils.h

        src/natives/cvar_sandbox.cpp
        src/natives/material.cpp
        src/natives/death_notice_wpn_icon.cpp
        src/natives/hud_sprite.cpp
        src/natives/miscellaneous.cpp
        src/natives/private_precache.cpp
        src/natives/viewmodelfx.cpp
        src/natives/nextclient.cpp
        src/natives/natives.h
        src/natives/natives.cpp
        src/natives/hwid.cpp
        src/natives/weapon_sound_override.cpp

        src/services/server_events/ServerEventsManager.h
        src/services/server_events/ServerEventsManager.cpp
        src/services/server_events/server_events.h
        src/services/server_events/server_events.cpp
        src/services/server_events/events.h
        src/services/mod_events/ModEventsManager.h
        src/services/mod_events/ModEventsManager.cpp
        src/services/mod_events/mod_events.h
        src/services/mod_events/mod_events.cpp
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
        src/services/ncl_entities/EntitySync.h
        src/services/ncl_entities/EntitySync.cpp
        src/services/ncl_entities/EntitySyncPackets.cpp
        src/services/ncl_entities/PlayerEntitySync.h
        src/services/ncl_entities/PlayerEntitySync.cpp
        src/services/ncl_entities/WeaponEntitySync.h
        src/services/ncl_entities/WeaponEntitySync.cpp
        src/services/ncl_entities/MaterialEntitySync.h
        src/services/ncl_entities/MaterialEntitySync.cpp
        src/services/StringRegistry.h
        src/services/StringRegistry.cpp
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
        src/services/NextClientVersion.h
        src/services/mod_events/events.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
        #easyloggingpp options
        ELPP_THREAD_SAFE
        ELPP_DISABLE_DEFAULT_CRASH_HANDLING
        $<$<NOT:$<CONFIG:Debug>>:ELPP_DISABLE_DEBUG_LOGS>
)

target_include_directories(${PROJECT_NAME} PUBLIC
        src/amxxmodule
        src
        include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        ${NAPI_TARGET_PROPS}
)

target_link_libraries(${PROJECT_NAME}
        amxx
        metamod
        cssdk
        mhooks
        core
        openssl::openssl
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

option(NEXTCLIENTAPI_BUILD_TESTS "Build engine-free server policy tests" OFF)
set(NEXTCLIENTAPI_PAWN_COMPILER "" CACHE FILEPATH "AMX Mod X compiler for the optional Pawn plugin test")
set(NEXTCLIENTAPI_PAWN_INCLUDE_DIR "" CACHE PATH "AMX Mod X and ReAPI include directory for the Pawn plugin test")
if (NEXTCLIENTAPI_BUILD_TESTS)
    enable_testing()
    if (NEXTCLIENTAPI_PAWN_COMPILER AND NEXTCLIENTAPI_PAWN_INCLUDE_DIR)
        add_test(NAME pawn-material-plugin COMMAND ${CMAKE_COMMAND}
                "-DPAWN_COMPILER=${NEXTCLIENTAPI_PAWN_COMPILER}"
                "-DPAWN_INCLUDE_DIR=${NEXTCLIENTAPI_PAWN_INCLUDE_DIR}"
                "-DAPI_INCLUDE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/addons/amxmodx/scripting/include"
                "-DPAWN_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/amxx_test/addons/amxmodx/scripting/test_nextclient_api.sma"
                "-DPAWN_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/test_nextclient_api.amxx"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/VerifyPawnPlugin.cmake")
    elseif (NEXTCLIENTAPI_PAWN_COMPILER OR NEXTCLIENTAPI_PAWN_INCLUDE_DIR)
        message(FATAL_ERROR "Set both NEXTCLIENTAPI_PAWN_COMPILER and NEXTCLIENTAPI_PAWN_INCLUDE_DIR for Pawn verification")
    endif ()

    add_executable(material-visibility-tests tests/MaterialVisibilityPolicyTests.cpp)
    target_include_directories(material-visibility-tests PRIVATE src)
    add_test(NAME material-visibility-policy COMMAND material-visibility-tests)

    add_executable(entity-sync-packets-tests
            tests/EntitySyncPacketsTests.cpp
            src/services/ncl_entities/EntitySyncPackets.cpp)
    target_include_directories(entity-sync-packets-tests PRIVATE src include)
    add_test(NAME entity-sync-packets COMMAND entity-sync-packets-tests)

    add_executable(material-entity-sync-tests
            tests/MaterialEntitySyncTests.cpp
            src/AmxContextGuard.cpp
            src/services/NextClientVersion.cpp
            src/services/StringRegistry.cpp
            src/services/ncl_entities/EntitySync.cpp
            src/services/ncl_entities/EntitySyncPackets.cpp
            src/services/ncl_entities/MaterialEntitySync.cpp)
    target_include_directories(material-entity-sync-tests PRIVATE
            tests/fakes src include deps/openssl/include
            deps/goldsrc/core/include deps/goldsrc/cssdk/include
            deps/goldsrc/metamod/include deps/goldsrc/amxmodx/include)
    target_compile_definitions(material-entity-sync-tests PRIVATE
            HAS_CSSDK_LIB HAS_METAMOD_LIB HAS_MHOOKS_LIB HAS_AMXX_LIB USE_METAMOD NOMINMAX _CRT_SECURE_NO_WARNINGS
            ELPP_THREAD_SAFE ELPP_DISABLE_DEFAULT_CRASH_HANDLING ELPP_NO_DEFAULT_LOG_FILE)
    target_link_libraries(material-entity-sync-tests PRIVATE Pal::Sigslot kangaru::kangaru easyloggingpp::easyloggingpp)
    foreach (scenario IN ITEMS repeated-preset-snapshot recipient-routing recipient-compatibility native-float-cells
            invalid-index registration-boundary binding-admission parameter-admission
            stale-unbind unbind-admission sync-identity same-identity reuse-before-bind reuse-before-param reuse-after-bind reuse-after-param
            ownership-new-bind ownership-new-param ownership-new-clear ownership-new-unbind ownership-new-enable ownership-new-disable ownership-new-refresh
            ownership-same-bind ownership-same-param ownership-same-clear ownership-same-unbind ownership-same-enable ownership-same-disable ownership-same-refresh
            ownership-other-type)
        add_test(NAME material-${scenario} COMMAND material-entity-sync-tests ${scenario})
    endforeach ()
endif ()