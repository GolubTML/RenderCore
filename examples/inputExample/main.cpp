#include <RenderCore/RenderCore.hpp>
#include <iostream>

void input(glm::vec3& pos, float dt)
{
    // we will be using methods from rc::Input
    // and rc::Key too
    float speed = 60.f;

    if (rc::Input::IsKeyPressed(rc::Key::W)) pos.y -= speed * dt;
    if (rc::Input::IsKeyPressed(rc::Key::S)) pos.y += speed * dt;
    if (rc::Input::IsKeyPressed(rc::Key::A)) pos.x -= speed * dt;
    if (rc::Input::IsKeyPressed(rc::Key::D)) pos.x += speed * dt;
}

int main()
{
    // GLFW init here
    rc::Init();

    rc::WindowDesc description
    {
        .width = 800,
        .height = 600,
        .title = "Input Examle"
    };

    rc::Window window(description);
    rc::InitVulkan(window);

    rc::Shader vertex = rc::LoadShader("shaders/default_vert.spv", rc::ShaderType::VERTEX);
    rc::Shader fragment = rc::LoadShader("shaders/default_frag.spv", rc::ShaderType::FRAGMENT);

    rc::SetShaders(vertex, fragment);

    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    glm::vec2 pos = {400.f, 300.f};

    auto rectangle = rc::CreateRectangle(pos, 40.f, 40.f, { 255, 255, 255 });

    while (!window.ShouldClose())
    {
        window.PollEvents();
        float dt = rc::Time::GetDeltaTime();

        rc::ClearColor(0.2f, 0.2f, 0.2f);

        input(rectangle.transform.position, dt);

        rc::BeginFrame();

            rc::DrawObject(rectangle);

        rc::EndFrame();
    }

    rc::DestroyObject(rectangle);

    window.Terminate();

    rc::Terminate();
}