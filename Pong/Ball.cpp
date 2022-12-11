#include "Ball.hpp"

Ball::Ball(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed) :
	Game_object(_renderer, _path_to_image, _start_position, _start_size, _start_speed)
{
	speed.X = 5;
	speed.Y = 2;
}

Ball::~Ball()
{
}

void Ball::addSpeed()
{
	speed.X += 2;
	speed.Y += 2;
}

void Ball::Move()
{
	position_and_size.x += speed.X;
	position_and_size.y += speed.Y;
}