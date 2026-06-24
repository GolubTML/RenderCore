#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

layout(set = 0, binding = 0) uniform CameraUBO
{
    mat4 view;
    mat4 proj;
} camera;

layout(push_constant) uniform PushModel
{
    mat4 model;
} pc;

void main()
{
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    
    gl_Position = camera.proj * camera.view * pc.model * vec4(inPos, 1.0);
}