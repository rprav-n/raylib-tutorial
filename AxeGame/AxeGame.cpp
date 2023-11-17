

#include <cstdio>
#include "raylib.h"

int main()
{

    const int width = 600;
    const int height = 600;

    InitWindow(width, height, "Axe game");

    int circleX = 100;
    int circleY = 100;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyDown(KEY_RIGHT))
        {
            circleX += 2;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            circleX -= 2;
        }

        DrawCircle(circleX, circleY, 50, RED);

        EndDrawing();
    }

}
