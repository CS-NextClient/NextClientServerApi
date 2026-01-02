cmake_minimum_required(VERSION 3.10)
project(cssdk)

add_library(${PROJECT_NAME} INTERFACE)
add_library(cssdk::cssdk ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/common
		${CMAKE_CURRENT_SOURCE_DIR}/dlls
		${CMAKE_CURRENT_SOURCE_DIR}/engine
		${CMAKE_CURRENT_SOURCE_DIR}/pm_shared
		${CMAKE_CURRENT_SOURCE_DIR}/public
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME} INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/public/interface.cpp
)
