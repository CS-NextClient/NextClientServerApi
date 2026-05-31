#-------------------------------------------------------------------------------------------
#
# To use this library, add the following code to your CMakeLists.txt:
#
#    add_subdirectory("path/to/core/directory")
#    target_link_libraries(${PROJECT_NAME} PRIVATE core)
#
# Dependencies:
#    https://gitlab.com/goldsrc-sdk/cssdk.git
#
# Optional dependencies:
#    https://gitlab.com/goldsrc-sdk/amxx.git
#    https://gitlab.com/goldsrc-sdk/metamod.git
#    https://gitlab.com/goldsrc-sdk/mhooks.git
#
#-------------------------------------------------------------------------------------------

# Minimum required version of CMake for a project
cmake_minimum_required(VERSION 3.20)

# Declare project
project("core")

# Add a library target to be built from the source files
add_library(${PROJECT_NAME} INTERFACE)

# Link dependencies
target_link_libraries(${PROJECT_NAME} INTERFACE cssdk)

# Add include directories to a target
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE "include")

# Find header and source files
file(GLOB_RECURSE CORE_PUBLIC_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE CORE_PRIVATE_HEADERS CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add header and source files to target sources list
target_sources(${PROJECT_NAME} INTERFACE
    ${CORE_PUBLIC_HEADERS}
    ${CORE_PRIVATE_HEADERS}
    ${CORE_SOURCES}
)

# Add compile definitions to a target
target_compile_definitions(${PROJECT_NAME} INTERFACE HAS_CORE_LIB)

# Specify the required C and C++ standard
target_compile_features(${PROJECT_NAME} INTERFACE c_std_11)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
