#include "raylib.h"
#include "menu.h"
namespace asteroids
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
	namespace menu
	{
		void init()
		{
			InitAudioDevice();

			for (short i = 0; i < amountMenu; i++)
			{
				button[i].rec.width = button[i].texture.width;
				button[i].rec.x = 100;
				button[i].rec.height = button[i].texture.height;
			}
			button[0].rec.y = 350;


			button[static_cast<int>(Scenes::game)].texture = LoadTexture("../res/texture/ui/PLAY.png");
			button[static_cast<int>(Scenes::instructions)].texture = LoadTexture("../res/texture/ui/INSTRUCTIONS.png");

			button[static_cast<int>(Scenes::credits)].texture = LoadTexture("../res/texture/ui/CREDITS.png");
			button[static_cast<int>(Scenes::exit)].texture = LoadTexture("../res/texture/ui/EXIT.png");
			for (size_t i = 0; i < tam; i++)
			{

				button[i].texture.height = 80;
				button[i].texture.width = 150;

			}

			background.height = GetScreenHeight();
			background.width = GetScreenWidth();
			background = LoadTexture("../res/texture/ui/BACKGROUNDMENU.png");
			for (short i = 0; i < amountMenu; i++)
			{
				button[i].rec.width = button[i].texture.width;
				button[i].rec.x = 400 - button[i].rec.width / 2;
				button[i].rec.height = button[i].texture.height;
			}
			button[0].rec.y = 120;
			button[1].rec.y = 220;
			button[3].rec.y = 320;
			button[2].rec.y = 420;





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
							scene = Scenes::game;

							break;




						case 1:
							scene = Scenes::credits;
							break;

						case 2:
							CloseWindow();
						case 3:
							scene = Scenes::instructions;

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

			DrawText("CUDRADOID ", 300 - button[static_cast<int>(Scenes::game)].texture.width / 2, 60, 50, BLACK);
			DrawTexture(button[static_cast<int>(Scenes::game)].texture, 400 - button[static_cast<int>(Scenes::game)].texture.width / 2, 120, WHITE);
			DrawTexture(button[static_cast<int>(Scenes::credits)].texture, 400 - button[static_cast<int>(Scenes::game)].texture.width / 2, 220, WHITE);
			DrawTexture(button[static_cast<int>(Scenes::instructions)].texture, 400 - button[static_cast<int>(Scenes::game)].texture.width / 2, 320, WHITE);

			DrawTexture(button[static_cast<int>(Scenes::exit)].texture, 400 - button[static_cast<int>(Scenes::game)].texture.width / 2, 420, WHITE);

			

		}
		void deinit()
		{

		}
	}
}

