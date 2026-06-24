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

    rc::Shader vertex = rc::LoadShader("shaders/default_vert.spv", rc::ShaderType::VERTEX);
    rc::Shader fragment = rc::LoadShader("shaders/default_frag.spv", rc::ShaderType::FRAGMENT);

    rc::SetShaders(vertex, fragment);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    // And now we can use Materials!
    // Let's load the texture
    rc::Texture2D texture = rc::LoadTexture("assets/dirt.png"); 
    // And create the material
    rc::Material* material = rc::CreateMaterial({255, 255, 255}, texture);
    rc::Material* defaultMaterial = rc::CreateMaterial({60, 255, 255});

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

    // We need also destroy the material
    rc::DestroyMaterial(material);
    rc::DestroyMaterial(defaultMaterial);

    window.Terminate();

    rc::Terminate();
}