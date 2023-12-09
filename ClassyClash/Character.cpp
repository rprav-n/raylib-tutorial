#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = (float)texture.width / MAX_FRAMES;
    height = (float)texture.height;
}

void Character::setPos(int win_width, int win_height) // :: - scope resolution operator
{
    pos = {
        win_width / 2.0f - SCALE * 0.5f * width,
        win_height / 2.0f - SCALE * 0.5f * height,
    };
}

void Character::tick(float dt)
{
    Vector2 direction = {};
    if (IsKeyDown(KEY_A))
        direction.x = -1;
    if (IsKeyDown(KEY_D))
        direction.x = 1;
    if (IsKeyDown(KEY_W))
        direction.y = -1;
    if (IsKeyDown(KEY_S))
        direction.y = 1;

    if (Vector2Length(direction) != 0.0)
    {
        texture = run;
        direction = Vector2Normalize(direction);
        world_pos = Vector2Subtract(world_pos, Vector2Scale(direction, SCALE));

        if (direction.x != 0)
        {
            right_left = direction.x < 0.f ? -1.f : 1.f;
        }
    }
    else
    {
        texture = idle;
    }

    // update knight animation
    running_time += dt;
    if (running_time > UPDATE_TIME)
    {
        running_time = 0.f;
        frame++;
        if (frame > MAX_FRAMES)
            frame = 0;
    }

    // draw the knight
    Rectangle source = Rectangle{frame * width, 0, right_left * width, height};
    Rectangle dest = Rectangle{pos.x, pos.y, SCALE * width, SCALE * height};
    DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.0f, WHITE);
}