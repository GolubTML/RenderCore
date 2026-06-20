file(GLOB_RECURSE SRC_FILES "*.cpp")
add_library(RenderCore STATIC ${SRC_FILES})

target_include_directories(RenderCore PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(RenderCore PUBLIC 
    Vulkan::Vulkan
    glfw    
)