#include "juego.h"
#include <iostream>
#include "menu.h"
#define PLAYER_BASE_SIZE  20.0f
#define METEORS_SPEED   3.0f 
namespace asteroids
{

	namespace game
	{

			Texture2D backgrounds;


			Rectangle player1;
		
			const int screenWidth = 800;
			const int screenHeight = 500;

			Music musicPunch;
			Music musicGameplay;
			float PLAYER_SPEED = 3.0f;


			const int maxSmallMeteor = 20;
			const int maxMediumMeteor = 10;
			const int maxBigMeteor = 3;
			const int maxPlayerShoots = 3;

			static float shipHeight = 0.0f;

			static Player player = { 0 };
			static Meteors smallMeteor[maxSmallMeteor] = { 0 };
			static Meteors mediumMeteor[maxMediumMeteor] = { 0 };
			static Meteors bigMeteor[maxBigMeteor] = { 0 };
			static Shoot shoot[maxPlayerShoots] = { 0 };

			int framesCounter = 0;

			Vector2 posNave;
			Vector2 posMouse;
			Vector2 vectorDirection;
			Vector2 normalizedDirection;

			float angle = 0;

			static int midMeteorsCount = 0;
			static int smallMeteorsCount = 0;
			static int destroyedMeteorsCount = 0;

			bool correctRangeMeteors = false;
			bool gameOver = false;
			bool gameFinished = false;
			bool pause = false;

			float timePlayed = 0.0f;

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

				float posX;
				float posY;

				float velX;
				float velY;

				const float meteorsSpeed = 2.0f;
				gameFinished = false;
				gameOver = false;

				framesCounter = 0;

				shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);

