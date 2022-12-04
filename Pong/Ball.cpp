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

bool Ball::isCollision(const SDL_Rect* _other) const
{
	return SDL_HasIntersection(&position_and_size, _other);
}

void Ball::Move(unsigned short _window_height, const SDL_Rect* _player1, const SDL_Rect* _player2)
{
	position_and_size.x += speed.X;
	position_and_size.y += speed.Y;

	if (position_and_size.y <= 0 || (position_and_size.y + position_and_size.h > _window_height)) //if ball trying to go beyond the bottom and top
	{
		speed.Y = -speed.Y;
	}
	else if (isCollision(_player1)) { //if collistion with first player
		if (position_and_size.x + abs(speed.X) < _player1->x + _player1->w) {
			speed.Y = -speed.Y;
		}
		else {
			speed.X = -speed.X;
		}
	}
	else if (isCollision(_player2)) { //if collistion with second player
		if ((position_and_size.x + position_and_size.w) - speed.X > _player2->x) {
			speed.Y = -speed.Y;
		}
		else {
			speed.X = -speed.X;
		}
	}
}