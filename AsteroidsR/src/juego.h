#ifndef juego_h
#define juego_h
#include "raylib.h"
namespace asteroids
{
	namespace game
	{
       struct Player
        {
            Vector2 position;
            Vector2 newPosition;
            Vector2 speed;
            float acceleration;
            float rotation;
            float newRotation;
            Vector3 collider;
            Color color;
            int height;
        } ;

      struct Meteors
        {
            Vector2 position;
            Vector2 speed;
            float radius;
            bool active;
            Color color;
        } ;

        struct Shoot
        {
            Vector2 position;
            Vector2 speed;
            float radius;
            float rotation;
            int lifeSpawn;
            bool active;
            Color color;
        } ;
		void init();
		void update();
		void draw();
		void deinit();
        void CollisionMeteorPlayer(Meteors x[], int index);
        void MeteorsMove(Meteors x[], int index);
        void ShootCollisions();
        void Restart();
	}
}
#endif // !1
