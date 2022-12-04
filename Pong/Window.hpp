#pragma once

#include <SDL.h>
#include "SDL_image.h"

class Window
{
	Window(short _width, short _height, short _map_width, short _map_height);
	~Window();

	static Window* m_window;

	unsigned short m_screen_width = 0, m_screen_height = 0, m_map_width = 0, m_map_height = 0;		// playing field m_screen_width and m_screen_height
	unsigned short m_top_border_Y = 0, m_left_border_X = 0, m_bottom_border_Y = 0, m_right_border_X = 0;		// playing field m_screen_width and m_screen_height

	SDL_Window* m_sdl_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

public:
	Window(Window& other) = delete;
	void operator=(const Window&) = delete;

	static Window* GetInstance(short _width, short _height, short _map_width, short _map_height);

	unsigned short GetScreenWidth() const;													// get m_screen m_screen_width
	unsigned short GetScreenHeight() const; 												// get m_screen m_screen_height

	unsigned short GetMapWidth() const;												// get map m_screen_width
	unsigned short GetMapHeight() const;												// get map m_screen_height

	unsigned short GetTopBorderY() const;												// get m_screen m_screen_height
	unsigned short GetLeftBorderX() const;											// get m_screen m_screen_height
	unsigned short GetBottomBorderY() const;											// get m_screen m_screen_height
	unsigned short GetRightBorderX() const;											// get m_screen m_screen_height

	SDL_Renderer* GetRenderer() const;											// get m_screen m_screen_height
};