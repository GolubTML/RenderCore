#include <RenderCore/RenderCore.hpp>

int main()
{
    rc::Init();

    rc::WindowDesc description{};
    description.width = 800;
    description.height = 600;
    description.title = "Test";

    rc::Window window(description);
    rc::InitVulkan(window);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    auto rectangle = rc::CreateRectangle({300.f, 200.f}, 80.f, 40.f, { 255, 255, 255 });
    auto rectangle2 = rc::CreateRectangle({500.f, 400.f}, 70.f, 70.f, { 0, 255, 255 });

    while (!window.ShouldClose())
    {
        window.PollEvents();

        rc::ClearColor(0.1f, 0.1f, 0.1f);

        rc::BeginFrame();
            // some bullshit code here
            rc::DrawObject(rectangle);
            rc::DrawObject(rectangle2);

        rc::EndFrame();
    }

    rc::DestroyObject(rectangle);
    rc::DestroyObject(rectangle2);
    
    rc::Terminate();
}