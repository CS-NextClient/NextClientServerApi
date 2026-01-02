cmake_minimum_required(VERSION 3.10)
project(metamod_sdk)

add_library(${PROJECT_NAME} INTERFACE)
add_library(metamod_sdk::metamod_sdk ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
)
