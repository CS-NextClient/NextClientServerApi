#-------------------------------------------------------------------------------------------
#
# To use this library, add the following code to your CMakeLists.txt:
#
#    add_subdirectory("path/to/mhooks/directory")
#    target_link_libraries(${PROJECT_NAME} PRIVATE mhooks)
#
# Dependencies:
#    https://gitlab.com/goldsrc-sdk/cssdk.git
#    https://gitlab.com/goldsrc-sdk/core.git
#
# Optional dependencies:
#    https://gitlab.com/goldsrc-sdk/amxx.git
#    https://gitlab.com/goldsrc-sdk/metamod.git
#
#-------------------------------------------------------------------------------------------

# Minimum required version of CMake for a project
cmake_minimum_required(VERSION 3.20)

# Declare project
project("mhooks")

# Add a library target to be built from the source files
add_library(${PROJECT_NAME} INTERFACE)

# Link dependencies
target_link_libraries(${PROJECT_NAME} INTERFACE "cssdk")
target_link_libraries(${PROJECT_NAME} INTERFACE "core")

# Add include directories to a target
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE "include")

# Find header and source files
file(GLOB_RECURSE MHOOKS_PUBLIC_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE MHOOKS_PRIVATE_HEADERS CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE MHOOKS_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Add header and source files to target sources list
target_sources(${PROJECT_NAME} INTERFACE
    ${MHOOKS_PUBLIC_HEADERS}
    ${MHOOKS_PRIVATE_HEADERS}
    ${MHOOKS_SOURCES}
)

# Add compile definitions to a target
target_compile_definitions(${PROJECT_NAME} INTERFACE HAS_MHOOKS_LIB)

# Specify the required C and C++ standard
target_compile_features(${PROJECT_NAME} INTERFACE c_std_11)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
