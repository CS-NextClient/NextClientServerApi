#-------------------------------------------------------------------------------------------
#
# To use this library, add the following code to your CMakeLists.txt:
#
#    # AMXX module info
#    set(AMXX_MODULE_NAME       "Module name")
#    set(AMXX_MODULE_VERSION    "Module version")
#    set(AMXX_MODULE_AUTHOR     "Module author")
#    set(AMXX_MODULE_URL        "Module URL")
#    set(AMXX_MODULE_LIBRARY    "Module library")
#    set(AMXX_MODULE_LIB_CLASS  "Module class")
#    set(AMXX_MODULE_LOG_TAG    "Module log tag")
#    set(AMXX_MODULE_DATE       "Module date")
#
#    # Use Metamod SDK (ON/OFF)
#    set(AMXX_USE_METAMOD OFF)
#
#    # Reload module on map change (AMXX_USE_METAMOD should be OFF) "true" / "false"
#    set(AMXX_MODULE_RELOAD_ON_MAP_CHANGE "false")
#
#    # Compatibility with AMXX v1.8.2 (ON/OFF)
#    set(AMXX_182_COMPATIBILITY ON)
#
#    # Uncomment the functions you want to use in your code and specify the desired function names
#    #set(AMXX_QUERY "OnAmxxQuery")                         # void OnAmxxQuery();
#    #set(AMXX_ATTACH "OnAmxxAttach")                       # AmxxStatus OnAmxxAttach();
#    #set(AMXX_DETACH "OnAmxxDetach")                       # void OnAmxxDetach();
#    #set(AMXX_CHECK_GAME "OnAmxxCheckGame")                # AmxxGameStatus OnAmxxCheckGame(const char* game);
#    #set(AMXX_PLUGINS_LOADED "OnAmxxPluginsLoaded")        # void OnAmxxPluginsLoaded();
#    #set(AMXX_PLUGINS_UNLOADED "OnAmxxPluginsUnloaded")    # void OnAmxxPluginsUnloaded();
#    #set(AMXX_PLUGINS_UNLOADING "OnAmxxPluginsUnloading")  # void OnAmxxPluginsUnloading();
#
#    add_subdirectory("path/to/amxx/directory")
#    target_link_libraries(${PROJECT_NAME} PRIVATE amxx)
#
# Optional dependencies:
#    https://gitlab.com/goldsrc-sdk/metamod.git
#
#-------------------------------------------------------------------------------------------

# Minimum required version of CMake for a project
cmake_minimum_required(VERSION 3.20)

# Declare project
project("amxx")

# Add a library target to be built from the source files
add_library(${PROJECT_NAME} INTERFACE)

# AMXX module info
if(NOT DEFINED AMXX_MODULE_NAME)
    set(AMXX_MODULE_NAME "${INFO_PROJECT_NAME}")
endif()

if(NOT DEFINED AMXX_MODULE_VERSION)
    set(AMXX_MODULE_VERSION "${CMAKE_PROJECT_VERSION}")
endif()

if(NOT DEFINED AMXX_MODULE_AUTHOR)
    set(AMXX_MODULE_AUTHOR "${INFO_PROJECT_AUTHOR}")
endif()

if(NOT DEFINED AMXX_MODULE_URL)
    set(AMXX_MODULE_URL "${CMAKE_PROJECT_HOMEPAGE_URL}")
endif()

if(NOT DEFINED AMXX_MODULE_LIBRARY)
    set(AMXX_MODULE_LIBRARY "${CMAKE_PROJECT_NAME}")
endif()

if(NOT DEFINED AMXX_MODULE_LIB_CLASS)
    set(AMXX_MODULE_LIB_CLASS "${CMAKE_PROJECT_NAME}")
endif()

if(NOT DEFINED AMXX_MODULE_LOG_TAG)
    string(TOUPPER "${INFO_PROJECT_NAME}" AMXX_MODULE_LOG_TAG)
endif()

if(NOT DEFINED AMXX_MODULE_DATE)
    set(AMXX_MODULE_DATE "__DATE__")
endif()

# Use Metamod SDK (ON/OFF)
if(NOT DEFINED AMXX_USE_METAMOD)
    set(AMXX_USE_METAMOD OFF)
endif()

# Reload module on map change (AMXX_USE_METAMOD should be OFF) "true" / "false"
if(NOT DEFINED AMXX_MODULE_RELOAD_ON_MAP_CHANGE)
    set(AMXX_MODULE_RELOAD_ON_MAP_CHANGE "false")
endif()

# Compatibility with AMXX v1.8.2 (ON/OFF)
if(NOT DEFINED AMXX_182_COMPATIBILITY)
    set(AMXX_182_COMPATIBILITY ON)
endif()

# Uncomment the functions you want to use in your code and specify the desired function names
#set(AMXX_QUERY "OnAmxxQuery")                          # void OnAmxxQuery();
#set(AMXX_ATTACH "OnAmxxAttach")                        # AmxxStatus OnAmxxAttach();
#set(AMXX_DETACH "OnAmxxDetach")                        # void OnAmxxDetach();
#set(AMXX_CHECK_GAME "OnAmxxCheckGame")                 # AmxxGameStatus OnAmxxCheckGame(const char* game);
#set(AMXX_PLUGINS_LOADED "OnAmxxPluginsLoaded")         # void OnAmxxPluginsLoaded();
#set(AMXX_PLUGINS_UNLOADED "OnAmxxPluginsUnloaded")     # void OnAmxxPluginsUnloaded();
#set(AMXX_PLUGINS_UNLOADING "OnAmxxPluginsUnloading")   # void OnAmxxPluginsUnloading();

# Link dependencies
if(AMXX_USE_METAMOD)
    target_link_libraries(${PROJECT_NAME} INTERFACE metamod)
endif()

# Create config.h
configure_file("include/amxx/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/amxx/config.h" @ONLY)

# Add include directories to a target
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE "include")

# Find header and source files
file(GLOB_RECURSE AMXX_PUBLIC_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE AMXX_PRIVATE_HEADERS CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE AMXX_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add header and source files to target sources list
target_sources(${PROJECT_NAME} INTERFACE
    ${AMXX_PUBLIC_HEADERS}
    ${AMXX_PRIVATE_HEADERS}
    ${AMXX_SOURCES}
)

# Add compile definitions to a target
target_compile_definitions(${PROJECT_NAME} INTERFACE HAS_AMXX_LIB)

if(AMXX_USE_METAMOD)
    target_compile_definitions(${PROJECT_NAME} INTERFACE USE_METAMOD)
endif()

if(AMXX_182_COMPATIBILITY)
    target_compile_definitions(${PROJECT_NAME} INTERFACE AMXX_182_COMPATIBILITY)
endif()

# Specify the required C and C++ standard
target_compile_features(${PROJECT_NAME} INTERFACE c_std_11)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
