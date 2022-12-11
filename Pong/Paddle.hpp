#pragma once

#include "Game_object.hpp"

#include <string>

#include <SDL_ttf.h>

class Paddle : public Game_object
{
	char m_score;
	TTF_Font* m_score_font; //TODO (make with smart pointer)
	SDL_Rect m_score_rect;

public:
	Paddle(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed, SDL_Rect _score_rect);
	~Paddle();

	void AddScore();

	void DrawScore(SDL_Renderer* _renderer);

	void MoveUp();
	void MoveDown(unsigned short _window_height);

	void AIMove(unsigned short _window_height, const SDL_Rect* _ball_position_and_size);

	char GetScore() const;
	const SDL_Rect* GetScoreRectPointer() const;
};