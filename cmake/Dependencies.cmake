include(FetchContent)

# === kangaru ===
FetchContent_Declare(
        kangaru
        GIT_REPOSITORY https://github.com/gracicot/kangaru.git
        GIT_TAG        v4.3.2
)
set(KANGARU_INSTALL OFF CACHE BOOL "" FORCE)
set(KANGARU_EXPORT OFF CACHE BOOL "" FORCE)
set(KANGARU_REVERSE_DESTRUCTION ON CACHE BOOL "" FORCE)

# === sigslot ===
FetchContent_Declare(
        sigslot
        GIT_REPOSITORY https://github.com/palacaze/sigslot
        GIT_TAG        19a6f0f5ea11fc121fe67f81fd5e491f2d7a4637 # v1.2.0
)
set(SIGSLOT_COMPILE_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SIGSLOT_COMPILE_TESTS OFF CACHE BOOL "" FORCE)

# === magic_enum ===
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG        v0.9.7
)

# =======

FetchContent_MakeAvailable(kangaru sigslot magic_enum)
