#include "raylib.h"

int main()
{
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

    int velocity = 0;
    const int jump_vel = 20;

    const int GRAVITY = 1;
    bool can_jump = true;

    Texture2D scarfy = LoadTexture("./textures/scarfy.png");
    Rectangle scarfy_rect;
    scarfy_rect.width = scarfy.width / 6;
    scarfy_rect.height = scarfy.height;
    scarfy_rect.x = 0;
    scarfy_rect.y = 0;

    Vector2 scarfy_pos;
    scarfy_pos.x = WINDOW_WIDTH / 2 - scarfy_rect.width / 2;
    scarfy_pos.y = WINDOW_HEIGHT - scarfy_rect.height;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfy_pos.y >= WINDOW_HEIGHT - scarfy_rect.height)
        {
            velocity = 0;
            scarfy_pos.y = WINDOW_HEIGHT - scarfy_rect.height;
            can_jump = true;
        }
        else
        {
            velocity += GRAVITY;
        }

        if (IsKeyPressed(KEY_SPACE) && can_jump)
        {
            velocity -= jump_vel;
            can_jump = false;
        }

        scarfy_pos.y += velocity;

        DrawTextureRec(scarfy, scarfy_rect, scarfy_pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}