#include "raylib.h"
#include <iostream>

struct AnimData
{
	Rectangle rect;
	Vector2 pos;
	int frame;
	float update_time;
	float running_time;
};

bool is_on_ground(AnimData data, int window_height)
{
	return data.pos.y >= window_height - data.rect.height;
}

AnimData update_anim_data(AnimData data, int vel, float dt, int max_frame)
{
	data.running_time += dt;
	if (data.running_time > data.update_time)
	{
		data.frame++;
		if (data.frame > max_frame)
		{
			data.frame = 0;
		}
		data.running_time = 0.0f;
	}

	return data;
}

float draw_background(Texture2D bg, float x_pos, int speed, float dt)
{
	x_pos -= speed * dt;
	if (x_pos <= -bg.width * 2)
	{
		x_pos = 0;
	}

	Vector2 bg_pos_1 = {x_pos, 0};
	DrawTextureEx(bg, bg_pos_1, 0.0f, 2.0f, WHITE);
	Vector2 bg_pos_2 = {x_pos + bg.width * 2, 0};
	DrawTextureEx(bg, bg_pos_2, 0.0f, 2.0f, WHITE);

	return x_pos;
}

int main()
{
	const int WINDOW_WIDTH = 512;
	const int WINDOW_HEIGHT = 380;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

	int velocity = 0;
	const int jump_vel = 800;

	const int GRAVITY = 1400;
	bool can_jump = true;

	float offset = 40.0f;
	bool collision = false;

	// backgrounds
	Texture2D background = LoadTexture("./textures/background.png");
	float bg_x = 0;

	Texture2D midground = LoadTexture("./textures/midground.png");
	float mg_x = 0;

	Texture2D foreground = LoadTexture("./textures/foreground.png");
	float fg_x = 0;

	// scarfy
	Texture2D scarfy = LoadTexture("./textures/scarfy.png");
	AnimData scarfy_data;
	scarfy_data.rect = Rectangle{0, 0, static_cast<float>(scarfy.width / 6), static_cast<float>(scarfy.height)}; // x, y, width, height
	scarfy_data.pos = Vector2{WINDOW_WIDTH / 2 - scarfy_data.rect.width / 2, WINDOW_HEIGHT - scarfy_data.rect.height};
	scarfy_data.frame = 0;
	scarfy_data.running_time = 0.0f;
	scarfy_data.update_time = 1.0f / 8.0f;

	// nebula
	int nebula_vel = 200;
	Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");

	const int SIZE_OF_NEBULAE = 6;
	AnimData nebulae[SIZE_OF_NEBULAE];

	for (int i = 0; i < SIZE_OF_NEBULAE; i++)
	{
		nebulae[i].rect = {0.0, 0.0, static_cast<float>(nebula.width / 8), static_cast<float>(nebula.height / 8)};
		nebulae[i].pos = {WINDOW_WIDTH, WINDOW_HEIGHT - nebulae[i].rect.height};
		nebulae[i].frame = 0;
		nebulae[i].running_time = 0.0f;
		nebulae[i].update_time = 1.0f / 12.0f;
	}
	for (int i = 0; i < SIZE_OF_NEBULAE; i++)
	{
		nebulae[i].pos.x = WINDOW_WIDTH + 300 * i;
	}

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		if (is_on_ground(scarfy_data, WINDOW_HEIGHT))
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

		scarfy_data.pos.y += velocity * dt;
		if (scarfy_data.pos.y >= WINDOW_HEIGHT - scarfy_data.rect.height)
		{
			scarfy_data.pos.y = WINDOW_HEIGHT - scarfy_data.rect.height;
		}

		if (can_jump)
		{
			scarfy_data = update_anim_data(scarfy_data, velocity, dt, 5);
		}

		scarfy_data.rect.x = scarfy_data.frame * scarfy_data.rect.width;

		for (int i = 0; i < SIZE_OF_NEBULAE; i++)
		{
			nebulae[i].pos.x -= nebula_vel * dt;
			nebulae[i] = update_anim_data(nebulae[i], nebula_vel, dt, 7);
		}

		for (int i = 0; i < SIZE_OF_NEBULAE; i++)
		{
			nebulae[i].rect.x = nebulae[i].frame * nebulae[i].rect.width;
		}

		// backgrounds
		bg_x = draw_background(background, bg_x, 20, dt);
		mg_x = draw_background(midground, mg_x, 40, dt);
		fg_x = draw_background(foreground, fg_x, 80, dt);

		if (nebulae[SIZE_OF_NEBULAE - 1].pos.x < scarfy_data.pos.x)
		{
			DrawText("You Win!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, WHITE);
		}

		for (AnimData nebula : nebulae)
		{
			Rectangle neb_rect = {nebula.pos.x + offset, nebula.pos.y + offset, nebula.rect.width - 2 * offset,
								  nebula.rect.height - 2 * offset};
			Rectangle scarfy_rect = {scarfy_data.pos.x,
									 scarfy_data.pos.y,
									 scarfy_data.rect.width,
									 scarfy_data.rect.height};

			if (CheckCollisionRecs(neb_rect, scarfy_rect))
			{
				collision = true;
			}
		}

		if (collision)
		{
			DrawText("Game Over", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, WHITE);
		}
		else
		{
			DrawTextureRec(scarfy, scarfy_data.rect, scarfy_data.pos, WHITE);
			// DrawRectangleLines(scarfy_data.pos.x, scarfy_data.pos.y, scarfy_data.rect.width, scarfy_data.rect.height, RED);

			for (int i = 0; i < SIZE_OF_NEBULAE; i++)
			{
				DrawTextureRec(nebula, nebulae[i].rect, nebulae[i].pos, WHITE);
				// DrawRectangleLines(nebulae[i].pos.x + offset, nebulae[i].pos.y + offset, nebulae[i].rect.width - 2 * offset,
				// 				   nebulae[i].rect.height - 2 * offset, RED);
			}
		}

		EndDrawing();
	}

	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	UnloadTexture(background);
	UnloadTexture(midground);
	UnloadTexture(foreground);

	CloseWindow();

	return 0;
}