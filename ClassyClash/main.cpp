#include <cstdio>
#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return world_pos; }
    void setPos(int win_width, int win_height); // function prototype
    void tick(float dt);

private:
    Texture2D texture = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("./characters/knight_run_spritesheet.png");
    Vector2 pos = {};
    Vector2 world_pos = {};

    // 1: right, -1: left
    float right_left = {1.f};

    // animation variables
    const float UPDATE_TIME = 1.f / 12.f;
    float running_time = 0.f;
    int frame = 1;
    const int MAX_FRAMES = 6;
    const float SCALE = {4.f};
};

void Character::setPos(int win_width, int win_height) // :: - scope resolution operator
{
    pos = {
        win_width / 2.0f - SCALE * 0.5f * texture.width / 6.0f,
        win_height / 2.0f - SCALE * 0.5f * texture.height,
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
    Rectangle source = Rectangle{frame * texture.width / 6.0f, 0, right_left * texture.width / 6.0f, (float)texture.height};
    Rectangle dest = Rectangle{pos.x, pos.y, SCALE * texture.width / 6.0f, SCALE * texture.height};
    DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.0f, WHITE);
}

int main()
{
    const int WIN_WIDTH = 384;
    const int WIN_HEIGHT = 384;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Classy Clash");

    Texture2D map = LoadTexture("./nature_tileset/background.png");
    Vector2 map_pos = {0.0f, 0.0f};
    const float SCALE = 4.0f;

    Character knight = Character();
    knight.setPos(WIN_WIDTH, WIN_HEIGHT);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();

        // draw the map
        DrawTextureEx(map, knight.getWorldPos(), 0.0f, SCALE, WHITE);

        // draw knight
        knight.tick(dt);

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();

    return 0;
}