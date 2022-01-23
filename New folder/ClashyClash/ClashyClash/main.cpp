#include "raylib.h"
#include "Game.h"

int main() {
	
	Game game;
	
	game.InitGame();

    while (!WindowShouldClose())
    {
        game.UpdateGame();
    }

    game.GameShouldStop();
}