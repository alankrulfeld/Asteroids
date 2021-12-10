#include "raylib.h"
#include "instructions.h"
#include "menu.h"
namespace asteroids
{
	namespace instructions
	{

		Texture2D background;
		const int tam = 6;
		const int amountMenu = 4;
		struct Button
		{
			Rectangle rec;
			Texture2D texture;
		};
		Button button[tam];
		void init()
		{
			background = LoadTexture("../res/texture/ui/BACKGROUNDMENU.png");

			background.height = GetScreenHeight();
			background.width = GetScreenWidth();
			button[static_cast<int>(Scenes::instructions)].texture = LoadTexture("../res/texture/ui/BACK.png");
			for (size_t i = 0; i < tam; i++)
			{

				button[i].texture.height = 80;
				button[i].texture.width = 150;

			}


			for (short i = 0; i < amountMenu; i++)
			{
				button[i].rec.width = button[i].texture.width;
				button[i].rec.x = 100;
				button[i].rec.height = button[i].texture.height;
			}
			button[0].rec.y = 350;


		}
		void update()
		{
			for (int i = 0; i < (tam); i++)
			{
				if (CheckCollisionPointRec(GetMousePosition(), button[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						switch (i)
						{
						case 0:
							scene = Scenes::mainMenu;
							break;


						default:

							break;
						}
					}

				}
			}
		}
		void draw()
		{

			DrawTexture(background, 0, 0, WHITE);
			DrawText("INSTRUCCIONES ", 400 - button[static_cast<int>(Scenes::instructions)].texture.width / 2 - 50, 60, 50, BLACK);



			DrawText(("Asteroids is a simple game where a ship must avoid crashing with tons of asteroids."), 15, 150, 19, BLACK);
			DrawText(("You are given the possibility to shoot to break this rocks into smaller pieces."), 15, 180, 19, BLACK);
			DrawText(("You win if you survive 60 seconds or break all asteroids."), 15, 210, 20, BLACK);
			DrawText(("Right mouse button to move - Left mouse button to shoot."), 15, 240, 20, BLACK);
			DrawText(("P to pause"), 15, 270, 20, BLACK);
			DrawText("Press M to return to menu", 15, 300, 20, BLACK);

			DrawTexture(button[static_cast<int>(Scenes::instructions)].texture, 100, 350, WHITE);

		}
		void deinit()
		{

		}
	}
}

