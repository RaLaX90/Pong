#pragma once

#include "Window.hpp"
#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <random>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Global.hpp"

class Game
{
public:
	enum State { 
		STATE_OK = 0,
		STATE_EXIT,
		STATE_PAUSE
	};

private:
	State state;

	std::uint32_t current_time;

	std::unique_ptr<Paddle> player1;
	std::unique_ptr<Paddle> player2;

	std::unique_ptr<Ball> ball;

	SDL_Event event;

	uint16_t m_actual_fps;				// current FPS.
	uint8_t m_desired_fps;		// The desired FPS for the game.

	//std::random_device m_rd;
	//std::mt19937 m_generator;											// generator for distribution
	//std::uniform_int_distribution<short> m_distribution_screen_width;	// object for random distribution of m_screen_width
	//std::uniform_int_distribution<short> m_distribution_screen_height;	// object for random distribution of m_screen_height

	//std::uniform_int_distribution<short> m_distribution_direction_x;
	//std::uniform_int_distribution<short> m_distribution_direction_y;

	void resetRound();
	void drawScore();

public:
	Game();
	~Game();

	void Update();
	void HandleEvents();
	void DrawAll();

	State GetState() const;
};