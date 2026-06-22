#include <RenderCore/RenderCore.hpp>
#include <iostream>

int main()
{
    rc::Init();

    rc::WindowDesc description
    {
        .width = 800,
        .height = 600,
        .title = "Test"
    };

    rc::Window window(description);
    rc::InitVulkan(window);

    rc::Shader vertex = rc::LoadShader("shaders/default_vert.spv", rc::ShaderType::VERTEX);
    rc::Shader fragment = rc::LoadShader("shaders/default_frag.spv", rc::ShaderType::FRAGMENT);

    // set up shaders
    rc::SetShaders(vertex, fragment);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    glm::vec2 pos = {300.f, 200.f};

    auto rectangle = rc::CreateRectangle(pos, 80.f, 40.f, { 255, 255, 255 });
    auto rectangle2 = rc::CreateRectangle({500.f, 400.f}, 70.f, 70.f, { 0, 255, 255 });

    while (!window.ShouldClose())
    {
        window.PollEvents();

        rc::ClearColor(0.2f, 0.2f, 0.2f);

        rc::BeginFrame();

            rc::DrawObject(rectangle);
            rc::DrawObject(rectangle2);

        rc::EndFrame();

        rectangle.transform.position.x += 10.f * rc::Time::GetDeltaTime();
    }

    rc::DestroyObject(rectangle);
    rc::DestroyObject(rectangle2);

    window.Terminate();

    rc::Terminate();
}