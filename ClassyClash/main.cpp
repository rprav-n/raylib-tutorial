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

    Texture2D knight = LoadTexture("./characters/knight_idle_spritesheet.png");
    Vector2 knight_pos = {
        WIN_WIDTH / 2.0f - SCALE * 0.5f * knight.width / 6.0f,
        WIN_HEIGHT / 2.0f - SCALE * 0.5f * knight.height,
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction = {};
        if (IsKeyDown(KEY_A))
            direction.x = -1;
        if (IsKeyDown(KEY_D))
            direction.x = 1;
        if (IsKeyDown(KEY_W))
            direction.y = -1;
        if (IsKeyDown(KEY_S))
            direction.y = 1;

        direction = Vector2Normalize(direction);
        map_pos = Vector2Subtract(map_pos, Vector2Scale(direction, SCALE));

        DrawTextureEx(map, map_pos, 0.0f, 4.0f, WHITE);
        Rectangle source = Rectangle{0, 0, knight.width / 6.0f, (float)knight.height};
        Rectangle dest = Rectangle{knight_pos.x, knight_pos.y, SCALE * knight.width / 6.0f, SCALE * knight.height};

        DrawTexturePro(knight, source, dest, Vector2{0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(knight);
    UnloadTexture(map);
    CloseWindow();

    return 0;
}