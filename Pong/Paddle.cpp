#include "Paddle.hpp"

Paddle::Paddle(SDL_Renderer* _renderer, const char* _path_to_image, const PositionStruct& _start_position, const SizeStruct& _start_size, const SpeedStruct& _start_speed, SDL_Rect _score_rect) :
	Game_object(_renderer, _path_to_image, _start_position, _start_size, _start_speed), m_score_rect(_score_rect)
{
	m_score = 0;

	if (TTF_Init() != 0) {
		throw "Error at TTF_Init";
	}

	TTF_Font* m_scoreFont = TTF_OpenFont("../res/fonts/OpenSans-Bold.ttf", 400);
	if (m_scoreFont == nullptr)
	{
		throw "Failed to load the font";
	}
	m_score_font = m_scoreFont;
}

Paddle::~Paddle()
{
	TTF_CloseFont(m_score_font);
	TTF_Quit();
}

void Paddle::DrawScore(SDL_Renderer* _renderer)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_score_font, std::to_string(m_score).c_str(), SDL_Color{200, 200, 200, 255});

	SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);

	SDL_FreeSurface(surfaceMessage);

	SDL_RenderCopy(_renderer, Message, NULL, &m_score_rect);

	SDL_DestroyTexture(Message);
}

void Paddle::AddScore()
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

void Paddle::AIMove(unsigned short _window_height, const SDL_Rect* _ball_position_and_size)
{
	if (_ball_position_and_size->y > position_and_size.y + (position_and_size.h / 2)) {
		MoveDown(_window_height);
	}
	else if (_ball_position_and_size->y < position_and_size.y + (position_and_size.h / 2)) {
		MoveUp();
	}
}

char Paddle::GetScore() const
{
	return m_score;
}

const SDL_Rect* Paddle::GetScoreRectPointer() const
{
	return &m_score_rect;
}
