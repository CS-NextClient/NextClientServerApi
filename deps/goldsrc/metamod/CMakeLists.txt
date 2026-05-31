#-------------------------------------------------------------------------------------------
#
# To use this library, add the following code to your CMakeLists.txt:
#
#    # Metamod plug-in info
#    set(META_PLUGIN_NAME    "Plug-in name")
#    set(META_PLUGIN_VERSION "Plug-in version")
#    set(META_PLUGIN_AUTHOR  "Plug-in author")
#    set(META_PLUGIN_URL     "Plug-in URL")
#    set(META_PLUGIN_LOG_TAG "Plug-in log tag")
#    set(META_PLUGIN_DATE    "Plug-in date")
#
#    # Flags for plug-in to indicate when it can be loaded/unloaded
#    #   "Never"
#    #   "Startup"     - Should only be loaded/unloaded at initial HLDS execution
#    #   "ChangeLevel" - Can be loaded/unloaded between maps
#    #   "AnyPause"    - Can be loaded/unloaded at any time, and can be "paused" during a map.
#    #   "AnyTime"     - Can be loaded/unloaded at any time
#    set(META_PLUGIN_LOADABLE "AnyTime")
#    set(META_PLUGIN_UNLOADABLE "AnyTime")
#
#    # Uncomment the functions you want to use in your code and specify the desired function names
#    #set(META_INIT "OnMetaInit")        # void OnMetaInit();
#    #set(META_QUERY "OnMetaQuery")      # void OnMetaQuery();
#    #set(META_ATTACH "OnMetaAttach")    # MetaStatus OnMetaAttach();
#    #set(META_DETACH "OnMetaDetach")    # void OnMetaDetach();
#
#    add_subdirectory("path/to/metamod/directory")
#    target_link_libraries(${PROJECT_NAME} PRIVATE metamod)
#
# Dependencies:
#    https://gitlab.com/goldsrc-sdk/cssdk.git
#
#-------------------------------------------------------------------------------------------

# Minimum required version of CMake for a project
cmake_minimum_required(VERSION 3.20)

# Declare project
project("metamod")

# Add a library target to be built from the source files
add_library(${PROJECT_NAME} INTERFACE)

# Link dependencies
target_link_libraries(${PROJECT_NAME} INTERFACE cssdk)

# Metamod plug-in info
if(NOT DEFINED META_PLUGIN_NAME)
    set(META_PLUGIN_NAME "${INFO_PROJECT_NAME}")
endif()

if(NOT DEFINED META_PLUGIN_VERSION)
    set(META_PLUGIN_VERSION "${CMAKE_PROJECT_VERSION}")
endif()

if(NOT DEFINED META_PLUGIN_AUTHOR)
    set(META_PLUGIN_AUTHOR "${INFO_PROJECT_AUTHOR}")
endif()

if(NOT DEFINED META_PLUGIN_URL)
    set(META_PLUGIN_URL "${CMAKE_PROJECT_HOMEPAGE_URL}")
endif()

if(NOT DEFINED META_PLUGIN_LOG_TAG)
    string(TOUPPER "${INFO_PROJECT_NAME}" META_PLUGIN_LOG_TAG)
endif()

if(NOT DEFINED META_PLUGIN_DATE)
    set(META_PLUGIN_DATE "__DATE__")
endif()

if(NOT DEFINED META_PLUGIN_LOADABLE)
    set(META_PLUGIN_LOADABLE "AnyTime")
endif()

if(NOT DEFINED META_PLUGIN_UNLOADABLE)
    set(META_PLUGIN_UNLOADABLE "AnyTime")
endif()

# Uncomment the functions you want to use in your code and specify the desired function names
#set(META_INIT "OnMetaInit")        # void OnMetaInit();
#set(META_QUERY "OnMetaQuery")      # void OnMetaQuery();
#set(META_ATTACH "OnMetaAttach")    # MetaStatus OnMetaAttach();
#set(META_DETACH "OnMetaDetach")    # void OnMetaDetach();

# Create config.h
configure_file("include/metamod/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/metamod/config.h" @ONLY)

# Add include directories to a target
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE "include")

# Find header and source files
file(GLOB_RECURSE METAMOD_PUBLIC_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE METAMOD_PRIVATE_HEADERS CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE METAMOD_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add header and source files to target sources list
target_sources(${PROJECT_NAME} INTERFACE
    ${METAMOD_PUBLIC_HEADERS}
    ${METAMOD_PRIVATE_HEADERS}
    ${METAMOD_SOURCES}
)

# Add compile definitions to a target
target_compile_definitions(${PROJECT_NAME} INTERFACE HAS_METAMOD_LIB)

# Add module-definition file to target sources list
if(WIN32)
    target_sources(${PROJECT_NAME} INTERFACE exports.def)
endif()

# Specify the required C and C++ standard
target_compile_features(${PROJECT_NAME} INTERFACE c_std_11)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
