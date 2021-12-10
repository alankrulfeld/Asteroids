#pragma once

#include "raylib.h"


namespace asteroids
{

	namespace game
	{
		struct MeteorClass
		{
			Rectangle body;
			Vector2 speed;
			bool active;
			Color color;
		} ;
		
		struct FireClass
		{
			Rectangle body;
			Vector2 speed;
			bool active;
			bool Colision;
		} ;
		struct PlayerClass
		{
			Rectangle body;
			Vector2 speed;
			float acceleration;
			float rotation;
			Color color;
		} ;
		void init();
		void update();
		void draw();
		void deinit();
	}
}

