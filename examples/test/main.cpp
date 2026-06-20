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

    rc::Camera camera(glm::vec3(0.f, 0.f, 6.f), 60.f, description.width, description.height);
    rc::SetCamera(camera);

    auto rectangle = rc::CreateRectangle({2.f, 2.f, 0.f}, 1.f, 1.f, { 255, 255, 255 });

    while (!window.ShouldClose())
    {
        window.PollEvents();

        rc::ClearColor(0.1f, 0.1f, 0.1f);

        rc::BeginFrame();
            // some cool code here
            rc::DrawObject(rectangle);

        rc::EndFrame();
    }

    rc::DestroyObject(rectangle);
    
    rc::Terminate();
}