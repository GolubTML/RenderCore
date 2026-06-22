add_executable(test main.cpp)
target_link_libraries(test PRIVATE RenderCore)

set(SHADER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

add_custom_command(
    TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_BIN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADER_SRC_DIR}" "${SHADER_BIN_DIR}"
    COMMENT "Copying shaders to build directory..."
)