				player.position = Vector2{ screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
				player.speed = Vector2{ 0, 0 };
				player.acceleration = 50;
				player.rotation = 0;
				player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f), 12 };
				player.color = RED;

				destroyedMeteorsCount = 0;

				for (int i = 0; i < maxPlayerShoots; i++)
				{
					shoot[i].position = Vector2{ 0, 0 };
					shoot[i].speed = Vector2{ 0, 0 };
					shoot[i].radius = 2;
					shoot[i].active = false;
					shoot[i].lifeSpawn = 0;
					shoot[i].color = WHITE;
				}

				for (int i = 0; i < maxMediumMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;

					}
					mediumMeteor[i].position = Vector2{ posX, posY };
					mediumMeteor[i].speed = Vector2{ velX, velY };
					mediumMeteor[i].radius = 20;
					mediumMeteor[i].active = true;
					mediumMeteor[i].color = BLUE;
				}

				for (int i = 0; i < maxSmallMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;
					}
					smallMeteor[i].position = Vector2{ posX, posY };
					smallMeteor[i].speed = Vector2{ velX, velY };
					smallMeteor[i].radius = 10;
					smallMeteor[i].active = true;
					smallMeteor[i].color = BLUE;
				}

				for (int i = 0; i < maxBigMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;
					}
					bigMeteor[i].position = Vector2{ posX, posY };
					bigMeteor[i].speed = Vector2{ velX, velY };
					bigMeteor[i].radius = 30;
					bigMeteor[i].active = true;
					bigMeteor[i].color = BLUE;
				}

				SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
				//--------------------------------------------------------------------------------------
			}

			void update()
			{
				UpdateMusicStream(musicPunch);
				UpdateMusicStream(musicGameplay);

				if (!gameFinished)
				{
					if (IsKeyPressed('P')) pause = !pause;

					if (!pause)
					{
						framesCounter++;



						// Player logic

						player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (player.height / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (player.height / 2.5f), 12 };

						if (!CheckCollisionPointCircle(GetMousePosition(), player.position, player.collider.z))
						{
							player.newPosition = player.position;
							player.newRotation = player.rotation;


							// Rotation   

							posMouse = GetMousePosition(); // Get destination position

							vectorDirection = { posMouse.x - player.position.x , posMouse.y - player.position.y }; // Subtact two vectors

							angle = atan2f(vectorDirection.y, vectorDirection.x) * (180.0f / PI); // Calculate arc tangent

							// Add degrees to the position the ship is watching
							if (vectorDirection.y > 0 && vectorDirection.x > 0) angle += 90.0f;
							else if (vectorDirection.y > 0 && vectorDirection.x < 0) angle += 90.0f;
							else if (vectorDirection.y < 0 && vectorDirection.x > 0) angle += 90.0f;
							else angle += 90.0f;

							player.rotation = angle; // Define rotation as the angle calculated before

						}

						if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON && !CheckCollisionPointCircle(GetMousePosition(), player.position, player.collider.z)))
						{
							// Speed
							player.speed.x = sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
							player.speed.y = cos(player.rotation * DEG2RAD) * PLAYER_SPEED;
						}


						player.position.x += (player.speed.x * player.acceleration * GetFrameTime());
						player.position.y -= (player.speed.y * player.acceleration * GetFrameTime());

						player.newRotation = player.rotation;

						// Wall behaviour for player
						if (player.position.x > screenWidth + player.height) player.position.x = -(player.height);
						else if (player.position.x < -(player.height)) player.position.x = screenWidth + player.height;
						else if (player.position.y > (screenHeight + player.height)) player.position.y = -(player.height);
						else if (player.position.y < -(player.height)) player.position.y = screenHeight + player.height;


						player.newPosition.x = player.position.x;
						player.newPosition.y = player.position.y;

						// Meteor logic

						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
						{
							for (int i = 0; i < maxPlayerShoots; i++)
							{
								if (!shoot[i].active)
								{
									shoot[i].position = Vector2{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight) };
									shoot[i].active = true;
									shoot[i].speed.x = 1.5 * sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
									shoot[i].speed.y = 1.5 * cos(player.rotation * DEG2RAD) * PLAYER_SPEED;
									shoot[i].rotation = player.rotation;
									break;
								}
							}
						}

						// Shoot life timer
						for (int i = 0; i < maxPlayerShoots; i++)
						{
							if (shoot[i].active) shoot[i].lifeSpawn++;
						}

						// Shot logic
						for (int i = 0; i < maxPlayerShoots; i++)
						{
							if (shoot[i].active)
							{
								// Movement
								shoot[i].position.x += shoot[i].speed.x;
								shoot[i].position.y -= shoot[i].speed.y;

								// Collision logic: shoot vs walls
								if (shoot[i].position.x > screenWidth + shoot[i].radius)
								{
									shoot[i].active = false;
									shoot[i].lifeSpawn = 0;
								}
								else if (shoot[i].position.x < 0 - shoot[i].radius)
								{
									shoot[i].active = false;
									shoot[i].lifeSpawn = 0;
								}
								if (shoot[i].position.y > screenHeight + shoot[i].radius)
								{
									shoot[i].active = false;
									shoot[i].lifeSpawn = 0;
								}
								else if (shoot[i].position.y < 0 - shoot[i].radius)
								{
									shoot[i].active = false;
									shoot[i].lifeSpawn = 0;
								}

								// Life of shoot
								if (shoot[i].lifeSpawn >= 60)
								{
									shoot[i].position = Vector2{ 0, 0 };
									shoot[i].speed = Vector2{ 0, 0 };
									shoot[i].lifeSpawn = 0;
									shoot[i].active = false;
								}
							}
						}


						CollisionMeteorPlayer(bigMeteor, maxBigMeteor);

						CollisionMeteorPlayer(mediumMeteor,maxMediumMeteor);
						CollisionMeteorPlayer(smallMeteor, maxSmallMeteor);


						//meteors move
						MeteorsMove(bigMeteor, maxBigMeteor);
						MeteorsMove(mediumMeteor, maxMediumMeteor);
						MeteorsMove(smallMeteor, maxSmallMeteor);


						// Collision logic: player-shoots vs meteors
						ShootCollisions();
						



					}

				}
				if (gameFinished)
				{
					if (IsKeyPressed(KEY_ENTER))
					{
						Restart();
						scene = Scenes::mainMenu;
					}
				}
				if (IsKeyPressed(KEY_M))
				{
					gameFinished = false;
					Restart();
					scene = Scenes::mainMenu;
				}

			}
			void draw()
			{

				// Draw
				//----------------------------------------------------------------------------------



				ClearBackground(WHITE);

				DrawTexture(backgrounds, 0, 0, WHITE);


				if (!gameFinished)
				{
					// Draw spaceship
					Vector2 v1 = { player.newPosition.x + sinf(player.newRotation * DEG2RAD) * (shipHeight), player.newPosition.y - cosf(player.newRotation * DEG2RAD) * (shipHeight) };
					Vector2 v2 = { player.newPosition.x - cosf(player.newRotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), player.newPosition.y - sinf(player.newRotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) };
					Vector2 v3 = { player.newPosition.x + cosf(player.newRotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), player.newPosition.y + sinf(player.newRotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) };
					DrawTriangle(v1, v2, v3, RED);

					// Draw meteor
					for (int i = 0; i < maxBigMeteor; i++)
					{
						if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, BLUE);
					}

					for (int i = 0; i < maxMediumMeteor; i++)
					{
						if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, BLUE);
					}

					for (int i = 0; i < maxSmallMeteor; i++)
					{
						if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, BLUE);
					}

					// Draw shoot
					for (int i = 0; i < maxPlayerShoots; i++)
					{
						if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
					}

					if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 30) / 2, screenHeight / 2 - 40, 30, BLACK);

					DrawText(TextFormat("TIME: %.02f", (float)framesCounter / 60), 10, 10, 20, BLACK);

				}
				else
				{
					if (gameFinished)
					{
						DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 20) / 2, screenHeight / 2, 20, BLACK);
						DrawText(TextFormat("TIME: %.02f", (float)framesCounter / 60 ), screenHeight / 1.5, 20,20, BLACK);

						DrawText("Press ENTER to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 100, 20, BLACK);
					}
				}





				//----------------------------------------------------------------------------------
			}

			void deinit()
			{


				CloseWindow();        // Close window and OpenGL context
				//--------------------------------------------------------------------------------------

			}

			void CollisionMeteorPlayer(Meteors x[],int index)
			{

				for (int a = 0; a < index; a++)
				{
					if (CheckCollisionCircles(Vector2{ player.collider.x, player.collider.y }, player.collider.z, x[a].position, x[a].radius) && x[a].active)
					{
						PlayMusicStream(musicPunch);
						gameFinished = true;
						gameOver = true;
					}
				}
				 
			}
			void MeteorsMove(Meteors x[], int index)
			{
				for (int i = 0; i < index; i++)
				{
					if (x[i].active)
					{

						x[i].position.x += x[i].speed.x;
						x[i].position.y += x[i].speed.y;


						if (x[i].position.x > screenWidth + x[i].radius) x[i].position.x = -(x[i].radius);
						else if (x[i].position.x < 0 - x[i].radius) x[i].position.x = screenWidth + x[i].radius;
						if (x[i].position.y > screenHeight + x[i].radius) x[i].position.y = -(x[i].radius);
						else if (x[i].position.y < 0 - x[i].radius) x[i].position.y = screenHeight + x[i].radius;
					}
				}
			}
			void ShootCollisions()
			{
				for (int i = 0; i < maxPlayerShoots; i++)
				{
					if ((shoot[i].active))
					{
						for (int a = 0; a < maxBigMeteor; a++)
						{
							if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
							{
								shoot[i].active = false;
								shoot[i].lifeSpawn = 0;
								bigMeteor[a].active = false;
								destroyedMeteorsCount++;

								for (int j = 0; j < 2; j++)
								{
									if (midMeteorsCount % 2 == 0)
									{
										mediumMeteor[midMeteorsCount].position = Vector2{ bigMeteor[a].position.x, bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 };
									}
									else
									{
										mediumMeteor[midMeteorsCount].position = Vector2{ bigMeteor[a].position.x, bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED };
									}

									mediumMeteor[midMeteorsCount].active = true;
									midMeteorsCount++;
								}
								bigMeteor[a].color = BLUE;
								a = maxBigMeteor;
							}
						}

						for (int b = 0; b < maxMediumMeteor; b++)
						{
							if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
							{
								shoot[i].active = false;
								shoot[i].lifeSpawn = 0;
								mediumMeteor[b].active = false;
								destroyedMeteorsCount++;

								for (int j = 0; j < 2; j++)
								{
									if (smallMeteorsCount % 2 == 0)
									{
										smallMeteor[smallMeteorsCount].position = Vector2{ mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 };
									}
									else
									{
										smallMeteor[smallMeteorsCount].position = Vector2{ mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED };
									}

									smallMeteor[smallMeteorsCount].active = true;
									smallMeteorsCount++;
								}
								mediumMeteor[b].color = BLUE;
								b = maxMediumMeteor;
							}
						}

						for (int c = 0; c < maxSmallMeteor; c++)
						{
							if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
							{


								shoot[i].active = false;
								shoot[i].lifeSpawn = 0;
								smallMeteor[c].active = false;
								destroyedMeteorsCount++;
								smallMeteor[c].color = BLUE;
								c = maxSmallMeteor;
							}
						}
					}
				}
			}
			void Restart()
			{
				float posX;
				float posY;

				float velX;
				float velY;

				const float meteorsSpeed = 2.0f;
				gameFinished = false;
				gameOver = false;

				framesCounter = 0;

				shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);

				player.position = Vector2{ screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
				player.speed = Vector2{ 0, 0 };
				player.acceleration = 50;
				player.rotation = 0;
				player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f), 12 };
				player.color = RED;

				destroyedMeteorsCount = 0;

				for (int i = 0; i < maxPlayerShoots; i++)
				{
					shoot[i].position = Vector2{ 0, 0 };
					shoot[i].speed = Vector2{ 0, 0 };
					shoot[i].radius = 2;
					shoot[i].active = false;
					shoot[i].lifeSpawn = 0;
					shoot[i].color = WHITE;
				}

				for (int i = 0; i < maxMediumMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;

					}
					mediumMeteor[i].position = Vector2{ posX, posY };
					mediumMeteor[i].speed = Vector2{ velX, velY };
					mediumMeteor[i].radius = 20;
					mediumMeteor[i].active = true;
					mediumMeteor[i].color = BLUE;
				}

				for (int i = 0; i < maxSmallMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;
					}
					smallMeteor[i].position = Vector2{ posX, posY };
					smallMeteor[i].speed = Vector2{ velX, velY };
					smallMeteor[i].radius = 10;
					smallMeteor[i].active = true;
					smallMeteor[i].color = BLUE;
				}

				for (int i = 0; i < maxBigMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;
					}
					bigMeteor[i].position = Vector2{ posX, posY };
					bigMeteor[i].speed = Vector2{ velX, velY };
					bigMeteor[i].radius = 30;
					bigMeteor[i].active = true;
					bigMeteor[i].color = BLUE;
				}
				gameFinished = false;
				framesCounter = 0;
				player.position = Vector2{ screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
				player.speed = Vector2{ 0, 0 };
				player.acceleration = 50;
				player.rotation = 0;
				player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f), 12 };
				player.color = RED;

				destroyedMeteorsCount = 0;

				for (int i = 0; i < maxPlayerShoots; i++)
				{
					shoot[i].position = Vector2{ 0, 0 };
					shoot[i].speed = Vector2{ 0, 0 };
					shoot[i].radius = 2;
					shoot[i].active = false;
					shoot[i].lifeSpawn = 0;
					shoot[i].color = WHITE;
				}

				for (int i = 0; i < maxMediumMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;

					}
					mediumMeteor[i].position = Vector2{ posX, posY };
					mediumMeteor[i].speed = Vector2{ velX, velY };
					mediumMeteor[i].radius = 20;
					mediumMeteor[i].active = true;
					mediumMeteor[i].color = BLUE;
				}

				for (int i = 0; i < maxSmallMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;
					}
					smallMeteor[i].position = Vector2{ posX, posY };
					smallMeteor[i].speed = Vector2{ velX, velY };
					smallMeteor[i].radius = 10;
					smallMeteor[i].active = true;
					smallMeteor[i].color = BLUE;
				}

				for (int i = 0; i < maxBigMeteor; i++)
				{
					posX = GetRandomValue(0, screenWidth);

					while (!correctRangeMeteors)
					{
						if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;

					posY = GetRandomValue(0, screenHeight);

					while (!correctRangeMeteors)
					{
						if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
						else correctRangeMeteors = true;
					}

					correctRangeMeteors = false;
					velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
					velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

					while (!correctRangeMeteors)
					{
						if (velX == 0 && velY == 0)
						{
							velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
							velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
						}
						else correctRangeMeteors = true;
					}
					bigMeteor[i].position = Vector2{ posX, posY };
					bigMeteor[i].speed = Vector2{ velX, velY };
					bigMeteor[i].radius = 30;
					bigMeteor[i].active = true;
					bigMeteor[i].color = BLUE;
				}

			}
	}
}




