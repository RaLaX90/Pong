#include "Game_object.hpp"

#include "SDL_image.h"
Game_object::Game_object(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed)
{
	this->position_and_size.x = _start_position.X;
	this->position_and_size.y = _start_position.Y;
	this->position_and_size.w = _start_size.Width;
	this->position_and_size.h = _start_size.Height;

	this->speed.X = _start_speed.X;
	this->speed.Y = _start_speed.Y;

	this->image = IMG_LoadTexture(_renderer, _path_to_image);
	if (!image)
	{
		throw "Error at load image";
	}
}

Game_object::~Game_object()
{
	SDL_DestroyTexture(image);
}

void Game_object::Draw(SDL_Renderer* m_renderer)
{
	if (SDL_RenderCopy(m_renderer, image, nullptr, &position_and_size))  //0 is a success
	{
		throw SDL_GetError();
	}
}

void Game_object::SetPositionXY(int _X, int _Y)
{
	position_and_size.x = _X;
	position_and_size.y = _Y;
}

void Game_object::SetPositionX(int _X)
{
	position_and_size.x = _X;
}

void Game_object::SetPositionY(int _Y)
{
	position_and_size.y = _Y;
}

SDL_Rect Game_object::GetPositionAndSize() const
{
	return position_and_size;
}

const SDL_Rect* Game_object::GetPositionAndSizePointer() const
{
	return &position_and_size;
}

int Game_object::GetPositionX() const
{
	return position_and_size.x;
}

int Game_object::GetPositionY() const
{
	return position_and_size.y;
}

void Game_object::SetDirectionXY(int _X, int _Y)
{
	speed.X = _X;
	speed.Y = _Y;
}

void Game_object::SetDirectionX(int _X)
{
	speed.X = _X;
}

void Game_object::SetDirectionY(int _Y)
{
	speed.Y = _Y;
}

short Game_object::GetDirectionX() const
{
	return speed.X;
}

short Game_object::GetDirectionY() const
{
	return speed.Y;
}

int Game_object::GetWidth() const
{
	return position_and_size.w;
}

int Game_object::GetHeight() const
{
	return position_and_size.h;
}

void Game_object::Reset()
{

}