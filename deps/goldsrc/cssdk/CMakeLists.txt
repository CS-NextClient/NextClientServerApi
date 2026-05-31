#-------------------------------------------------------------------------------------------
#
# To use this library, add the following code to your CMakeLists.txt:
#
#    add_subdirectory("path/to/cssdk/directory")
#    target_link_libraries(${PROJECT_NAME} PRIVATE cssdk)
#
#-------------------------------------------------------------------------------------------

# Minimum required version of CMake for a project
cmake_minimum_required(VERSION 3.20)

# Options
option(CSSDK_REHLDS_FIXES    "Compile with ReHLDS fixes"      ON)
option(CSSDK_REGAMEDLL_FIXES "Compile with ReGameDLL fixes"   ON)
option(CSSDK_REGAMEDLL_API   "Compile with ReGameDLL API"     ON)
option(CSSDK_REGAMEDLL_ADD   "Compile with ReGameDLL add-ons" ON)

# Declare project
project("cssdk")

# Add a library target to be built from the source files
add_library(${PROJECT_NAME} INTERFACE)

# Add include directories to a target
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE "include")

# Find header and source files
file(GLOB_RECURSE CSSDK_PUBLIC_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE CSSDK_PRIVATE_HEADERS CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE CSSDK_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add header and source files to target sources list
target_sources(${PROJECT_NAME} INTERFACE
    ${CSSDK_PUBLIC_HEADERS}
    ${CSSDK_PRIVATE_HEADERS}
    ${CSSDK_SOURCES}
)

# Add compile definitions to a target
target_compile_definitions(${PROJECT_NAME} INTERFACE HAS_CSSDK_LIB)

if(CSSDK_REHLDS_FIXES)
    target_compile_definitions(${PROJECT_NAME} INTERFACE REHLDS_FIXES)
endif()

if(CSSDK_REGAMEDLL_FIXES)
    target_compile_definitions(${PROJECT_NAME} INTERFACE REGAMEDLL_FIXES)
endif()

if(CSSDK_REGAMEDLL_API)
    target_compile_definitions(${PROJECT_NAME} INTERFACE REGAMEDLL_API)
endif()

if(CSSDK_REGAMEDLL_ADD)
    target_compile_definitions(${PROJECT_NAME} INTERFACE REGAMEDLL_ADD)
endif()

# Specify the required C and C++ standard
target_compile_features(${PROJECT_NAME} INTERFACE c_std_11)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
