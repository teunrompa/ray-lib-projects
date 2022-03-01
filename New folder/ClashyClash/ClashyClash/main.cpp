#include "raylib.h"
#include "Game.h"
#include "Prop.h"

int main() {
	
	Game game;

	game.InitGame();

    while (!WindowShouldClose())
    {
        game.UpdateGame();
    }

    game.GameShouldStop();
}
