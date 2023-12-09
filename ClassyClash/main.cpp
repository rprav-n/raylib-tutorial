#include <cstdio>
#include "raylib.h"
#include "raymath.h"

int main()
{
    const int WIN_WIDTH = 384;
    const int WIN_HEIGHT = 384;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Classy Clash");

    Texture2D map = LoadTexture("./nature_tileset/background.png");
    Vector2 map_pos = {0.0f, 0.0f};
    const float SCALE = 4.0f;

    Texture2D knight_idle = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("./characters/knight_run_spritesheet.png");

    Texture2D knight = knight_idle;
    Vector2 knight_pos = {
        WIN_WIDTH / 2.0f - SCALE * 0.5f * knight.width / 6.0f,
        WIN_HEIGHT / 2.0f - SCALE * 0.5f * knight.height,
    };
    // 1: right, -1: left
    float right_left = {1.f};

    // animation variables
    const float UPDATE_TIME = 1.f / 12.f;
    float running_time = 0.f;
    int frame = 1;
    const int MAX_FRAMES = 6;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();

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
            knight = knight_run;
            direction = Vector2Normalize(direction);
            map_pos = Vector2Subtract(map_pos, Vector2Scale(direction, SCALE));

            if (direction.x != 0)
            {
                right_left = direction.x < 0.f ? -1.f : 1.f;
            }
        }
        else
        {
            knight = knight_idle;
        }

        // draw the map
        DrawTextureEx(map, map_pos, 0.0f, 4.0f, WHITE);

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
        Rectangle source = Rectangle{frame * knight.width / 6.0f, 0, right_left * knight.width / 6.0f, (float)knight.height};
        Rectangle dest = Rectangle{knight_pos.x, knight_pos.y, SCALE * knight.width / 6.0f, SCALE * knight.height};
        DrawTexturePro(knight, source, dest, Vector2{0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(knight);
    UnloadTexture(map);
    CloseWindow();

    return 0;
}