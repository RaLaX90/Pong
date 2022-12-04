#include <iostream>

#include "Game.hpp"

int main(int argc, char* argv[])
{
    Game pong_game;

    while (pong_game.GetState() == Game::State::STATE_OK)
    {
        pong_game.Update();
        pong_game.HandleEvents();
        pong_game.DrawAll();
    }

    return 0;
}