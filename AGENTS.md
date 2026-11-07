# NextClientServerApi

This repository builds a 32-bit AMX Mod X module for Counter-Strike 1.6. Production services synchronize explicit entity fields to NextClient recipients. Read the affected service, native, and client consumer before changing their shared protocol.

## Build and verification

CMake 3.16+, C++17, and a 32-bit compiler toolchain are required. On Windows, initialize the MSVC x86 environment with `vcvarsall.bat x86` before using Ninja. Configure a build directory before building; the local `cmake-build-release-visual-studio-2026-x86` directory uses Ninja, MSVC x86, Release, and enabled tests.

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DNEXTCLIENTAPI_BUILD_TESTS=ON
cmake --build build --target material-visibility-tests --parallel
cmake --build build --target entity-sync-packets-tests --parallel
cmake --build build --target material-entity-sync-tests --parallel
ctest --test-dir build --output-on-failure
cmake --build build --target nextclientapi_amxx --parallel
```

Build one target per command. Use BelowNormal priority for Windows builds and tests; all CPUs are permitted. Select focused CTest scenarios while implementing a localized change, then run the affected suite once. Keep passing evidence for the same source, dependency, and build configuration snapshot. Generated SDK configuration headers may change during configure; preserve unrelated working changes in those files.

`material-entity-sync-tests` compiles the production native, string registry, entity synchronization, material service, and serializer with external engine and transport fakes. The transport retains message type and recipient identity. Test complete reconstructed state separately for each recipient, including registration order, first frame, late join, visibility changes, disconnect, version, and readiness. Material bindings are ordered complete `(preset_id, material_id)` pairs; several materials may use one preset.

Compile the maintained test plugin with the real AMX Mod X compiler and the AMX Mod X/ReAPI include directories. Configure the optional `pawn-material-plugin` CTest with `-DNEXTCLIENTAPI_PAWN_COMPILER=<AMXXPC_PATH>` and `-DNEXTCLIENTAPI_PAWN_INCLUDE_DIR=<AMXX_REAPI_INCLUDE_DIR>`; compiler warnings fail this test. The repository's API include must be supplied explicitly for a direct invocation:

```powershell
amxxpc amxx_test/addons/amxmodx/scripting/test_nextclient_api.sma -iaddons/amxmodx/scripting/include -i<AMXX_REAPI_INCLUDE_DIR> -o<OUTPUT_DIR>/test_nextclient_api.amxx
```

Do not launch a game or live server for automated verification. Do not install or copy build outputs into a running server as a verification step.

## Native and wire contracts

Pawn material parameters use `Float:` cells. A native reads the cell's IEEE 754 bits through `amx::CellToFloat`; passing an integer cell does not perform numeric conversion. Read floating-point command arguments with `read_argv_float` and pass finite values in the material parameter's declared units. The wear command uses `0.0` for untouched and `1.0` for fully worn.

The wire schema is explicit in `include/nextclientapi_amxx/ncl_entity` and the corresponding service descriptor and serializer. C++ object layouts, variants, pointers, and bookkeeping fields are process-local and must never be sent as raw structs. Keep client and server type IDs, field order, field masks, sizes, and little-endian encoding consistent. Create headers contain a one-byte type and two-byte sync ID; update headers add a two-byte field mask. Material fields are the rendered entity's uint32 index, ordered string-ID pairs, then string-ID/float parameter pairs. Collection chunks and clear/removal operations must reconstruct the complete state.

`msg_ex::kMaxPayload` is 192 bytes. A string registration uses a two-byte ID and a null terminator, so a registered string or complete scoped parameter key can contain at most 189 bytes. Validate all names and finite values before state mutation. Send reliable string registrations to each recipient before any packet references those IDs; one recipient's known-string state cannot authorize another recipient's references.

A material synchronization owner is identified by sync ID, entity type, edict pointer, and edict serial number. Check the complete identity with `EntitySync::IsBoundTo` before mutation, destruction, or visibility changes. Numeric IDs can be recycled and do not establish ownership by themselves.

Generic `EntitySync` delivery requires a known client version of at least 2.5.0 and its first-frame state. It does not use `IsClientReady` as a separate delivery gate. Clients without a handler for the material type ignore that type. `MaterialEntitySync` owns the separate through-wall packing policy: the recipient must be ready and version 2.6.0 or newer, and the current source, drawn entity, and packing host identities must remain valid. Test these policies separately rather than applying the packing gate to generic packet delivery.

## Scope and conventions

Preserve existing line endings and format only touched code. Write comments and maintained Markdown documentation in English with American spelling; translations use matching `.ru.md` files. Keep comments concise and explain constraints rather than restating code. Keep protocol state with its owner and lifecycle. Add production behavior only when a reproducing test proves the need.
