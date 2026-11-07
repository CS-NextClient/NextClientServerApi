foreach (required IN ITEMS PAWN_COMPILER PAWN_INCLUDE_DIR API_INCLUDE_DIR PAWN_SOURCE PAWN_OUTPUT)
    if (NOT DEFINED ${required} OR "${${required}}" STREQUAL "")
        message(FATAL_ERROR "Missing ${required}")
    endif ()
endforeach ()

execute_process(
        COMMAND "${PAWN_COMPILER}" "${PAWN_SOURCE}" "-i${API_INCLUDE_DIR}" "-i${PAWN_INCLUDE_DIR}" "-o${PAWN_OUTPUT}"
        RESULT_VARIABLE compile_result
        OUTPUT_VARIABLE compile_output
        ERROR_VARIABLE compile_error)

set(compiler_diagnostics "${compile_output}\n${compile_error}")
message("${compiler_diagnostics}")
if (NOT compile_result STREQUAL "0" OR compiler_diagnostics MATCHES "warning [0-9]+:")
    message(FATAL_ERROR "Pawn plugin compilation failed or produced warnings (exit ${compile_result})")
endif ()
