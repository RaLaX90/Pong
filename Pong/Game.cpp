#include "Game.hpp"

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw "Error at sdl_init";
	}

	if (TTF_Init() != 0) {
		throw "Error at TTF_Init";
	}

	//if (IMG_Init(IMG_INIT_PNG) != 0) {
	//	throw "Error at IMG_Init";
	//}

	State state = STATE_OK;
	m_desired_fps = 60;

	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	//m_generator = std::mt19937(m_rd());
	//m_distribution_screen_width = std::uniform_int_distribution<short>(window->GetLeftBorderX(), window->GetRightBorderX());
	//m_distribution_screen_height = std::uniform_int_distribution<short>(window->GetTopBorderY(), window->GetBottomBorderY());

	//m_distribution_direction_x = std::uniform_int_distribution<short>(-5, 5);
	//m_distribution_direction_y = std::uniform_int_distribution<short>(-5, 5);

	player1 = std::make_unique<Paddle>(
		window->GetRenderer(),
		"../res/icons/paddle.bmp",
		PositionStruct{ 10, (window->GetScreenHeight() / 2) - PADDLE_HEIGHT },
		SizeStruct{ PADDLE_WIDTH, PADDLE_HEIGHT },
		SpeedStruct{ 0, INITIAL_PADDLE_SPEED_Y },
		SDL_Rect{ window->GetMapWidth() / 3, window->GetMapHeight() / 4 , 50, 120 }
	);

	player2 = std::make_unique<Paddle>(
		window->GetRenderer(),
		"../res/icons/paddle.bmp",
		PositionStruct{ window->GetScreenWidth() - PADDLE_WIDTH - 10, (window->GetScreenHeight() / 2) - PADDLE_HEIGHT },
		SizeStruct{ PADDLE_WIDTH, PADDLE_HEIGHT },
		SpeedStruct{ 0, INITIAL_PADDLE_SPEED_Y },
		SDL_Rect{ (window->GetMapWidth() / 3) * 2, window->GetMapHeight() / 4 , 50, 120 }
	);

	ball = std::make_unique<Ball>(
		window->GetRenderer(),
		"../res/icons/ball.png",
		PositionStruct{ window->GetScreenWidth() / 2, window->GetScreenHeight() / 2 },
		SizeStruct{ BALL_WIDTH, BALL_HEIGHT },
		SpeedStruct{ INITIAL_BALL_SPEED_X, INITIAL_BALL_SPEED_Y }
	);

	m_scoreFont = TTF_OpenFont("../res/fonts/OpenSans-Bold.ttf", 400);
	if (m_scoreFont == nullptr)
	{
		throw "Failed to load the font";
	}
}

Game::~Game()
{
	TTF_CloseFont(m_scoreFont);

	//IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Game::resetRound()
{
	SDL_Delay(1500);

	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
	ball->SetPositionX(window->GetScreenWidth() / 2);
}

void Game::drawScore(Paddle paddle)
{
	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_Color White = { 200, 200, 200, 255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_scoreFont, std::to_string(paddle.GetScore()).c_str(), White);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);

	SDL_FreeSurface(surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = window->GetMapWidth() / 3;
	Message_rect.y = window->GetMapHeight() / 4;
	Message_rect.w = 100;
	Message_rect.h = 100;

	SDL_RenderCopy(window->GetRenderer(), Message, NULL, paddle.GetScoreRectPointer());

	SDL_DestroyTexture(Message);
}

void Game::Update()
{
	current_time = SDL_GetTicks();

	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	ball->Move(window->GetScreenHeight(), player1->GetRectPointer(), player2->GetRectPointer());

	if (ball->GetRect().x + ball->GetRect().w < 0)
	{
		player1->addScore();
		resetRound();
	}
	else if (ball->GetRect().x > window->GetScreenWidth())
	{
		player2->addScore();
		resetRound();
	}

	// Clamping FPS.
	if (1000 / m_desired_fps > (SDL_GetTicks() - current_time)) {
		m_actual_fps = 1000 / m_desired_fps - (SDL_GetTicks() - current_time);

		SDL_Delay(m_actual_fps);
	}
}

void Game::HandleEvents()
{
	while (SDL_PollEvent(&event)) {

		switch (event.type)
		{
		case SDL_QUIT: {
			state = STATE_EXIT;
			break;
		}
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: {
				state = STATE_EXIT;
				break;
			}
			case SDLK_w: {
				player1->MoveUp();
				break;
			}
			case SDLK_s: {
				Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

				player1->MoveDown(window->GetScreenHeight());
				break;
			}
			case SDLK_UP: {
				player2->MoveUp();
				break;
			}
			case SDLK_DOWN: {
				Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

				player2->MoveDown(window->GetScreenHeight());
				break;
			}
			default: {
				break;
			}
			}

			break;
		}
		default: {
			break;
		}
		}
	}
}

void Game::DrawAll()
{
	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_SetRenderDrawColor(window->GetRenderer(), 0x00, 0x00, 0x00, 0x00);
	// Clear Scene
	SDL_RenderClear(window->GetRenderer());

	SDL_SetRenderDrawColor(window->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

	player1->Draw(window->GetRenderer());
	player2->Draw(window->GetRenderer());

	ball->Draw(window->GetRenderer());
	//drawScore(*player1.get()); //TODO (work, but throw a exception)
	//drawScore(*player2.get());

	SDL_Rect rect;
	int height = 0;
	while (height < WINDOW_HEIGHT)
	{
		rect = { WINDOW_WIDTH / 2, height, 5, 30 };
		SDL_RenderFillRect(window->GetRenderer(), &rect);
		height += 70;
	}

	SDL_RenderPresent(window->GetRenderer());
}

Game::State Game::GetState() const
{
	return state;
}