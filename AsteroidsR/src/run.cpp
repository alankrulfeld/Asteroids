#include "menu.h"
#include "juego.h"
#include "raylib.h"
#include "credits.h"
#include "instructions.h"
namespace asteroids
{
	bool endGame = false;


	Scenes scene = Scenes::mainMenu;



	void init()
	{
		const int screenWidth = 800;
		const int screenHeight = 500;
		SetTargetFPS(60);
		SetExitKey(KEY_F4);

		game::init();
		menu::init();
		credits::init();
		instructions::init();



	}

	void update() 
	{

		switch (scene)
		{
		case Scenes::mainMenu:
			menu::update();
			break;

		case Scenes::game:
			game::update();
			break;

		case Scenes::credits:
			credits::update();
			break;
		case Scenes::instructions:
			instructions::update();
			break;
		
		default:
			break;
		}
	}

	void draw()
	{

		BeginDrawing();

		ClearBackground(WHITE);

		switch (scene)
		{
		case Scenes::mainMenu:
			menu::draw();
			break;

		case Scenes::game:
			game::draw();
			break;

		case Scenes::credits:
			credits::draw();
			break;
		case Scenes::instructions:
			instructions::draw();
			break;

			//case instructions:
			//	instructions::draw( );
			//	break;

		default:
			break;
		}

		EndDrawing();
	}

	void deinit()
	{
		menu::deinit();
		game::deinit();
		credits::deinit();
		instructions::deinit();

	}
	void runGame()
	{

		init();

		while (!WindowShouldClose() && !endGame)
		{
			update();
			draw();
		}

		deinit();
	}
}