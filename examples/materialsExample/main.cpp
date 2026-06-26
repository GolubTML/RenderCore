#include <RenderCore/RenderCore.hpp>
#include <iostream>

int main()
{
    // GLFW init here
    rc::Init();

    rc::WindowDesc description
    {
        .width = 800,
        .height = 600,
        .title = "Material Example",
        .resizable = false // we dont need this here 
    };

    rc::Window window(description);
    rc::InitVulkan(window);

    auto vertex = rc::Assets::Create<rc::Shader>("shaders/default_vert.spv", rc::ShaderType::VERTEX);
    auto fragment = rc::Assets::Create<rc::Shader>("shaders/default_frag.spv", rc::ShaderType::FRAGMENT);

    rc::SetShaders(*vertex, *fragment);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    // And now we can use Materials!
    // Let's load the texture
    auto texture = rc::Assets::Create<rc::Texture2D>("assets/dirt.png");
    
    // And create the material
    auto material = rc::Assets::Create<rc::Material>(
        rc::Color{255, 255, 255}, 
        texture
    );

    auto defaultMaterial = rc::Assets::Create<rc::Material>(rc::Color{60, 255, 255});

    auto rectangle = rc::Shapes::CreateRectangle({140.f, 300.f}, 160.f, 160.f, material);
    auto rectangle2 = rc::Shapes::CreateRectangle({description.width - 160.f, 300.f}, 160.f, 160.f, defaultMaterial);

    while (!window.ShouldClose())
    {
        window.PollEvents();
        float dt = rc::Time::GetDeltaTime();

        rc::ClearColor(0.01f, 0.01f, 0.01f);

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