//#include "raylib.h"
//
//int main(void)
//{
//
//	// Initialization
//	//--------------------------------------------------------------------------------------
//	const int screenWidth = 800;
//	const int screenHeight = 500;
//	int score1 = 0;
//	int score2 = 0;
//	struct Ball
//	{
//		Vector2 position;
//		Vector2 speed;
//		int radius;
//		bool active;
//		bool sideColision;
//	} ball;
//	ball.position.x = 400;
//	ball.position.y = 250;
//	ball.radius = 10;
//	ball.speed.x = 0;
//	ball.speed.y = 0;
//	ball.sideColision = false;
//	Rectangle player1;
//	player1.x = 20;
//	player1.y = 200;
//	player1.height = 80;
//	player1.width = 20;
//	Rectangle player2;
//	player2.x = 760;
//	player2.y = 200;
//	player2.height = 80;
//	player2.width = 20;
//	bool win = false;
//
//	InitWindow(screenWidth, screenHeight, "");
//
//	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//	//--------------------------------------------------------------------------------------
//
//	// Main game loop
//	while ( !WindowShouldClose( )  )    // Detect window close button or ESC key
//	{
//		
//
//			int timer = GetTime( );
//
//			// Update
//			//----------------------------------------------------------------------------------
//
//			if ( player1.y > 7 )
//			{
//				if ( IsKeyDown(KEY_W) ) player1.y -= 10;
//			}
//			if ( player1.y < screenHeight - 80 )
//			{
//				if ( IsKeyDown(KEY_S) ) player1.y += 10;
//			}
//			if ( player2.y > 7 )
//			{
//				if ( IsKeyDown(KEY_UP) )player2.y -= 10;
//			}
//			if ( player2.y < screenHeight - 80 )
//			{
//				if ( IsKeyDown(KEY_DOWN) ) player2.y += 10;
//			}
//
//			ball.position.x -= ball.speed.x;
//			ball.position.y -= ball.speed.y;
//
//			if ( ball.speed.x == 0 && ball.speed.y == 0 && IsKeyPressed(KEY_SPACE) )
//			{
//				if ( GetRandomValue(0, 1) == 0 )
//				{
//					ball.speed.x = 3;
//				}
//				else
//				{
//					ball.speed.x = -3;
//
//				}
//				if ( GetRandomValue(0, 1) == 0 )
//				{
//					ball.speed.y = 1;
//
//				}
//				else
//				{
//					ball.speed.y = -1;
//				}
//
//
//			}
//
//			if ( CheckCollisionCircleRec(ball.position, ball.radius, player1) && !ball.sideColision )
//			{
//				if ( ball.position.x - ball.radius / 2 + ball.speed.x > player1.x + player1.width )
//				{
//					ball.speed.x = -ball.speed.x;
//				}
//				else
//				{
//					ball.speed.y = -ball.speed.y;
//					ball.sideColision = true;
//				}
//
//			}
//			else if ( CheckCollisionCircleRec(ball.position, ball.radius, player2) && !ball.sideColision )
//			{
//				if ( ball.position.x + ball.radius / 2 + ball.speed.x < player2.x )
//				{
//					ball.speed.x = -ball.speed.x;
//				}
//				else
//				{
//					ball.speed.y = -ball.speed.y;
//					ball.sideColision = true;
//				}
//			}
//			if ( ball.position.y + ball.radius / 2 + ball.speed.x < 20 )
//			{
//				ball.speed.y = -ball.speed.y;
//			}
//			else if ( ball.position.y + ball.radius / 2 > screenHeight - 1 )
//			{
//				ball.speed.y = -ball.speed.y;
//
//			}
//
//
//			if ( ball.position.x < 0 )
//			{
//				score2++;
//				ball.position.y = 250;
//				ball.position.x = screenWidth / 2;
//				ball.speed.x = 0;
//				ball.speed.y = 0;
//				ball.sideColision = false;
//			}
//			if ( ball.position.x > 800 )
//			{
//				score1++;
//				ball.position.y = 250;
//				ball.position.x = screenWidth / 2;
//				ball.speed.x = 0;
//				ball.speed.y = 0;
//				ball.sideColision = false;
//			}
//
//			if ( timer % 1 == 0 && ball.speed.x > 0 )
//			{
//				ball.speed.x += 0.01;
//			}
//			else if ( timer % 1 == 0 && ball.speed.x < 0 )
//			{
//				ball.speed.x -= 0.01;
//			}
//			if ( timer % 1 == 0 && ball.speed.y > 0 )
//			{
//				ball.speed.y += 0.001;
//			}
//			else if ( timer % 1 == 0 && ball.speed.y < 0 )
//			{
//				ball.speed.y -= 0.001;
//			}
//
//
//
//			// TODO: Update your variables here
//			//----------------------------------------------------------------------------------
//
//			// Draw
//			//----------------------------------------------------------------------------------
//			BeginDrawing( );
//
//			for ( int linea = 0; linea < screenHeight; linea += 40 )
//			{
//				DrawRectangle(400, linea, 5, 20, GRAY);
//
//			}
//			DrawRectangleRec(player1, WHITE);
//			DrawRectangleRec(player2, WHITE);
//
//			DrawCircle(ball.position.x, ball.position.y, ball.radius, WHITE);
//
//			ClearBackground(BLACK);
//
//			DrawText(TextFormat("SCORE %4i", score1), 120, 20, 20, LIGHTGRAY);
//			DrawText(TextFormat("SCORE %4i", score2), 600, 20, 20, LIGHTGRAY);
//
//
//			EndDrawing( );
//			//----------------------------------------------------------------------------------
//		
//	}
//
//	// De-Initialization
//	//--------------------------------------------------------------------------------------
//	CloseWindow( );        // Close window and OpenGL context
//	//--------------------------------------------------------------------------------------
//
//}
//
//
