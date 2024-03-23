cmake_minimum_required(VERSION 3.10)

project(nextclientapi_amxx)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
	set(NAPI_TARGET_PROPS
		SUFFIX "_i386.so"
		COMPILE_FLAGS "-m32" 
		LINK_FLAGS "-m32 -static-libstdc++ -static-libgcc -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/version.version"
		LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/version.version
	)

	set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
endif()

set(AMXXMODULE_SDK_MODULECONFIG_DIR
	${CMAKE_SOURCE_DIR}/public
)

find_package(Threads REQUIRED)
add_subdirectory(deps/amxxmodule)
add_subdirectory(deps/cssdk)
add_subdirectory(deps/metamod)
add_subdirectory(deps/openssl)
add_subdirectory(deps/rsa_keygen)

add_library(${PROJECT_NAME} SHARED
	src/main.h
	src/main.cpp
	src/utilfuncs.cpp
	src/rehlds_api_provider.h
	src/rehlds_api_provider.cpp
	src/SizeBufWriter.h
	src/api/CvarSandbox.h
	src/api/CvarSandbox.cpp
	src/api/PrivatePrecache.h
	src/api/PrivatePrecache.cpp
	src/api/ViewmodelFX.h
	src/api/ViewmodelFX.cpp
	src/api/Verificator.h
	src/api/Verificator.cpp
	src/api/HealthNext.h
	src/api/HealthNext.cpp
	src/api/NextClientApi.h
	src/api/NextClientApi.cpp
	src/api/NclmProtocol.h
	src/api/NclmProtocol.cpp
	src/api/DeathMsgWpnIcon.h
	src/api/DeathMsgWpnIcon.cpp
	src/EventManager.h
	src/EventManager.cpp
	src/natives/cvar_sandbox.cpp
	src/natives/death_notice_wpn_icon.cpp
	src/natives/private_precache.cpp
	src/natives/viewmodelfx.cpp
	src/natives/nextclient.cpp
	src/natives/natives.cpp
	src/asserts.cpp
	src/asserts.h

	${AMXXMODULE_SDK_INCLUDE_PATHS}
	${AMXXMODULE_SDK_RUNTIME_SOURCE_FILE}
	${CSSDK_RUNTIME_SOURCE_FILES}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	HAVE_STDINT_H
	NOMINMAX
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CSSDK_INCLUDE_PATHS}
	${METAMOD_SDK_INCLUDE_PATHS}
	${AMXXMODULE_SDK_INCLUDE_PATHS}
	${OPENSSL_INCLUDE_PATHS}
	src
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	PREFIX ""
	${NAPI_TARGET_PROPS}
)

target_link_libraries(${PROJECT_NAME} 
	${OPENSSL_STATIC_LIBS}
	${NAPI_LINK_LIBS}
	Threads::Threads
)

# custom build targets
add_custom_target(BUILD_ALL ALL)
add_dependencies(BUILD_ALL nextclientapi_amxx)

add_custom_target(INSTALL_ALL
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:nextclientapi_amxx> $ENV{nextclientapi_amxx_COPY_TO_PATH})

add_custom_target(BUILD_AND_INSTALL_ALL ALL)
add_dependencies(BUILD_AND_INSTALL_ALL BUILD_ALL)
add_dependencies(BUILD_AND_INSTALL_ALL INSTALL_ALL)
