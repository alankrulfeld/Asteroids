#include "raylib.h"
#include "credits.h"
#include "menu.h"
namespace asteroids
{
	namespace credits
	{

		Texture2D background;
		const int tam = 5;
		const int amountMenu = 3;
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
			button[static_cast<int>(Scenes::credits)].texture = LoadTexture("../res/texture/ui/BACK.png");
			for (size_t i = 0; i < 5; i++)
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
			if (CheckCollisionPointRec(GetMousePosition(), button[0].rec))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{

					scene = Scenes::mainMenu;




				}

			}
		}
		void draw()
		{

			DrawTexture(background, 0, 0, WHITE);
			DrawText("CREDITS ", 400 - button[static_cast<int>(Scenes::credits)].texture.width / 2-50, 60, 50, BLACK);


		
			DrawText("CUADRADOID by Alan Krulfeld ", 400 - button[static_cast<int>(Scenes::credits)].texture.width / 2 - 150, 200, 30, BLACK);

			DrawTexture(button[static_cast<int>(Scenes::credits)].texture, 100, 350, WHITE);

		}
		void deinit()
		{

		}
	}
}

