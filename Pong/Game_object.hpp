#pragma once

#include <SDL.h>
#include "SDL_image.h"

struct PositionStruct {
	int X;
	int Y;
};

struct SpeedStruct {
	short X;
	short Y;
};

struct SizeStruct {
	char Width;
	char Height;
};

class Game_object
{
protected:
	SDL_Texture* image;
	SDL_Rect position_and_size;

	SpeedStruct speed;

public:
	Game_object(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed);
	~Game_object();

	void Draw(SDL_Renderer* m_renderer);

	void SetPositionXY(int _X, int _Y);
	void SetPositionX(int _X);
	void SetPositionY(int _Y);

	SDL_Rect GetRect() const;
	const SDL_Rect* GetRectPointer();

	int GetPositionX() const;
	int GetPositionY() const;

	void SetDirectionXY(int _X, int _Y);
	void SetDirectionX(int _X);
	void SetDirectionY(int _Y);

	short GetDirectionX() const;
	short GetDirectionY() const;

	int GetWidth() const;
	int GetHeight() const;

	void Reset();
};