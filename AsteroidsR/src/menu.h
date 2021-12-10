#ifndef menu_h
#define menu_h


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

#endif // !1



