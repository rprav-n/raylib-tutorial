#include <cstdio>
#include "raylib.h"
#include "Character.h"

int main()
{
    const int WIN_WIDTH = 384;
    const int WIN_HEIGHT = 384;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Classy Clash");

    Texture2D map = LoadTexture("./nature_tileset/background.png");
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