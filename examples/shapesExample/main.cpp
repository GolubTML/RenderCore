#include <RenderCore/RenderCore.hpp>
#include <RenderCore/math/math.hpp>
#include <RenderCore/2d/shape2D.hpp>

#include <cmath>

void rotateObjectAround(rc::Transform& object, const rc::Vec2& pivot, float radius, float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    object.position.x = pivot.x + radius * c;
    object.position.y = pivot.y + radius * s;
}

int main()
{
    // GLFW init here
    rc::Init();

    rc::WindowDesc description
    {
        .width = 800,
        .height = 600,
        .title = "Shapes Example",
        .resizable = true
    };

    rc::Window window(description);
    rc::InitVulkan(window);

    /*
        Now, there is no need to create and load shaders to the program
        RenderCore has default prebuild shaders in it

        But, you can use your own shaders in any way

        auto vertex = rc::Assets::Create<rc::Shader>("shaders/default_vert.spv", rc::ShaderType::VERTEX);
        auto fragment = rc::Assets::Create<rc::Shader>("shaders/default_frag.spv", rc::ShaderType::FRAGMENT)
        rc::SetShaders(*vertex, *fragment);

        Or, you can skip this stage, and use basic shaders
    */
    
    rc::Camera2D camera(description.width, description.height);
    rc::SetCamera(camera);

    auto heartTexture = rc::Assets::Create<rc::Texture2D>("assets/heart.png");

    auto defaultMaterial = rc::Assets::Create<rc::Material>(rc::Color{60, 129, 50});
    auto triangleMaterial = rc::Assets::Create<rc::Material>(rc::Color{180, 50, 80});
    auto heartMat = rc::Assets::Create<rc::Material>(rc::Color{255, 255, 255}, heartTexture);

    // new type for 2D rectangles
    rc::Rectangle rect
    {
        .position = rc::Vec2(description.width - 160.f, 300.f),
        .size = rc::Vec2(50.f, 50.f)
    };

    // also, added 3 new overloads to create rectangle
    // auto quad = rc::Shapes::CreateRectangle(posX, posY, width, height, defaultMaterial);
    // auto quad = rc::Shapes::CreateRectangle(pos, width, height, defaultMaterial);
    // auto quad = rc::Shapes::CreateRectangle(pos, size, defaultMaterial); -- size is Vec2
    auto quad = rc::Shape2D::CreateRectangle(rect, defaultMaterial);
    auto heart = rc::Shape2D::CreateRectangle(rect, heartMat);

    // and new triangle here
    rc::Triangle triangle = rc::Triangle::Equilateral(rc::Vec2(0, 0), 50.f);

    auto trian = rc::Shape2D::CreateTriangle(triangle, rc::Color{180, 50, 80});

    rc::Circle circle 
    {
        .position = {400.f, 300.f},
        .radius = 23,
        .segments = 32
    };

    auto testCircle = rc::Shape2D::CreateCircle(circle, rc::Color(0, 0, 0));
    testCircle.transform.scale *= 2.f;

    // And yes, you can create line also
    // rc::Line line{.start = rc::Vec2(10.f, 10.f), .end = rc::Vec2(200.f, 100.f)};
    // auto testLine = rc::Shape2D::CreateLine(line, 5.f, rc::Color(255, 0, 0));

    rc::Vec2 point = rc::Vec2(400.f, 300.f);
    float angle = 0.f;
    float angle2 = 180.f;
    float angle3 = 90.f;

    float radius = 150.f;

    while (!window.ShouldClose())
    {
        window.PollEvents();
        float dt = rc::Time::GetDeltaTime();

        angle += 1.f * dt;
        if (angle >= 360.f) angle = 0.f;

        angle2 += 1.f * dt;
        if (angle2 >= 360.f) angle2 = 0.f;

        angle3 += 1.f * dt;
        if (angle3 >= 360.f) angle3 = 0.f;

        rc::ClearColor(0.01f, 0.01f, 0.01f);

        rotateObjectAround(trian.transform, point, radius - 25.f, angle);
        rotateObjectAround(quad.transform, point, radius, angle2);
        rotateObjectAround(heart.transform, point, radius + 25.f, angle3);

        trian.transform.rotation.rotate(rc::Vec3::Forward(), 120.f * dt); 
        quad.transform.rotation.rotate(rc::Vec3::Forward(), 90.f * dt); 
        heart.transform.rotation.rotate(rc::Vec3::Forward(), 80.f * dt);

        rc::BeginFrame();
            rc::DrawObject(quad);
            rc::DrawObject(trian);
            rc::DrawObject(heart);
            rc::DrawObject(testCircle);
        rc::EndFrame();
    }

    rc::DestroyObject(quad);
    rc::DestroyObject(trian);
    rc::DestroyObject(heart);
    rc::DestroyObject(testCircle);

    window.Terminate();

    rc::Terminate();
}