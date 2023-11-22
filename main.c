#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUTTON_COLOUR RAYWHITE

int main(void) {	
	
	const int sides = 400;
	const char* title = "siner";
	const int fps = 40;	
	
	/* Wave colours */
	Color colours[] = {
		RAYWHITE, RED, GRAY, BLUE, LIGHTGRAY, YELLOW, GREEN, PINK, ORANGE,
			PURPLE };
	size_t colour_count = sizeof(colours) / sizeof(colours[0]);
	
	struct {
		double colour_code;
		double amplitude, frequency;
		double thickness, shift;
	} wave = { 0.0, 5.0, 0.2, 5.0, 0.0 };
	
	double mod_mode = 0;
	struct {
		int x, y;
		int width, height;
		char text[12];
		
		double step; // amount to add to target
		void* target; // ptr to target num or ptr to var name ("x", "y", etc.)
	} buttons[] = {
		{ 10, 20, 60, 20,  "[   +/-   ]",
			1.0, &mod_mode },
		{ 90, 20, 60, 20,  "[   amp   ]",
			1.0, &(wave.amplitude) },
		{ 170, 20, 60, 20, "[   frq   ]",
			1.0, &(wave.frequency) },
		{ 250, 20, 60, 20, "[   thk   ]",
			1.0, &(wave.thickness) },
		{ 330, 20, 60, 20, "[   sft   ]",
			1.0, &(wave.shift) },
		{ 170, 60, 60, 20, "[   col   ]",
			1.0, &(wave.colour_code) }
	};
	size_t button_count = sizeof(buttons) / sizeof(buttons[0]);

	InitWindow(sides, sides, title);
	SetTargetFPS(fps);

	int x = 0, right = 1;
	while (!WindowShouldClose()) {

		/* Detect button press */
		Vector2 mouse = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			for (int b = 0; b < button_count; b++) {
				if (mouse.x > buttons[b].x
						&& mouse.x < (buttons[b].x + buttons[b].width)
						&& mouse.y > buttons[b].y
						&& mouse.y < (buttons[b].y + buttons[b].height)) {
					*((double*)(buttons[b].target)) += mod_mode == 0
							? buttons[b].step : -(buttons[b].step);
					break;
				}
			}
		}

		/* Update the wave's state */
		right = x >= sides ? 0 : (x <= 0 ? 1 : right);
		x += (right ? 1 : -1);
		
		/* Draw the buttons + wave */
		BeginDrawing();
		ClearBackground(BLACK);

		for (int b = 0; b < button_count; b++) {
			DrawRectangle(buttons[b].x, buttons[b].y, buttons[b].width,
				buttons[b].height, BUTTON_COLOUR);
			DrawText(buttons[b].text, buttons[b].x + 5,
				buttons[b].y + 5, 10, BLACK);
		}
		
		/* Draw pixels individually */
		for (int j = 0; j < x; j++) {
			for (int w = -ceil(wave.thickness / 2); w < ceil(wave.thickness / 2); w++) {
				int y = floor(wave.amplitude * sin(wave.frequency * (j+w) + wave.shift));
				DrawPixel(j, y + (sides / 2), colours[(int)(wave.colour_code) % colour_count]);
			}
		}

		EndDrawing();
	}
	
	CloseWindow();

	return 0;
}

