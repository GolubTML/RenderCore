#include <RenderCore.hpp>
#include <iostream>

int main()
{
    rc::Init();

    rc::WindowDesc description{};
    description.width = 800;
    description.height = 600;
    description.title = "Test";

    rc::Window window(description);

    rc::InitVulkan(window);

    while (!window.ShouldClose())
    {
        window.PollEvents();

        rc::BeginFrame();
            // some cool code here
        rc::EndFrame();
    }
    
    rc::Terminate();
}