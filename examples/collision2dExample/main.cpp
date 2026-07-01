#include <RenderCore/RenderCore.hpp>
#include <RenderCore/2d/shape2D.hpp>
#include <RenderCore/2d/physics/collision2D.hpp>
#include <iostream>

// let's say, we have a player
// Player has a hitbox in it, so we can use it to calculate collisions 

class Player
{
public:
    Player(const rc::Vec2& pos) : position(pos)
    {
        speed = 60.f;
        direction = {0.f, 0.f};

        hitbox.position = position;
        hitbox.size = { 40.f, 40.f };

        rItem = rc::Shape2D::CreateRectangle(hitbox, rc::Color::White());
    }
    void Destroy()
    {
        rc::DestroyObject(rItem);
    }

    void update(float dt, const rc::Rectangle& wall)
    {
        oldPosition = position;

        direction = {0, 0};

        if (rc::Input::IsKeyPressed(rc::Key::W)) direction.y = -1;
        if (rc::Input::IsKeyPressed(rc::Key::S)) direction.y = 1;
        if (rc::Input::IsKeyPressed(rc::Key::A)) direction.x = -1;
        if (rc::Input::IsKeyPressed(rc::Key::D)) direction.x = 1;

        position.x += direction.x * speed * dt;
        hitbox.position = position;

        if (rc::Collision2D::Intersects(hitbox, wall))
                position.x = oldPosition.x;

        hitbox.position = position;

        position.y += direction.y * speed * dt;
        hitbox.position = position;

        if (rc::Collision2D::Intersects(hitbox, wall))
                position.y = oldPosition.y;

        hitbox.position = position;
        rItem.transform.position = rc::Vec3(position, 0); // yeah, this should be fixed
    }

    void draw()
    {
        rc::DrawObject(rItem);
    }

    const rc::Rectangle& getHitBox() const
    {
        return hitbox;
    }

private:
    rc::RenderItem rItem; // so, this is what we will drawing

    rc::Vec2 position; // later, we will use it for both Transform and hitbox
    rc::Vec2 oldPosition; // need for collision
    rc::Vec2 direction;

    rc::Rectangle hitbox; // hitbox

    float speed = 0.f;
};

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

    Player player({ 400.f, 300.f });

    // and, we have a wall for example
    // wall is a static object, so we should update his hitbox position

    rc::Rectangle wallHitBox 
    {
        .position = { 500.f, 300.f },
        .size = { 40.f, 120.f }
    };

    auto wall = rc::Shape2D::CreateRectangle(wallHitBox, rc::Color::Orange());

    while (!window.ShouldClose())
    {
        window.PollEvents();
        float dt = rc::Time::GetDeltaTime();

        rc::ClearColor(0.01f, 0.01f, 0.01f);

        player.update(dt, wallHitBox);

        rc::BeginFrame();

            player.draw();
            rc::DrawObject(wall);

        rc::EndFrame();
    }

    player.Destroy(); // and clean up all data in player
    rc::DestroyObject(wall);

    window.Terminate();

    rc::Terminate();
}