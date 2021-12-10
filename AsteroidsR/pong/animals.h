#pragma once
#include "raylib.h"
namespace asteroids
{
	namespace game
	{
		const int tam = 5;
		const int amountMenu = 3;
		enum class BLOCKTYPE
		{
			CAT,
			OWL,
			RAINBOW,
			NONE
		};
		struct object
		{
			bool onSelection;
			bool active;
			Texture2D textureOff;
			Texture2D textureOn;
			BLOCKTYPE type;
			Rectangle rec;
		};
		void InitAnimals();
		void AnimationAnimals();
		void MakeAnimals();
	}

}