#pragma once

#include "Game_object.hpp"

class Ball : public Game_object
{
	void addSpeed();

public:
	Ball(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed);
	~Ball();

	void Move();
};