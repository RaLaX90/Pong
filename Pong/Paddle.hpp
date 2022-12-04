#pragma once
#include "Game_object.hpp"

class Paddle : public Game_object
{
	char m_score;
	SDL_Rect m_score_rect;

public:
	Paddle(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed, SDL_Rect _score_rect);
	~Paddle();

	void addScore();

	void MoveUp();
	void MoveDown(unsigned short _window_height);

	char GetScore() const;
	const SDL_Rect* GetScoreRectPointer();
};