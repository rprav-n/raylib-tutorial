

#include <cstdio>
#include "raylib.h"

int main()
{

	const int width = 1280;
	const int height = 720;

	InitWindow(width, height, "Axe game");

	// cricle coords
	int circle_x = 100;
	int circle_y = 100;
	int circle_r = circle_x / 2;
	int l_circle_x = 0;
	int r_circle_x = 0;
	int u_circle_y = 0;
	int d_circle_y = 0;

	// axe coords
	int axe_x = 400;
	int axe_y = 0;
	int l_axe_x = 0;
	int r_axe_x = 0;
	int u_axe_y = 0;
	int d_axe_y = 0;
	int axe_length = 50;

	int direction = 10;

	bool collision_with_axe = false;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		if (collision_with_axe)
		{
			DrawText("Game Over", width / 2, height / 2, 24, RED);
		}
		else
		{

			// Input
			if (IsKeyDown(KEY_D))
			{
				circle_x += 10;
			}
			if (IsKeyDown(KEY_A))
			{
				circle_x -= 10;
			}

			axe_y += direction;
			if (axe_y > height - axe_length || axe_y < 0)
			{
				direction = -direction;
			}

			// wall detection
			if (circle_x + circle_r > width)
			{
				circle_x = width - circle_r;
			}
			if (circle_x - circle_r < 0)
			{
				circle_x = circle_r;
			}

			l_circle_x = circle_x - circle_r;
			r_circle_x = circle_x + circle_r;
			u_circle_y = circle_y - circle_r;
			d_circle_y = circle_y + circle_r;

			l_axe_x = axe_x;
			r_axe_x = axe_x + axe_length;
			u_axe_y = axe_y;
			d_axe_y = axe_y + axe_length;

			// collision detection
			if (d_axe_y >= u_circle_y && u_axe_y <= d_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x )
			{
				printf("You lose");
				collision_with_axe = true;
			}

			DrawCircle(circle_x, circle_y, circle_r, RED);
			DrawRectangle(axe_x, axe_y, axe_length, axe_length, BLUE);
		}



		EndDrawing();
	}

}
