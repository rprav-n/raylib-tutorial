#include "raylib.h"

int main()
{
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

    int velocity = 0;
    const int jump_vel = 600;

    const int GRAVITY = 1800;
    bool can_jump = true;

    // scarfy
    Texture2D scarfy = LoadTexture("./textures/scarfy.png");
    Rectangle scarfy_rect;
    scarfy_rect.width = scarfy.width / 6;
    scarfy_rect.height = scarfy.height;
    scarfy_rect.x = 0;
    scarfy_rect.y = 0;

    Vector2 scarfy_pos;
    scarfy_pos.x = WINDOW_WIDTH / 2 - scarfy_rect.width / 2;
    scarfy_pos.y = WINDOW_HEIGHT - scarfy_rect.height;

    int frame = 0;
    const float update_time = 1.0f / 8.0f;
    float running_time = 0.0f;

    // nebula
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
    Rectangle nebula_rect = {0.0, 0.0, static_cast<float>(nebula.width / 8), static_cast<float>(nebula.height / 8)}; // x, y, width, height

    Vector2 nebula_pos = {WINDOW_WIDTH, WINDOW_HEIGHT - nebula_rect.height};
    int nebula_vel = 600;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfy_pos.y >= WINDOW_HEIGHT - scarfy_rect.height)
        {
            velocity = 0;
            can_jump = true;
        }
        else
        {
            velocity += GRAVITY * dt;
        }

        if (IsKeyPressed(KEY_SPACE) && can_jump)
        {
            velocity -= jump_vel;
            can_jump = false;
        }

        scarfy_pos.y += velocity * dt;
        if (scarfy_pos.y >= WINDOW_HEIGHT - scarfy_rect.height)
        {
            scarfy_pos.y = WINDOW_HEIGHT - scarfy_rect.height;
        }

        running_time += dt;
        if (running_time >= update_time && can_jump)
        {
            running_time = 0.0f;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        scarfy_rect.x = frame * scarfy_rect.width;

        nebula_pos.x -= nebula_vel * dt;

        DrawTextureRec(scarfy, scarfy_rect, scarfy_pos, WHITE);
        DrawTextureRec(nebula, nebula_rect, nebula_pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();

    return 0;
}