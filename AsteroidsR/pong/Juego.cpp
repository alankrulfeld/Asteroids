#include "raylib.h"
#include "juego.h"
#include <iostream>
#include "menu.h"
//struct Ball
//{
//	Vector2 position;
//	Vector2 speed;
//	int radius;
//	bool active;
//	bool sideColision;
//	Texture2D texture;
//} ball;
namespace asteroids
{

	namespace game
	{
		const int tam = 5;
		const int amountMenu = 3;
		

		struct Button
		{
			Rectangle rec;
			Texture2D texture;
		};
		Button button[tam];
		Texture2D backgrounds;
	

		Rectangle player1;
		Rectangle player2;
		const int screenWidth = 800;
		const int screenHeight = 500;
	
		Music musicPunch;
		Music musicGameplay;

		void init()
		{


			// Initialization
			//--------------------------- 
			InitWindow(screenWidth, screenHeight, "");
			backgrounds = LoadTexture("../res/texture/ui/BACKGROUNDMENU.png");
			InitAudioDevice();
			button[static_cast<int>(Scenes::game)].texture = LoadTexture("../res/texture/ui/BACK.png");
			
			musicPunch = LoadMusicStream("../res/audio/explosion_estrella.ogg");
			musicGameplay = LoadMusicStream("../res/audio/Musica_gameplay.ogg");
			PlayMusicStream(musicGameplay);
			SetMusicVolume(musicGameplay, 0.5);
			musicGameplay.looping = true;

			
			SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
			//--------------------------------------------------------------------------------------
		}

		void update()
		{
			UpdateMusicStream(musicPunch);
			UpdateMusicStream(musicGameplay);




		}
		void draw()
		{

			// Draw
			//----------------------------------------------------------------------------------
		
				
			
			DrawTexture(backgrounds, 0, 0, WHITE);
			
			

			ClearBackground(WHITE);


			//----------------------------------------------------------------------------------
		}

		void deinit()
		{
			

			CloseWindow();        // Close window and OpenGL context
			//--------------------------------------------------------------------------------------

		}


	}
}




