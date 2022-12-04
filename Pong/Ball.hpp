#pragma once

#include "Game_object.hpp"

class Ball : public Game_object
{
	void addSpeed();
	bool isCollision(const SDL_Rect* _other) const; //TODO (make parameters more optimized)

public:
	Ball(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed);
	~Ball();

	void Move(unsigned short _window_height, const SDL_Rect* _player1, const SDL_Rect* _player2);
};