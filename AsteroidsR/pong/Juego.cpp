#pragma once
#include "juego.h"
#include <iostream>

namespace asteroids
{

	namespace game
	{
		
		Texture2D backgrounds;
	
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

		void playerInput()
		{
			  GetMousePosition();
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{

			}

		}
	}
}


