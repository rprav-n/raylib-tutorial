#include "raylib.h"

class Character
{
public:
    Character();
    Vector2 getWorldPos() { return world_pos; }
    void setPos(int win_width, int win_height); // function prototype
    void tick(float dt);

private:
    Texture2D texture = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("./characters/knight_run_spritesheet.png");
    Vector2 pos = {};
    Vector2 world_pos = {};

    float width = {};
    float height = {};

    // 1: right, -1: left
    float right_left = {1.f};

    // animation variables
    const float UPDATE_TIME = 1.f / 12.f;
    float running_time = 0.f;
    int frame = 1;
    const int MAX_FRAMES = 6;
    const float SCALE = {4.f};
};
