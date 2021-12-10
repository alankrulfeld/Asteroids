#pragma once


namespace asteroids
{

	enum class Scenes
	{
		mainMenu = 1, game, credits, exit, instructions
	};
	extern Scenes scene;
	namespace menu
	{
		void init();
		void update();
		void draw();
		void deinit();
	}
}




