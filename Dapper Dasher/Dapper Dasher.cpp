#include "raylib.h"

int main()
{
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

    int velocity = 0;
    const int jump_vel = 700;

    const int GRAVITY = 1600;
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
    Rectangle nebula_rect = { 0.0, 0.0, static_cast<float>(nebula.width / 8), 
        static_cast<float>(nebula.height / 8) }; // x, y, width, height

    Vector2 nebula_pos = { WINDOW_WIDTH, WINDOW_HEIGHT - nebula_rect.height };
    int nebula_vel = 200;
    int nebula_frame = 0;
    float nebula_running_time = 0.0f;

    Rectangle nebula_rect_2 = { 0.0, 0.0, static_cast<float>(nebula.width / 8),
        static_cast<float>(nebula.height / 8) };
    Vector2 nebula_pos_2 = { WINDOW_WIDTH + 200, WINDOW_HEIGHT - nebula_rect_2.height };
    int nebula_frame_2 = 0;
    float nebula_running_time_2 = 0.0f;


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

        if (can_jump)
        {
            running_time += dt;
            if (running_time >= update_time)
            {
                running_time = 0.0f;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        scarfy_rect.x = frame * scarfy_rect.width;
       
        nebula_pos.x -= nebula_vel * dt;
        nebula_running_time += dt;
        if (nebula_running_time > update_time)
        {
            nebula_frame++;
            if (nebula_frame > 7) {
                nebula_frame = 0;
            }
            nebula_running_time = 0.0f;
        }
        nebula_rect.x = nebula_frame * nebula_rect.width;

        nebula_pos_2.x -= nebula_vel * dt;
        nebula_running_time_2 += dt;
        if (nebula_running_time_2 > update_time)
        {
            nebula_frame_2++;
            if (nebula_frame_2 > 7)
            {
                nebula_frame_2 = 0;
            }
            nebula_running_time_2 = 0.0f;
        }
        nebula_rect_2.x = nebula_frame_2 * nebula_rect_2.width;
        

        DrawTextureRec(scarfy, scarfy_rect, scarfy_pos, WHITE);
        DrawTextureRec(nebula, nebula_rect, nebula_pos, WHITE);
        DrawTextureRec(nebula, nebula_rect_2, nebula_pos_2, RED);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();

    return 0;
}