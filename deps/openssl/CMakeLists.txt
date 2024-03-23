cmake_minimum_required(VERSION 3.0.0)
project(cssdk)

if(WIN32)
	set(OPENSSL_LINK_LIBS 
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto_static.lib
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libssl_static.lib
		ws2_32.lib
	)
elseif(UNIX)
	set(OPENSSL_LINK_LIBS 
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrypto.a
		${CMAKE_CURRENT_SOURCE_DIR}/lib/libssl.a
	)
endif()

set(OPENSSL_INCLUDE_PATHS
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(OPENSSL_INCLUDE_PATHS
    ${OPENSSL_INCLUDE_PATHS}
	PARENT_SCOPE
)

set(OPENSSL_STATIC_LIBS
	${OPENSSL_LINK_LIBS}
)

set(OPENSSL_STATIC_LIBS
    ${OPENSSL_STATIC_LIBS}
	PARENT_SCOPE
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${OPENSSL_INCLUDE_PATHS}
)
