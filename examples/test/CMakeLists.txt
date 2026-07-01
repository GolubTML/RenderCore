add_executable(collision2dExample main.cpp)
target_link_libraries(collision2dExample PRIVATE RenderCore)

set(SHADER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

add_custom_command(
    TARGET collision2dExample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_BIN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADER_SRC_DIR}" "${SHADER_BIN_DIR}"
    COMMENT "Copying shaders to build directory..."
)
