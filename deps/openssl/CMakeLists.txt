cmake_minimum_required(VERSION 3.10)
project(openssl)

add_library(${PROJECT_NAME} INTERFACE)
add_library(openssl::openssl ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
	target_link_libraries(${PROJECT_NAME} INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto_static.lib
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libssl_static.lib
		ws2_32.lib
	)
elseif(UNIX)
	target_link_libraries(${PROJECT_NAME} INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto.a
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libssl.a
	)
endif()
