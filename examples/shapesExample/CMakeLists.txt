add_executable(shapesExample main.cpp)
target_link_libraries(shapesExample PRIVATE RenderCore)

set(SHADER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

set(ASSETS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

add_custom_command(
    TARGET shapesExample POST_BUILD
    
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_BIN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SHADER_SRC_DIR}" "${SHADER_BIN_DIR}"
    COMMENT "Copying shaders to build directory..."
)

add_custom_command(
    TARGET shapesExample POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_BIN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SRC_DIR}" "${ASSETS_BIN_DIR}"
    COMMENT "Copying assets to build directory..."
)
