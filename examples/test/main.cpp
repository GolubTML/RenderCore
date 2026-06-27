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

    auto vertex = rc::Assets::Create<rc::Shader>("shaders/default_vert.spv", rc::ShaderType::VERTEX);
    auto fragment = rc::Assets::Create<rc::Shader>("shaders/default_frag.spv", rc::ShaderType::FRAGMENT);

    // set up shaders
    rc::SetShaders(*vertex, *fragment);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    rc::Vec2 pos = {300.f, 200.f};

    auto defaultMaterial = rc::Assets::Create<rc::Material>(rc::Color{255, 255, 255});

    auto rectangle = rc::Shapes::CreateRectangle(pos, 80.f, 40.f, defaultMaterial);
    auto rectangle2 = rc::Shapes::CreateRectangle({500.f, 400.f}, 70.f, 70.f, defaultMaterial);

    while (!window.ShouldClose())
    {
        window.PollEvents();
        float dt = rc::Time::GetDeltaTime();

        rc::ClearColor(0.2f, 0.2f, 0.2f);

        rc::BeginFrame();

            rc::DrawObject(rectangle);
            rc::DrawObject(rectangle2);

        rc::EndFrame();
    }

    rc::Shapes::DestroyObject(rectangle);
    rc::Shapes::DestroyObject(rectangle2);

    window.Terminate();

    rc::Terminate();
}