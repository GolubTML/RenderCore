#include <RenderCore/RenderCore.hpp>
#include <RenderCore/2d/shape2D.hpp>
#include <iostream>

int main()
{
    rc::Init();

    rc::WindowDesc description
    {
        .width = 800,
        .height = 600,
        .title = "Collision 2D example",
        .resizable = true
    };

    rc::Window window(description);
    rc::InitVulkan(window);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    rc::Vec2 pos = {300.f, 200.f};

    auto rectangle = rc::Shape2D::CreateRectangle(pos, 80.f, 40.f, rc::Color::White());

    while (!window.ShouldClose())
    {
        window.PollEvents();
        float dt = rc::Time::GetDeltaTime();

        rc::ClearColor(0.01f, 0.01f, 0.01f);

        rc::BeginFrame();

            rc::DrawObject(rectangle);

        rc::EndFrame();
    }

    rc::DestroyObject(rectangle);

    window.Terminate();

    rc::Terminate();
}