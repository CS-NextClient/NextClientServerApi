cmake_minimum_required(VERSION 3.0.0)
project(rsa_keygen)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_PATHS})

target_link_libraries(${PROJECT_NAME} ${OPENSSL_STATIC_LIBS})