#include "Paddle.hpp"

Paddle::Paddle(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed, SDL_Rect _score_rect) :
	Game_object(_renderer, _path_to_image, _start_position, _start_size, _start_speed), m_score_rect(_score_rect)
{
	m_score = 0;
}

Paddle::~Paddle()
{
}

void Paddle::addScore()
{
	m_score++;
}

void Paddle::MoveUp()
{
	if (position_and_size.y > 50) //can't reach the end of the top of the screen
	{
		position_and_size.y -= speed.Y;
	}
}

void Paddle::MoveDown(unsigned short _window_height)
{
	if (position_and_size.y + position_and_size.h < _window_height)
	{
		position_and_size.y += speed.Y;
	}
}

char Paddle::GetScore() const
{
	return m_score;
}

const SDL_Rect* Paddle::GetScoreRectPointer()
{
	return &m_score_rect;
}
