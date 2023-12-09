// Classy Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include "raylib.h"
#include "raymath.h"

int main()
{
    const int WIN_WIDTH = 384;
    const int WIN_HEIGHT = 384;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Classy Clash");

    Texture2D map = LoadTexture("./nature_tileset/background.png");
    Vector2 map_pos = { 0.0f, 0.0f };
    const float SPEED = 4.0f;

    Texture2D knight = LoadTexture("./characters/knight_idle_spritesheet.png");
    Vector2 knight_pos = Vector2{ 
        WIN_WIDTH / 2.0f - (0.5f * knight.width / 6.0f) * 4.0f, 
        WIN_HEIGHT / 2.0f - (0.5f * knight.height) * 4.0f
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction = {0.0f, 0.0f};

        if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
        if (IsKeyDown(KEY_D)) direction.x += 1.0f;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
        if (IsKeyDown(KEY_S)) direction.y += 1.0f;
        
        if (Vector2Length(direction) != 0.0)
        {
            direction = Vector2Normalize(direction);
            direction = Vector2Scale(direction, SPEED);
            map_pos = Vector2Subtract(map_pos, direction);
        }

        DrawTextureEx(map, map_pos, 0.0f, 4.0f, WHITE);

        Rectangle source = Rectangle{ 0, 0, knight.width / 6.0f, (float)knight.height };
        Rectangle dest = Rectangle{ knight_pos.x, knight_pos.y, 4.0f * knight.width / 6.0f, 4.0f * knight.height };
        DrawTexturePro(knight, source, dest, Vector2{0, 0}, 0.0f, WHITE);



        EndDrawing();
    }

    UnloadTexture(knight);
    UnloadTexture(map);
    CloseWindow();

    return 0;
}